/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* BigInteger.c                                         /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: November 30, 2024                              \ \ \_/__ \_\ \_  __  */
/*                                                       \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the hxy open source project.
 *
 * Copyright (c) 2024 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */
 
#include "Foundation/BigInteger.h"

/* MARK: - Private Constants */

/*
 * ceil(log2(radix) * 1024)
 * bitsPerDigit in the given radix times 1024.
 * Rounded up to avoid underallocation.
 */
Int32 BIG_INTEGER_BITS_PER_DIGIT[] = {
     0,    0, 1024, 1624, 2048, 2378, 2648, 2875, 3072, 3247, 3402,
  3543, 3672, 3790, 3899, 4001, 4096, 4186, 4271, 4350, 4426, 4498,
  4567, 4633, 4696, 4756, 4814, 4870, 4923, 4975, 5025, 5074, 5120,
  5166, 5210, 5253, 5295
};

/*
 * The following two arrays are used for fast String conversions. Both are
 * indexed by radix.  The first is the number of digits of the given radix that
 * can fit in a UInt64 without overflow, i.e., the highest integer n such that
 * radix**n < 2**64 - 1.
 *
 * The second is the "UInt64 radix" that tears each number into "UInt64 digits",
 * each of which consists of the number of digits in the corresponding element
 * in DIGITS_PER_UINT64 (UINT64_RADIX[i] = i ** DIGITS_PER_UINT64[i]).
 *
 * Both arrays have nonsense values in their 0 and 1 elements, as radixes 0 and
 * 1 are not used.
 */
Int32 BIG_INTEGER_DIGITS_PER_UINT64[] = {
   0,  0, 63, 40, 31, 27, /*  0 ...  5 */
  24, 22, 21, 20, 19, 18, /*  6 ... 11 */
  17, 17, 16, 16, 15, 15, /* 12 ... 17 */
  15, 15, 14, 14, 14, 14, /* 18 ... 23 */
  13, 13, 13, 13, 13, 13, /* 24 ... 29 */
  13, 12, 12, 12, 12, 12, /* 30 ... 35 */
  12                      /* 36 */
};

UInt64 BIG_INTEGER_UINT64_RADIX[] = {
  0x0000000000000000ull, 0x0000000000000000ull, 0x8000000000000000ull,
  0xa8b8b452291fe821ull, 0x4000000000000000ull, 0x6765c793fa10079dull,
  0x41c21cb8e1000000ull, 0x3642798750226111ull, 0x8000000000000000ull,
  0xa8b8b452291fe821ull, 0x8ac7230489e80000ull, 0x4d28cb56c33fa539ull,
  0x1eca170c00000000ull, 0x780c7372621bd74dull, 0x1e39a5057d810000ull,
  0x5b27ac993df97701ull, 0x1000000000000000ull, 0x27b95e997e21d9f1ull,
  0x5da0e1e53c5c8000ull, 0xd2ae3299c1c4aedbull, 0x16bcc41e90000000ull,
  0x2d04b7fdd9c0ef49ull, 0x5658597bcaa24000ull, 0xa0e2073737609371ull,
  0x0c29e98000000000ull, 0x14adf4b7320334b9ull, 0x226ed36478bfa000ull,
  0x383d9170b85ff80bull, 0x5a3c23e39c000000ull, 0x8e65137388122bcdull,
  0xdd41bb36d259e000ull, 0x0aee5720ee830681ull, 0x1000000000000000ull,
  0x172588ad4f5f0981ull, 0x211e44f7d02c1000ull, 0x2ee56725f06e5c71ull,
  0x41c21cb8e1000000ull
};

/* The natural log of 2. */
#define BIG_INTEGER_LOG_TWO 0.6931471805599453

