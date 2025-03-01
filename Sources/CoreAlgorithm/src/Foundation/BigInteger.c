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
 * This source file is part of the CoreAlgorithm open source project.
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
 * can fit in a Int64 without overflow, i.e., the highest integer n such that
 * radix**n < 2**63.
 *
 * The second is the "Int64 radix" that tears each number into "Int64 digits",
 * each of which consists of the number of digits in the corresponding element
 * in DIGITS_PER_UINT64 (UINT64_RADIX[i] = i ** DIGITS_PER_UINT64[i]).
 *
 * Both arrays have nonsense values in their 0 and 1 elements, as radixes 0 and
 * 1 are not used.
 */
Int64 BIG_INTEGER_DIGITS_PER_DOUBLE_WORD[] = {
   0,  0, 62, 39, 31, 27, /*  0 ...  5 */
  24, 22, 20, 19, 18, 18, /*  6 ... 11 */
  17, 17, 16, 16, 15, 15, /* 12 ... 17 */
  15, 14, 14, 14, 14, 13, /* 18 ... 23 */
  13, 13, 13, 13, 13, 12, /* 24 ... 29 */
  12, 12, 12, 12, 12, 12, /* 30 ... 35 */
  12                      /* 36        */
};

Int64 BIG_INTEGER_DOUBLE_WORD_RADIX[] = {
  0x0000000000000000ll, 0x0000000000000000ll, 0x4000000000000000ll,
  0x383d9170b85ff80bll, 0x4000000000000000ll, 0x6765c793fa10079dll,
  0x41c21cb8e1000000ll, 0x3642798750226111ll, 0x1000000000000000ll,
  0x12bf307ae81ffd59ll,  0xde0b6b3a7640000ll, 0x4d28cb56c33fa539ll,
  0x1eca170c00000000ll, 0x780c7372621bd74dll, 0x1e39a5057d810000ll,
  0x5b27ac993df97701ll, 0x1000000000000000ll, 0x27b95e997e21d9f1ll,
  0x5da0e1e53c5c8000ll,  0xb16a458ef403f19ll, 0x16bcc41e90000000ll,
  0x2d04b7fdd9c0ef49ll, 0x5658597bcaa24000ll,  0x6feb266931a75b7ll,
   0xc29e98000000000ll, 0x14adf4b7320334b9ll, 0x226ed36478bfa000ll,
  0x383d9170b85ff80bll, 0x5a3c23e39c000000ll,  0x4e900abb53e6b71ll,
   0x7600ec618141000ll,  0xaee5720ee830681ll, 0x1000000000000000ll,
  0x172588ad4f5f0981ll, 0x211e44f7d02c1000ll, 0x2ee56725f06e5c71ll,
  0x41c21cb8e1000000ll
};

/*
 * These two arrays are the integer analogue of above.
 */
Int64 BIG_INTEGER_DIGITS_PER_WORD[] = {
   0,  0, 30, 19, 15, 13, /*  0 ...  5 */
  11, 11, 10,  9,  9,  8, /*  6 ... 11 */
   8,  8,  8,  7,  7,  7, /* 12 ... 17 */
   7,  7,  7,  7,  6,  6, /* 18 ... 23 */
   6,  6,  6,  6,  6,  6, /* 24 ... 29 */
   6,  6,  6,  6,  6,  6, /* 30 ... 35 */
   5                      /* 36        */
};