Double BIG_INTEGER_LOG_CACHE[] = {
  0.0, 0.0,
  0.6931471805599453, 1.0986122886681098, 1.3862943611198906,
  1.6094379124341003, 1.791759469228055,  1.9459101490553132,
  2.0794415416798357, 2.1972245773362196, 2.302585092994046,
  2.3978952727983707, 2.4849066497880004, 2.5649493574615367,
  2.6390573296152584, 2.70805020110221,   2.772588722239781,
  2.833213344056216,  2.8903717578961645, 2.9444389791664403,
  2.995732273553991,  3.044522437723423,  3.091042453358316,
  3.1354942159291497, 3.1780538303479458, 3.2188758248682006,
  3.258096538021482,  3.295836866004329,  3.332204510175204,
  3.367295829986474,  3.4011973816621555, 3.4339872044851463,
  3.4657359027997265, 3.4965075614664802, 3.5263605246161616,
  3.5553480614894135, 3.58351893845611
};

/*
 * The threshold value for using Schoenhage recursive base conversion. If
 * the number of ints in the number are larger than this value,
 * the Schoenhage algorithm will be used. In practice, it appears that the
 * Schoenhage routine is faster for any threshold down to 2, and is
 * relatively flat for thresholds between 2-25, so this choice may be
 * varied within this range for very small effect.
 */
#define BIG_INTEGER_SCHOENHAGE_BASE_CONVERSION_THRESHOLD 20

/* MARK: - Private methods */

/* Multiply x array times word y in place, and add word z. */
static Void big_integer_destructive_multiply_add(UInt64* x,
                                                 Int64 count,
                                                 UInt64 y,
                                                 UInt64 z) {
  /* Perform the multiplication word by word */
  UInt128 product = 0;
  UInt64 carry = 0;
  var i = count - 1;
  for (; i >= 0; i -= 1) {
    product = (UInt128)y * x[i] + carry;
    x[i] = (UInt64)product;
    carry = product >> 64;
  }

  /* Perform the addition */
  var sum = (UInt128)x[count - 1] + z;
  x[count - 1] = (UInt64)sum;
  carry = sum >> 64;
  for (i = count - 2; i >= 0; i -= 1) {
    sum = x[i] + carry;
    x[i] = (UInt64)sum;
    carry = sum >> 64;
  }
}

/*
 * Removes all the leading zero bytes.
 * Returnes the count of the array stripped of any leading zero bytes.
 * Since the source is trusted the copying is skipped.
 */
static Int64 big_integer_trusted_strip_leading_zero_uint64s(UInt64* value,
                                                            Int64 count) {
  var keep = 0;
  /* Find first nonzero byte. */
  for (; keep < count && value[keep] == 0; keep += 1);
  if (keep != 0) {
    let new_count = count - keep;

    /* Copy value[keep ..< count] */
    memmove(value, value + keep * sizeof(UInt64), new_count * sizeof(UInt64));

    return new_count;
  }

  return count;
}

/* Private method to return bit count for a UInt64. */
#define big_integer_bit_count_for_uint64(n) \
          (64 - __builtin_clzll((n)))

struct BigInteger* big_integer_init_from_words(UInt64* magnitude,                                                                Int64 count,
                                               enum BigIntegerSign sign) {
  var n = (struct BigInteger*)malloc(sizeof(struct BigInteger));

  n->_magnitude = malloc(sizeof(UInt64) * count);
  memcpy(n->_magnitude, magnitude, sizeof(UInt64) * count);
  n->_magnitude_capacity = count;
  n->_magnitude_count = count;
  n->_sign = count == 0 ? none : sign;

  return n;
}

/* Convert this MutableBigInteger to a BigInteger object. */
struct BigInteger*
big_integer_mutable_big_integer_to_big_integer(struct MutableBigInteger* value,
                                               enum BigIntegerSign sign) {
  if (value->_magnitude_count == 0 || sign == none) {
    var n = (struct BigInteger*)malloc(sizeof(struct BigInteger));

    n->_magnitude = malloc(sizeof(UInt64) * 0);
    n->_magnitude_count = 0;
    n->_magnitude_capacity = 0;
    n->_sign = none;

    return n;
  }

  return big_integer_init_from_words(value->_magnitude + value->_offset,
                                     value->_magnitude_count, sign);
}

/**
 * If `zero_count` > 0, appends that many zeros to the specified `text`;
 * otherwise, does nothing.
 *
 * - Parameters:
 *   - text: The string buffer that will be appended to.
 *   - zero_count: The number of zeros to append.
 */
static Void big_integer_pad_with_zeros(Char* text,
                                       Int64 offset,
                                       Int64 zero_count) {
  while (zero_count >= 63) {
    strcat(text + offset,
           "000000000000000000000000000000000000000000000000000000000000000");
    zero_count -= 63;
  }
  if (zero_count > 0) {
    strncpy(text + offset,
            "000000000000000000000000000000000000000000000000000000000000000",
            zero_count);
  }
}

/**
 * This method is used to perform `to_string()` when arguments are small.
 * The value must be non-negative. If `padding <= 0` no padding
 * (pre-pending with zeros) will be effected.
 *
 * - Parameters:
 *   - radix: The base to convert to.
 *   - text: The string buffer that will be appended to in place.
 *   - offset: The start index of `text`.
 *   - padding: The minimum number of digits to pad to.
 */
static Void big_integer_small_to_string(struct BigInteger* u,
                                        Int64 radix,
                                        Char* text,
                                        Int64 offset,
                                        Int64 padding) {
  precondition(u->_sign != minus,
               "This method can only be called for non-negative numbers.");

  if (u->_sign == none) {
    big_integer_pad_with_zeros(text, offset, padding);
    return;
  }

  /* Compute upper bound on number of digit groups and allocate space. */
  /* FIXME: This upper bound may not enough. */
  let max_number_digit_groups = (4 * u->_magnitude_count + 6) / 7;
  var digit_groups = (UInt64*)malloc(sizeof(UInt64) * max_number_digit_groups);

  /* Translate number to string, a digit group at a time. */
  var tmp = big_integer_copy(u);
  var group_count = 0;
  while (tmp->_sign != none) {
    var d = BIG_INTEGER_UINT64_RADIX[radix];

    var a = mutable_big_integer_init_from_words(tmp->_magnitude,
                                                tmp->_magnitude_count);
    var b = mutable_big_integer_init_from_words(&d, 1);
    var quotient_and_remainder = mutable_big_integer_divide(a, b);
    var q = quotient_and_remainder[0];
    var r = quotient_and_remainder[1];

    var q2 = big_integer_mutable_big_integer_to_big_integer(q, tmp->_sign);
    var r2 = big_integer_mutable_big_integer_to_big_integer(r, tmp->_sign);

    digit_groups[group_count] = r2->_magnitude[0];
    group_count += 1;

    mutable_big_integer_deinit(a);
    mutable_big_integer_deinit(b);
    mutable_big_integer_deinit(q);
    mutable_big_integer_deinit(r);
    big_integer_deinit(r2);
    big_integer_deinit(tmp);

    tmp = q2;
  }
  big_integer_deinit(tmp); /* Free the last q2 */

  /* Get string version of first digit group. */
  Char s[64 + 1];
  ansi_itoaull(digit_groups[group_count - 1], s, (Int32)radix);

  /* Pad with internal zeros if necessary. */
  let digits = (group_count - 1) * BIG_INTEGER_DIGITS_PER_UINT64[radix];
  big_integer_pad_with_zeros(text,
                             offset,
                             padding - (strlen(s) + digits));

  /* Put first digit group into result buffer. */
  strcat(text + offset, s);

  /* Append remaining digit groups each padded with leading zeros. */
  var i = group_count - 2;
  for (; i >= 0; i -= 1) {
    /* Prepend (any) leading zeros for this digit group. */
    ansi_itoaull(digit_groups[i], s, (Int32)radix);
    let leading_zeros = BIG_INTEGER_DIGITS_PER_UINT64[radix] - strlen(s);
    if (leading_zeros != 0) {
      strncat(text + offset,
              "000000000000000000000000000000000000000000000000000000000000000",
              leading_zeros);
    }
    strcat(text + offset, s);
  }

  free(digit_groups);
}