Int32 BIG_INTEGER_WORD_RADIX[] = {
  0x00000000, 0x00000000, 0x40000000,
  0x4546b3db, 0x40000000, 0x48c27395,
  0x159fd800, 0x75db9c97, 0x40000000,
  0x17179149, 0x3b9aca00,  0xcc6db61,
  0x19a10000, 0x309f1021, 0x57f6c100,
   0xa2f1b6f, 0x10000000, 0x18754571,
  0x247dbc80, 0x3547667b, 0x4c4b4000,
  0x6b5a6e1d,  0x6c20a40,  0x8d2d931,
   0xb640000,  0xe8d4a51, 0x1269ae40,
  0x17179149, 0x1cb91000, 0x23744899,
  0x2b73a840, 0x34e63b41, 0x40000000,
  0x4cfa3cc1, 0x5c13d840, 0x6d91b519,
  0x39aa400
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
 * This mask is used to obtain the value of an int32 as if it were unsigned.
 */
#define BIG_INTEGER_INT64_MASK 0xffffffffll

/*
 * The threshold value for using Schoenhage recursive base conversion. If
 * the number of int32s in the number are larger than this value,
 * the Schoenhage algorithm will be used. In practice, it appears that the
 * Schoenhage routine is faster for any threshold down to 2, and is
 * relatively flat for thresholds between 2-25, so this choice may be
 * varied within this range for very small effect.
 */
#define BIG_INTEGER_SCHOENHAGE_BASE_CONVERSION_THRESHOLD 20

/*
 * The threshold value for using Karatsuba multiplication.  If the number of
 * int32s in both magnitude arrays are greater than this number, then Karatsuba
 * multiplication will be used. This value is found experimentally to work well.
 */
#define BIG_INTEGER_KARATSUBA_THRESHOLD 80

/* MARK: - Private methods */

/* Multiply x array times word y in place, and add word z. */
static Void big_integer_destructive_multiply_add(Int32* x,
                                                 Int64 count,
                                                 Int32 y,
                                                 Int32 z) {
  /* Perform the multiplication word by word */
  var y_int64 = y & BIG_INTEGER_INT64_MASK;
  var z_int64 = z & BIG_INTEGER_INT64_MASK;

  var product = (Int64)0;
  var carry = (Int64)0;
  var i = count - 1;
  for (; i >= 0; i -= 1) {
    product = y_int64 * (x[i] & BIG_INTEGER_INT64_MASK) + carry;
    x[i] = (Int32)product;
    carry = ((UInt64)product) >> 32;
  }

  /* Perform the addition */
  var sum = (x[count - 1] & BIG_INTEGER_INT64_MASK) + z_int64;
  x[count - 1] = (Int32)sum;
  carry = ((UInt64)sum) >> 32;
  for (i = count - 2; i >= 0; i -= 1) {
    sum = (x[i] & BIG_INTEGER_INT64_MASK) + carry;
    x[i] = (Int32)sum;
    carry = ((UInt64)sum) >> 32;
  }
}

/*
 * Removes all the leading zero bytes.
 * Returnes the count of the array stripped of any leading zero bytes.
 * Since the source is trusted the copying is skipped.
 */
static Int64 big_integer_trusted_strip_leading_zero_words(Int32* value,
                                                          Int64 count) {
  var keep = 0;
  /* Find first nonzero byte. */
  for (; keep < count && value[keep] == 0; keep += 1);
  if (keep != 0) {
    let new_count = count - keep;

    /* Copy value[keep ..< count] */
    memmove(value, value + keep, new_count * sizeof(Int32));

    return new_count;
  }

  return count;
}

/* Private method to return bit count for a word. */
#define big_integer_bit_count_for_word(n) \
          (32 - __builtin_clz((n)))

static struct BigInteger* big_integer_init_from_words(Int32* magnitude,
                                                      Int64 count,
                                                      enum BigIntegerSign sign,
                                                      Bool needs_allocation) {
  var n = (struct BigInteger*)malloc(sizeof(struct BigInteger));

  if (needs_allocation) {
    n->_magnitude = malloc(sizeof(Int32) * count);
    memcpy(n->_magnitude, magnitude, sizeof(Int32) * count);
  } else {
    n->_magnitude = magnitude;
  }
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

    n->_magnitude = malloc(sizeof(UInt32) * 0);
    n->_magnitude_count = 0;
    n->_magnitude_capacity = 0;
    n->_sign = none;

    return n;
  }

  return big_integer_init_from_words(value->_magnitude + value->_offset,
                                     value->_magnitude_count,
                                     sign,
                                     true);
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
    strncat(text + offset,
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
 *   - is_uppercase: Pass `true` to use uppercase letters to represent numerals
 *   greater than 9, or false to use lowercase letters.
 */
static Void big_integer_small_to_string(struct BigInteger* u,
                                        Int64 radix,
                                        Char* text,
                                        Int64 offset,
                                        Int64 padding,
                                        Bool is_uppercase) {
  precondition(u->_sign != minus,
               "This method can only be called for non-negative numbers.");

  if (u->_sign == none) {
    big_integer_pad_with_zeros(text, offset, padding);
    return;
  }

  /* Compute upper bound on number of digit groups and allocate space. */
  let max_number_digit_groups = (4 * u->_magnitude_capacity + 6) / 7;
  var digit_groups = (Int64*)malloc(sizeof(Int64) * max_number_digit_groups);

  /* Translate number to string, a digit group at a time. */
  var tmp = big_integer_copy(u);
  var group_count = 0;
  while (tmp->_sign != none) {
    var d = BIG_INTEGER_DOUBLE_WORD_RADIX[radix];

    var a = mutable_big_integer_init_from_words(tmp->_magnitude,
                                                tmp->_magnitude_count);
    var b = mutable_big_integer_init_from_int64(d);
    var quotient_and_remainder = mutable_big_integer_divide(a, b);
    var q = quotient_and_remainder[0];
    var r = quotient_and_remainder[1];

    var q2 = big_integer_mutable_big_integer_to_big_integer(q, tmp->_sign);
    var r2 = big_integer_mutable_big_integer_to_big_integer(r, tmp->_sign);

    /* r2.int64Value() */
    if (r2->_magnitude_count == 2) {
      var result = (Int64)0;
      var i = 1;
      for (; i >= 0; i -= 1) {
        result = result << 32;
        let index = r2->_magnitude_count - i - 1;
        result += r2->_magnitude[index] & BIG_INTEGER_INT64_MASK;
      }
      digit_groups[group_count] = result;
    } else if (r2->_magnitude_count == 1) {
      digit_groups[group_count] = r2->_magnitude[0] & BIG_INTEGER_INT64_MASK;
    } else {
      digit_groups[group_count] = 0;
    }
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
  Char s[64];
  ansi_itoall(digit_groups[group_count - 1], s, (Int32)radix, is_uppercase);

  /* Pad with internal zeros if necessary. */
  let digits = (group_count - 1) * BIG_INTEGER_DIGITS_PER_DOUBLE_WORD[radix];
  big_integer_pad_with_zeros(text,
                             offset,
                             padding - (strlen(s) + digits));

  /* Put first digit group into result buffer. */
  strcat(text + offset, s);

  /* Append remaining digit groups each padded with leading zeros. */
  var i = group_count - 2;
  for (; i >= 0; i -= 1) {
    /* Prepend (any) leading zeros for this digit group. */
    ansi_itoall(digit_groups[i], s, (Int32)radix, is_uppercase);
    let leading_zeros = BIG_INTEGER_DIGITS_PER_DOUBLE_WORD[radix] - strlen(s);
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
 *   - is_uppercase: Pass `true` to use uppercase letters to represent numerals
 *   greater than 9, or false to use lowercase letters.
 */
static Void big_integer_to_string_schoenhage(struct BigInteger* u,
                                             Char* text,
                                             Int64 offset,
                                             Int64 radix,
                                             Int64 padding,
                                             Bool is_uppercase) {
  precondition(u->_sign != minus,
               "This method can only be called for non-negative numbers.");

  /*
   * If we're smaller than a certain threshold, use the small_to_string()
   * method, padding with leading zeroes when necessary unless we're
   * at the beginning of the string or digits <= 0. As u->_sign >= 0,
   * small_to_string() will not prepend a negative sign.
   */
//  if (u->_magnitude_count <= BIG_INTEGER_SCHOENHAGE_BASE_CONVERSION_THRESHOLD) {
    big_integer_small_to_string(u, radix, text, offset, padding, is_uppercase);
    return;
//  }
}

/**
 * Adds the contents of the int32 arrays x and y. This method allocates a new
 * int32 array to hold the answer and returns a pointer to that array.
 */
static Int32* big_integer_add_words(Int32* x,
                                    Int64 x_count,
                                    Int32* y,
                                    Int64 y_count,
                                    Int64* result_count) {
  /* If x is shorter, swap the two arrays */
  if (x_count < y_count) {
    var delta = x;
    x = y;
    y = delta;

    var delta2 = x_count;
    x_count = y_count;
    y_count = delta2;
  }

  var x_index = x_count;
  var y_index = y_count;
  var result = (Int32*)malloc(sizeof(Int32) * x_index);
  *result_count = x_index;
  var sum = (Int64)0;
  if (y_index == 1) {
    x_index -= 1;
    sum = (x[x_index] & BIG_INTEGER_INT64_MASK);
    sum += y[0] & BIG_INTEGER_INT64_MASK;
    result[x_index] = (Int32)sum;
  } else {
    /* Add common parts of both numbers */
    while (y_index > 0) {
      x_index -= 1;
      y_index -= 1;
      var x_i = x[x_index] & BIG_INTEGER_INT64_MASK;
      var y_i = y[y_index] & BIG_INTEGER_INT64_MASK;
      sum = x_i + y_i + (Int64)(((UInt64)sum) >> 32);
      result[x_index] = (Int32)sum;
    }
  }

  /* Copy remainder of longer number while carry propagation is required */
  var carry = (((UInt64)sum) >> 32) != 0;
  while (x_index > 0 && carry) {
    x_index -= 1;
    result[x_index] = x[x_index] + 1;
    carry = result[x_index] == 0;
  }

  /* Copy remainder of longer number */
  while (x_index > 0) {
    x_index -= 1;
    result[x_index] = x[x_index];
  }

  /* Grow result if necessary */
  if (carry) {
    var bigger = (Int32*)malloc(sizeof(Int32) * (*result_count + 1));
    memcpy(bigger + 1, result, sizeof(Int32) * (*result_count));
    bigger[0] = 0x01;
    *result_count += 1;
    return bigger;
  }
  return result;
}

/**
 * Subtracts the contents of the second int32 arrays (little) from the first
 * (big). The first int32 array (big) must represent a larger number than the
 * second. This method allocates the space necessary to hold the answer.
 */
static Int32* big_integer_subtract_words(Int32* big,
                                         Int64 big_count,
                                         Int32* little,
                                         Int64 little_count) {
  var big_index = big_count;
  var result = (Int32*)calloc(big_index, sizeof(Int32));
  var little_index = little_count;

  var difference = (Int64)0;

  /* Subtract common parts of both numbers. */
  while (little_index > 0) {
    big_index -= 1;
    little_index -= 1;
    difference >>= 32;
    difference += big[big_index] & BIG_INTEGER_INT64_MASK;
    difference -= little[little_index] & BIG_INTEGER_INT64_MASK;
    result[big_index] = (Int32)difference;
  }

  /* Subtract remainder of longer number while borrow propagates. */
  var borrow = difference >> 32 != 0;
  while (big_index > 0 && borrow) {
    big_index -= 1;
    result[big_index] = big[big_index] - 1;
    borrow = result[big_index] == -1;
  }

  /* Copy remainder of longer number */
  while (big_index > 0) {
    big_index -= 1;
    result[big_index] = big[big_index];
  }

  return result;
}

/**
 * Compares the magnitude array of `lhs` with the `rhs`'s. This is the version
 * of compare() ignoring sign.
 */
static Int64 big_integer_compare_words(struct BigInteger* lhs,
                                       struct BigInteger* rhs) {
  if (lhs->_magnitude_count < rhs->_magnitude_count) {
    return -1;
  }
  if (lhs->_magnitude_count > rhs->_magnitude_count) {
    return 1;
  }
  /* Find the first mismatch index */
  var i = -1;
  var k = 0;
  for (; k < lhs->_magnitude_count; k += 1) {
    if (lhs->_magnitude[k] != rhs->_magnitude[k]) {
      i = k;
      break;
    }
  }
  if (i != -1) {
    return (UInt32)lhs->_magnitude[i] < (UInt32)rhs->_magnitude[i] ? -1 : 1;
  }
  return 0;
}

static
struct BigInteger* big_integer_multiply_by_word(Int32* x,
                                                Int64 x_count,
                                                Int32 y,
                                                enum BigIntegerSign sign) {
  /* TODO: special case for left shift */
  //if (__builtin_popcount(y) == 1) {
  //}

  var result = (Int32*)calloc(x_count + 1, sizeof(Int32));
  var result_count = x_count + 1;

  var carry = (Int64)0;
  var y_int64 = y & BIG_INTEGER_INT64_MASK;
  var r_start = x_count;
  var i = x_count - 1;
  for (; i >= 0; i -= 1) {
    var product = (x[i] & BIG_INTEGER_INT64_MASK) * y_int64 + carry;
    result[r_start] = (Int32)product;
    r_start -= 1;
    carry = ((UInt64)product) >> 32;
  }
  if (carry == 0) {
    memmove(result, result + 1, sizeof(Int32) * x_count);
    result_count = x_count;
  } else {
    result[r_start] = (Int32)carry;
  }

  return big_integer_init_from_words(result, result_count, sign, false);
}

/*
 * Multiplies int32 arrays x and y to the specified lengths and places the
 * result into z. There will be no leading zeros in the resultant array.
 */
static Int32* big_integer_multiply_to_count(Int32* x,
                                            Int64 x_count,
                                            Int32* y,
                                            Int64 y_count,
                                            Int64* z_count) {
  var z = (Int32*)calloc(x_count + y_count, sizeof(Int32));
  *z_count = x_count + y_count;

  var x_start = x_count - 1;
  var y_start = y_count - 1;

  var carry = (Int64)0;
  var j = y_start;
  var k = y_start + 1 + x_start;
  for (; j >= 0; j -= 1, k -= 1) {
    var product = y[j] & BIG_INTEGER_INT64_MASK;
    product *= x[x_start] & BIG_INTEGER_INT64_MASK;
    product += carry;
    z[k] = (Int32)product;
    carry = ((UInt64)product) >> 32;
  }
  z[x_start] = (Int32)carry;

  var i = x_start - 1;
  for (; i >= 0; i -= 1) {
    carry = 0;
    for (j = y_start, k = y_start + 1 + i; j >= 0; j -= 1, k -= 1) {
      var product = y[j] & BIG_INTEGER_INT64_MASK;
      product *= x[i] & BIG_INTEGER_INT64_MASK;
      product += (z[k] & BIG_INTEGER_INT64_MASK) + carry;
      z[k] = (Int32)product;
      carry = ((UInt64)product) >> 32;
    }
    z[i] = (Int32)carry;
  }
  return z;
}

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
    value->_magnitude = (Int32*)malloc(sizeof(Int32) * 0);
    return value;
  }

  let digits_count = (Int64)text_count - cursor;

  /*
   * Pre-allocate array of expected size. May be too large but can never be too
   * small. Typically exact.
   */
  var bits_count = ((digits_count * BIG_INTEGER_BITS_PER_DIGIT[radix]) >> 10);
  bits_count += 1;
  /* Add 31 to make sure that count is bigger than 32. */
  let magnitude_count = (bits_count + 31) >> 5;
  value->_magnitude_count = magnitude_count;
  value->_magnitude_capacity = magnitude_count;
  value->_magnitude = (Int32*)calloc(magnitude_count, sizeof(Int32));

  /* Process first (potentially short) digit group. */
  var first_group_count = digits_count % BIG_INTEGER_DIGITS_PER_WORD[radix];
  if (first_group_count == 0) {
    first_group_count = BIG_INTEGER_DIGITS_PER_WORD[radix];
  }
  Char group[32];
  memcpy(group, text + cursor * sizeof(Char), first_group_count);
  group[first_group_count] = '\0';
  cursor += first_group_count;
  value->_magnitude[magnitude_count - 1] = (Int32)strtol(group,
                                                         NULL,
                                                         (Int32)radix);
  precondition(value->_magnitude[magnitude_count - 1] >= 0, "Illegal digit");

  /* Process remaining digit groups */
  let super_radix = BIG_INTEGER_WORD_RADIX[radix];
  var group_value = 0;
  while (cursor < text_count) {
    memcpy(group,
           text + cursor,
           BIG_INTEGER_DIGITS_PER_WORD[radix]);
    group[BIG_INTEGER_DIGITS_PER_WORD[radix]] = '\0';
    cursor += BIG_INTEGER_DIGITS_PER_WORD[radix];
    group_value = (Int32)strtol(group, NULL, (Int32)radix);
    precondition(group_value >= 0, "Illegal digit");
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
  let new_count = big_integer_trusted_strip_leading_zero_words(magnitude,
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
  copy->_magnitude = malloc(sizeof(Int32) * value->_magnitude_capacity);
  memcpy(copy->_magnitude,
         value->_magnitude,
         sizeof(Int32) * value->_magnitude_capacity);
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
   * Plus one again for the null terminator.
   */
  let b = big_integer_bit_count(abs);
  let log_cache_radix = BIG_INTEGER_LOG_CACHE[radix];
  var count = (Int64)floor(b * BIG_INTEGER_LOG_TWO / log_cache_radix) + 1;
  count += value->_sign == minus ? 1 : 0;
  count += 1;

  var text = (Char*)malloc(sizeof(Char) * count);
  var offset = 0;
  if (value->_sign == minus) {
    text[0] = '-';
    offset += 1;
  }
  text[offset] = '\0';

  /* Use recursive toString. */
  big_integer_to_string_schoenhage(abs, text, offset, radix, 0, is_uppercase);

  return text;
}

/* MARK: - Performing Calculations */

/**
 * Adds two values and produces their sum.
 */
struct BigInteger* big_integer_add(struct BigInteger* lhs,
                                   struct BigInteger* rhs) {
  if (rhs->_sign == none) {
    return big_integer_copy(lhs);
  }
  if (lhs->_sign == none) {
    return big_integer_copy(rhs);
  }
  if (lhs->_sign == rhs->_sign) {
    var result_count = (Int64)0;
    var result = big_integer_add_words(lhs->_magnitude,
                                       lhs->_magnitude_count,
                                       rhs->_magnitude,
                                       rhs->_magnitude_count,
                                       &result_count);
    return big_integer_init_from_words(result, result_count, lhs->_sign, false);
  }

  let compare_result = big_integer_compare_words(lhs, rhs);
  if (compare_result == 0) {
    return big_integer_init_from_words(malloc(sizeof(Int32) * 0),
                                       0,
                                       none,
                                       false);
  }

  var result_count = (Int64)0;
  var result = (Int32*)NULL;
  if (compare_result > 0) {
    result = big_integer_subtract_words(lhs->_magnitude,
                                        lhs->_magnitude_count,
                                        rhs->_magnitude,
                                        rhs->_magnitude_count);
    result_count = lhs->_magnitude_count;
  } else {
    result = big_integer_subtract_words(rhs->_magnitude,
                                        rhs->_magnitude_count,
                                        lhs->_magnitude,
                                        lhs->_magnitude_count);
    result_count = rhs->_magnitude_count;
  }
  result_count = big_integer_trusted_strip_leading_zero_words(result,
                                                              result_count);

  var sign = none;
  if ((compare_result > 0 && lhs->_sign == plus) ||
      (compare_result < 0 && lhs->_sign == minus)) {
    sign = plus;
  } else {
    sign = minus;
  }
  return big_integer_init_from_words(result,
                                     result_count,
                                     sign,
                                     false);
}

/**
 * Subtracts one value from another and produces their difference.
 */
struct BigInteger* big_integer_subtract(struct BigInteger* lhs,
                                        struct BigInteger* rhs) {
  if (rhs->_sign == none) {
    return big_integer_copy(lhs);
  }
  if (lhs->_sign == none) {
    var result = big_integer_copy(rhs);
    if (result->_sign == plus) {
      result->_sign = minus;
    } else if (result->_sign == minus) {
      result->_sign = plus;
    }
    return result;
  }
  if (rhs->_sign != lhs->_sign) {
    var result_count = (Int64)0;
    var result = big_integer_add_words(lhs->_magnitude,
                                       lhs->_magnitude_count,
                                       rhs->_magnitude,
                                       rhs->_magnitude_count,
                                       &result_count);
    return big_integer_init_from_words(result, result_count, lhs->_sign, false);
  }

  var compare_result = big_integer_compare_words(lhs, rhs);
  if (compare_result == 0) {
    return big_integer_init_from_words(malloc(sizeof(Int32) * 0),
                                       0,
                                       none,
                                       false);
  }

  var result_count = (Int64)0;
  var result = (Int32*)NULL;
  if (compare_result > 0) {
    result = big_integer_subtract_words(lhs->_magnitude,
                                        lhs->_magnitude_count,
                                        rhs->_magnitude,
                                        rhs->_magnitude_count);
    result_count = lhs->_magnitude_count;
  } else {
    result = big_integer_subtract_words(rhs->_magnitude,
                                        rhs->_magnitude_count,
                                        lhs->_magnitude,
                                        lhs->_magnitude_count);
    result_count = rhs->_magnitude_count;
  }
  result_count = big_integer_trusted_strip_leading_zero_words(result,
                                                              result_count);

  var sign = none;
  if ((compare_result > 0 && lhs->_sign == plus) ||
      (compare_result < 0 && lhs->_sign == minus)) {
    sign = plus;
  } else {
    sign = minus;
  }
  return big_integer_init_from_words(result,
                                     result_count,
                                     sign,
                                     false);
}

/**
 * Multiplies two values and produces their product.
 */
struct BigInteger* big_integer_multiply(struct BigInteger* lhs,
                                        struct BigInteger* rhs) {
  if (lhs->_sign == none || rhs->_sign == none) {
    return big_integer_init_from_words(malloc(sizeof(Int32) * 0),
                                       0,
                                       none,
                                       false);
  }

  /* TODO: special case for square */

//  if (lhs->_magnitude_count < BIG_INTEGER_KARATSUBA_THRESHOLD ||
//      rhs->_magnitude_count < BIG_INTEGER_KARATSUBA_THRESHOLD) {
    var result_sign = lhs->_sign == rhs->_sign ? plus : minus;
    if (rhs->_magnitude_count == 1) {
      return big_integer_multiply_by_word(lhs->_magnitude,
                                          lhs->_magnitude_count,
                                          rhs->_magnitude[0],
                                          result_sign);
    }
    if (lhs->_magnitude_count == 1) {
      return big_integer_multiply_by_word(rhs->_magnitude,
                                          rhs->_magnitude_count,
                                          lhs->_magnitude[0],
                                          result_sign);
    }
    var result_count = (Int64)0;
    var result = big_integer_multiply_to_count(lhs->_magnitude,
                                               lhs->_magnitude_count,
                                               rhs->_magnitude,
                                               rhs->_magnitude_count,
                                               &result_count);
    result_count = big_integer_trusted_strip_leading_zero_words(result,
                                                                result_count);
    return big_integer_init_from_words(result,
                                       result_count,
                                       result_sign,
                                       false);
//  }
}

/**
 * Returns the quotient and remainder of one value divided by another value.
 */
struct BigInteger** big_integer_divide_and_modulo(struct BigInteger* lhs,
                                                  struct BigInteger* rhs) {
  var a = mutable_big_integer_init_from_words(lhs->_magnitude,
                                              lhs->_magnitude_count);
  var b = mutable_big_integer_init_from_words(rhs->_magnitude,
                                              rhs->_magnitude_count);
  var quotient_and_remainder = mutable_big_integer_divide(a, b);
  var q = quotient_and_remainder[0];
  var r = quotient_and_remainder[1];

  var result = (struct BigInteger**)malloc(sizeof(struct BigInteger*) * 2);
  let quotient_sign = lhs->_sign == rhs->_sign ? plus : minus;
  result[0] = big_integer_mutable_big_integer_to_big_integer(q, quotient_sign);
  result[1] = big_integer_mutable_big_integer_to_big_integer(r, lhs->_sign);

  mutable_big_integer_deinit(a);
  mutable_big_integer_deinit(b);
  mutable_big_integer_deinit(q);
  mutable_big_integer_deinit(r);

  return result;
}

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
  var bit_count = ((value->_magnitude_count - 1) << 5);
  bit_count += big_integer_bit_count_for_word((UInt32)value->_magnitude[0]);
  if (value->_sign == minus) {
    /* Check if magnitude is a power of two. */
    var is_pow2 = __builtin_popcount(value->_magnitude[0]) == 1;
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