/**
 * Converts the specified BigInt to a string and appends to `text`. This
 * implements the recursive Schoenhage algorithm for base conversions. This
 * method can only be called for non-negative numbers.
 *
 * See Knuth, Donald, _The Art of Computer Programming_, Vol. 2,
 * Answers to Exercises (4.4) Question 14.
 *
 * - Parameters:
 *   - u: The number to convert to a string.
 *   - text: The buffer string that will be appended to in place.
 *   - offset: The start index of `text`.
 *   - radix: The base to convert to.
 *   - padding: The minimum number of digits to pad to.
 */
static Void big_integer_to_string_schoenhage(struct BigInteger* u,
                                             Char* text,
                                             Int64 offset,
                                             Int64 radix,
                                             Int64 padding) {
  precondition(u->_sign != minus,
               "This method can only be called for non-negative numbers.");

  /*
   * If we're smaller than a certain threshold, use the small_to_string()
   * method, padding with leading zeroes when necessary unless we're
   * at the beginning of the string or digits <= 0. As u->_sign >= 0,
   * small_to_string() will not prepend a negative sign.
   */
  if (u->_magnitude_count <= BIG_INTEGER_SCHOENHAGE_BASE_CONVERSION_THRESHOLD) {
    big_integer_small_to_string(u, radix, text, offset, padding);
  }
//  if (u.mag.length <= SCHOENHAGE_BASE_CONVERSION_THRESHOLD) {
//      u.smallToString(radix, sb, digits);
//      return;
//  }
}


///*
// * Ensure that the BigInt is in normal form, specifically making sure that there
// * are no leading zeros, and that if the magnitude is zero, then count is zero.
// */
//static Void big_int_normalize(struct BigInt* bigInt) {
//  if (bigInt->_magnitude_count == 0) {
//    bigInt->_sign = none;
//    return;
//  }
//
//  if (bigInt->_magnitude[0] != 0) {
//    return;
//  }
//
//  let new_count = big_int_strip_leading_zero_uint64s(bigInt->_magnitude,
//                                                     bigInt->_magnitude_count);
//  bigInt->_magnitude_count = new_count;
//}

//static struct BigInt* big_int_init_internal(UInt64* magnitude,
//                                            Int64 count,
//                                            Int64 capacity,
//                                            enum BigIntSign sign) {
//  precondition(count <= capacity, "count must less than or equal to capacity");
//
//  var bigInt = (struct BigInt*)malloc(sizeof(struct BigInt));
//
//  bigInt->_magnitude = malloc(sizeof(UInt64) * capacity);
//  if (count != 0 && magnitude != NULL) {
//    memcpy(bigInt->_magnitude, magnitude, sizeof(UInt64) * count);
//  }
//  bigInt->_magnitude_count = count;
//  bigInt->_magnitude_capacity = capacity;
//  bigInt->_sign = sign;
//
//  return bigInt;
//}
//
//
///*
// * Return the index of the lowest set bit in given big int. If the magnitude of
// * that big int is zero, -1 is returned.
// */
//static Int64 big_int_get_lowest_set_bit(struct BigInt* value) {
//  if (value->_sign == none) {
//    return -1;
//  }
//  var j = value->_magnitude_count - 1;
//  for (; (j > 0) && (value->_magnitude[j] == 0); j -= 1);
//  let word = value->_magnitude[j];
//  if (word == 0) {
//    return -1;
//  }
//  let bit = (value->_magnitude_count - 1 - j) << 6;
//  return bit + __builtin_ctzll(word);
//}
//
///*
// * Left shift the big int n bits, where n is less than 64, placing the result in
// * the specified array.
// * Assumes that magnitude_count > 0, n > 0 for speed.
// */
//static Void big_int_primitive_left_shift(struct BigInt* value,
//                                         Int64 n,
//                                         UInt64* result) {
//  let n2 = 64 - n;
//  let count = value->_magnitude_count - 1;
//  var b = value->_magnitude[0];
//  var i = 0;
//  for (; i < count; i += 1) {
//    var c = value->_magnitude[i + 1];
//    result[i] = (b << n) | (c >> n2);
//    b = c;
//  }
//  result[count] = b << n;
//}
//
///*
// * Divide the BigInt by the divisor.
// *
// * Given nonnegative integers u = (u_1, u_2, ..., u_m+n)_b and
// * v = (v1, v2, ..., v_n)_b, where v1 != 0 and n > 1, we form the radix-b
// * quotient floor(u/v) = (q_0, q_1, ..., q_m)_b and the remainder u  mod v =
// * (r_1, r_2, ..., r_n)_b.
// */
//static Void big_int_divide_magnitude(struct BigInt* u,
//                                     struct BigInt* v,
//                                     struct BigInt** result) {
//  /* assert v.magnitude_count > 1 */
//  /*
//   * D1 normalize the divisor
//   * Set d be a value. Then set (u_0, u_1, u_2, ..., u_m+n)_b equal to
//   * (u_1, u_2, ..., u_m+n)_b times d, and set (v_1, v_2, ..., v_n)_b equal to
//   * (v_1, v_2, ..., v_n)_b times d. Any value of d that results in
//   * v_1 >= floor(b / 2) will suffice.
//   */
//  var shift = __builtin_clzll(v->_magnitude[0]);
//  /* Copy v to protect divisor */
//  let divisor_magnitude_count = v->_magnitude_count;
//  UInt64* divisor_magnitude = NULL;
//  var remainder = big_int_init_from_int128(0);
//  if (shift > 0) {
//    divisor_magnitude = malloc(sizeof(UInt64) * divisor_magnitude_count);
//    big_int_primitive_left_shift(v, shift, divisor_magnitude);
//    if (__builtin_clzll(u->_magnitude[0]) >= shift) {
//      remainder->_magnitude = realloc(remainder->_magnitude,
//                                      sizeof(UInt64) * u->_magnitude_count + 1);
//      remainder->_magnitude_count = u->_magnitude_count;
////      remainder
//    }
//  }
//}
//
//
///**
// * Compares the magnitude array of `lhs` with the `rhs`'s. This is the version
// * of compare() ignoring sign.
// */
//static Int64 big_int_compare_magnitude(struct BigInt* lhs, struct BigInt* rhs) {
//  if (lhs->_magnitude_count < rhs->_magnitude_count) {
//    return -1;
//  }
//  if (lhs->_magnitude_count > rhs->_magnitude_count) {
//    return 1;
//  }
//  /* Find the first mismatch index */
//  var i = -1;
//  var k = 0;
//  for (; k < lhs->_magnitude_count; k += 1) {
//    if (lhs->_magnitude[k] != rhs->_magnitude[k]) {
//      i = k;
//      break;
//    }
//  }
//  if (i != -1) {
//    return lhs->_magnitude[i] < rhs->_magnitude[i] ? -1 : 1;
//  }
//  return 0;
//}
//
/* MARK: - Creating and Destroying a BigInt */

/**
 * Creates a new `BigInt` value from the given string and radix.
 */
struct BigInteger* big_integer_init_from_string(const Char* text, Int64 radix) {
  var cursor = 0;
  let text_count = strlen(text);

  precondition(radix >= 2 && radix <= 36, "Radix out of range");
  precondition(text_count > 0, "Zero length BigInt");

  var value = (struct BigInteger*)malloc(sizeof(struct BigInteger));

  /* Check for at most one leading sign. */
  value->_sign = plus;
  let index1 = (Int64)(strrchr(text, '-') - text); /* lastIndexOf */
  let index2 = (Int64)(strrchr(text, '+') - text); /* lastIndexOf */
  if (index1 >= 0) {
    precondition(index1 == 0 && index2 < 0, "Illegal embedded sign character");
    value->_sign = minus;
    cursor = 1;
  } else if (index2 >= 0) {
    precondition(index2 == 0, "Illegal embedded sign character");
    cursor = 1;
  }
  precondition(cursor != text_count, "Zero length BigInt");

  /* Skip leading zeros and compute number of digits in magnitude. */
  while (cursor < text_count && text[cursor] == '0') {
    cursor += 1;
  }
  if (cursor == text_count) {
    /* The BigInteger zero has a zero-length magnitude array. */
    value->_sign = none;
    value->_magnitude_count = 0;
    value->_magnitude_capacity = 0;
    value->_magnitude = (UInt64*)malloc(sizeof(UInt64) * 0);
    return value;
  }
  let digits_count = (Int64)text_count - cursor;

  /*
   * Pre-allocate array of expected size. May be too large but can never be too
   * small. Typically exact.
   */
  var bits_count = ((digits_count * BIG_INTEGER_BITS_PER_DIGIT[radix]) >> 10);
  bits_count += 1;
  /* Add 63 to make sure that count is bigger than 64. */
  let magnitude_count = (bits_count + 63) >> 6;
  value->_magnitude_count = magnitude_count;
  value->_magnitude_capacity = magnitude_count;
  value->_magnitude = (UInt64*)malloc(sizeof(UInt64) * magnitude_count);

  /* Process first (potentially short) digit group. */
  var first_group_count = digits_count % BIG_INTEGER_DIGITS_PER_UINT64[radix];
  if (first_group_count == 0) {
    first_group_count = BIG_INTEGER_DIGITS_PER_UINT64[radix];
  }
  Char group[64 + 1];
  memcpy(group, text + cursor * sizeof(Char), first_group_count);
  group[first_group_count] = '\0';
  cursor += first_group_count;
  value->_magnitude[magnitude_count - 1] = ansi_strtoull(group,
                                                         NULL,
                                                         (Int32)radix);
  /* Process remaining digit groups */
  let super_radix = BIG_INTEGER_UINT64_RADIX[radix];
  var group_value = 0ull;
  while (cursor < text_count) {
    memcpy(group,
           text + cursor * sizeof(Char),
           BIG_INTEGER_DIGITS_PER_UINT64[radix]);
    group[BIG_INTEGER_DIGITS_PER_UINT64[radix]] = '\0';
    cursor += BIG_INTEGER_DIGITS_PER_UINT64[radix];
    group_value = ansi_strtoull(group, NULL, (Int32)radix);
    big_integer_destructive_multiply_add(value->_magnitude,
                                         value->_magnitude_count,
                                         super_radix,
                                         group_value);
  }

  /*
   * Required for cases where the array was overallocated.
   * Remove leading zeros.
   */
  let count = value->_magnitude_count;
  let magnitude = value->_magnitude;
  let new_count = big_integer_trusted_strip_leading_zero_uint64s(magnitude,
                                                                 count);
  value->_magnitude_count = new_count;

  return value;
}

/**
 * Creates a new `BigInteger` containing the given value.
 */
struct BigInteger* big_integer_copy(struct BigInteger* value) {
  var copy = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  /* Copy magnitude */
  copy->_magnitude = malloc(sizeof(UInt64) * value->_magnitude_capacity);
  memcpy(copy->_magnitude,
         value->_magnitude,
         sizeof(UInt64) * value->_magnitude_capacity);
  copy->_magnitude_count = value->_magnitude_count;
  copy->_magnitude_capacity = value->_magnitude_capacity;
  /* Copy others */
  copy->_sign = value->_sign;

  return copy;
}

/**
 * Destroys a BigInteger.
 */
Void big_integer_deinit(struct BigInteger* value) {
  if (value == NULL) {
    return;
  }

  free(value->_magnitude);
  free(value);
}

///**
// * Creates a new `BigInt` value with the specified value.
// */
//struct BigInt* big_int_init_from_int128(Int128 value) {
//  var sign = none;
//
//  if (value < 0) {
//    sign = minus;
//    value = -value;
//  } else if (value > 0) {
//    sign = plus;
//  }
//
//  let high_word = (UInt64)(value >> 64);
//  if (high_word == 0) {
//    UInt64 magnitude[1] = { (UInt64)value };
//    return big_int_init_internal(magnitude, 1, 1, sign);
//  }
//  UInt64 magnitude[2] = { high_word, (UInt64)value };
//  return big_int_init_internal(magnitude, 2, 2, sign);
//}
//

/* MARK: - Converting Numeric Values */

/**
 * Creates a string representing the given value in base 10, or some other
 * specified base.
 */
Char* big_integer_to_string(struct BigInteger* value,
                            Int64 radix,
                            Bool is_uppercase) {
  if (value->_sign == none) {
    var text = (Char*)malloc(sizeof(Char) * 2);
    strcpy(text, "0");
    return text;
  }
  if (radix < 2 || radix > 36) {
    radix = 10;
  }

  var abs = big_integer_copy(value);
  abs->_sign = abs->_sign == minus ? plus : abs->_sign;

  /*
   * Ensure buffer capacity sufficient to contain string representation
   *     floor(bitLength*log(2)/log(radix)) + 1
   * plus an additional character for the sign if negative.
   */
  let b = big_integer_bit_count(abs);
  let log_cache_radix = BIG_INTEGER_LOG_CACHE[radix];
  var count = (UInt64)floor(b * BIG_INTEGER_LOG_TWO / log_cache_radix) + 1;
  count += value->_sign == minus ? 1 : 0;

  var text = (Char*)malloc(sizeof(Char) * count);
  var offset = 0;
  if (value->_sign == minus) {
    text[0] = '-';
    offset += 1;
  }

  /* Use recursive toString. */
  big_integer_to_string_schoenhage(abs, text, offset, radix, 0);

  return text;
}

///* MARK: - Performing Calculations */
//
///**
// * Returns -1, 0 or 1 that indicates whether the number object's value is
// * greater than, equal to, or less than a given number.
// */
//Int64 big_int_compare(struct BigInt* lhs, struct BigInt* rhs) {
//  if (lhs->_sign == rhs->_sign) {
//    switch (lhs->_sign) {
//      case plus: return big_int_compare_magnitude(lhs, rhs); break;
//      case minus: return big_int_compare(rhs, lhs); break;
//      default: return 0; break;
//    }
//  }
//
//  return lhs->_sign == plus ? 1 : -1;
//}
//
/* MARK: - Working with Binary Representation */

/**
 * Returns the number of bits in the minimal two's-complement representation of
 * this BigInt, **excluding** a sign bit.
 */
Int64 big_integer_bit_count(struct BigInteger* value) {
  if (value->_sign == none) {
    return 0;
  }
  /* Calculate the bit length of the magnitude. */
  var bit_count = ((value->_magnitude_count - 1) << 6);
  bit_count += big_integer_bit_count_for_uint64(value->_magnitude[0]);
  if (value->_sign == minus) {
    /* Check if magnitude is a power of two. */
    var is_pow2 = __builtin_popcountll(value->_magnitude[0]) == 1;
    var i = 1;
    for (; i < value->_magnitude_count && is_pow2; i += 1) {
      is_pow2 = (value->_magnitude[i] == 0);
    }
    bit_count = is_pow2 ? bit_count - 1 : bit_count;
  }

  return bit_count;
}

/*===----------------------------------------------------------------------===*/
/*         ___                            ___                                 */
/*       /'___\                          /\_ \    __                          */
/*      /\ \__/   __      ___      __    \//\ \  /\_\    ___      __          */
/*      \ \ ,__\/'__`\  /' _ `\  /'_ `\    \ \ \ \/\ \ /' _ `\  /'_ `\        */
/*       \ \ \_/\ \L\.\_/\ \/\ \/\ \L\ \    \_\ \_\ \ \/\ \/\ \/\ \L\ \       */
/*        \ \_\\ \__/.\_\ \_\ \_\ \____ \   /\____\\ \_\ \_\ \_\ \____ \      */
/*         \/_/ \/__/\/_/\/_/\/_/\/___L\ \  \/____/ \/_/\/_/\/_/\/___L\ \     */
/*                                 /\____/                        /\____/     */
/*                                 \_/__/                         \_/__/      */
/*===----------------------------------------------------------------------===*/
