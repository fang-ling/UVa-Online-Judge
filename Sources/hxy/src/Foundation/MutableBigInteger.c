/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* MutableBigInteger.c                                  /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: December 14, 2024                              \ \ \_/__ \_\ \_  __  */
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

#include "Foundation/MutableBigInteger.h"

/* MARK: - Private Constants */

/*
 * This mask is used to obtain the value of an int32 as if it were unsigned.
 */
#define MUTABLE_BIG_INTEGER_INT64_MASK 0xffffffffll

/*
 * The threshold value for using Burnikel-Ziegler division. If the number of
 * words in the divisor are larger than this value, Burnikel-Ziegler division
 * may be used. This value is found experimentally to work well.
 */
#define MUTABLE_BIG_INTEGER_BURNIKEL_ZIEGLER_THRESHOLD 80

/*
 * The offset value for using Burnikel-Ziegler division. If the number of words
 * in the divisor exceeds the Burnikel-Ziegler threshold, and the number of
 * words in the dividend is greater than the number of words in the divisor plus
 * this value, Burnikel-Ziegler division will be used. This value is found
 * experimentally to work well.
 */
#define MUTABLE_BIG_INTEGER_BURNIKEL_ZIEGLER_OFFSET 40

/*
 * The minimum magnitude count for cancelling powers of two before dividing.
 * If the number of words is less than this threshold, `divide_knuth` does not
 * eliminate common powers of two from the dividend and divisor.
 */
#define MUTABLE_BIG_INTEGER_KNUTH_POW2_THRESHOLD_COUNT 6

/*
 * The minimum number of trailing zero ints for cancelling powers of two before
 * dividing.
 * If the dividend and divisor don't share at least this many zero words at the
 * end, `divide_knuth` does not eliminate common powers of two from the dividend
 * and divisor.
 */
#define MUTABLE_BIG_INTEGER_KNUTH_POW2_THRESHOLD_ZEROS 3

/* MARK: - Private methods */

/*
 * Ensure that the MutableBigInteger is in normal form, specifically making sure
 * that there are no leading zeros, and that if the magnitude is zero, then
 * magnitude_count is zero.
 */
static Void mutable_big_integer_normalize(struct MutableBigInteger* value) {
  if (value->_magnitude_count == 0) {
    value->_offset = 0;
    return;
  }

  var index = value->_offset;
  if (value->_magnitude[index] != 0) {
    return;
  }

  var index_bound = index + value->_magnitude_count;
  do {
    index += 1;
  } while (index < index_bound && value->_magnitude[index] == 0);

  var zeros_count = index - value->_offset;
  value->_magnitude_count -= zeros_count;
  if (value->_magnitude_count == 0) {
    value->_offset = 0;
  } else {
    value->_offset += zeros_count;
  }
}

/*
 * This method is used for division of an n word dividend by a one word divisor.
 */
static Void
mutable_big_integer_divide_one_word(struct MutableBigInteger* dividend,
                                    Int32 divisor,
                                    struct MutableBigInteger* quotient,
                                    Int32* remainder) {
  /* Special case of one word dividend. */
  if (dividend->_magnitude_count == 1) {
    var dividend_value = dividend->_magnitude[dividend->_offset];
    var q = dividend_value / divisor;
    var r = dividend_value % divisor;

    quotient->_magnitude[0] = q;
    quotient->_magnitude_count = q == 0 ? 0 : 1;
    quotient->_offset = 0;
    *remainder = r;

    return;
  }

  if (quotient->_magnitude_capacity < dividend->_magnitude_count) {
    let size = sizeof(Int32) * dividend->_magnitude_count;
    quotient->_magnitude = realloc(quotient->_magnitude, size);
  }
  quotient->_offset = 0;
  quotient->_magnitude_count = dividend->_magnitude_count;

  var r = (UInt64)0;
  var x_count = dividend->_magnitude_count;
  for (; x_count > 0; x_count -= 1) {
    var dividend_estimate = r << 32;
    let index = dividend->_offset + dividend->_magnitude_count - x_count;
    let temp = dividend->_magnitude[index] & MUTABLE_BIG_INTEGER_INT64_MASK;
    dividend_estimate |= temp;

    var q = (Int32)(dividend_estimate / divisor);
    r = (UInt64)dividend_estimate % (UInt64)divisor;

    quotient->_magnitude[dividend->_magnitude_count - x_count] = q;
  }

  mutable_big_integer_normalize(quotient);
  *remainder = (Int32)r;
}

/*
 * Left shift the MutableBigInteger n bits, where n is less than 32, placing
 * the result in the specified array.
 * Assumes that magnitude_count > 0, n > 0 for speed.
 */
static Void
mutable_big_integer_primitive_left_shift(struct MutableBigInteger* value,
                                         Int64 n,
                                         Int32* result,
                                         Int64 starting) {
  var n2 = 32 - n;
  let count = value->_magnitude_count - 1;
  var b = value->_magnitude[value->_offset];
  var i = 0;
  for (; i < count; i += 1) {
    var c = value->_magnitude[value->_offset + i + 1];
    result[starting + i] = (b << n) | (((UInt32)c) >> n2);
    b = c;
  }
  result[starting + count] = b << n;
}

/*
 * Right shift this MutableBigInteger n bits, where n is
 * less than 32, placing the result in the specified array.
 * Assumes that intLen > 0, n > 0 for speed.
 */
static Void
mutable_big_integer_primitive_right_shift(struct MutableBigInteger* value,
                                          Int64 n,
                                          Int32* result,
                                          Int64 starting) {
  var n2 = 32 - n;
  var b = value->_magnitude[value->_offset];
  result[starting] = ((UInt32)b) >> n;
  var i = 1;
  for (; i < value->_magnitude_count; i += 1) {
    var c = b;
    b = value->_magnitude[value->_offset + i];
    result[starting + i] = (c << n2) | (((UInt32)b) >> n);
  }
}

/*
 * This method is used for division. It multiplies an n word input a by one word
 * input x, and subtracts the n word product from q. This is needed when
 * subtracting qhat*divisor from dividend.
 */
static Int32 mutable_big_integer_mulsub(Int32* q,
                                        Int32* a,
                                        Int32 x,
                                        Int64 count,
                                        Int64 offset) {
  var x_int64 = x & MUTABLE_BIG_INTEGER_INT64_MASK;
  var carry = (Int64)0;
  offset += count;

  var j = count - 1;
  for (; j >= 0; j -= 1) {
    var product = (a[j] & MUTABLE_BIG_INTEGER_INT64_MASK) * x_int64 + carry;
    var difference = q[offset] - product;
    q[offset] = (Int32)difference;
    offset -= 1;

    let difference_int64 = difference & MUTABLE_BIG_INTEGER_INT64_MASK;
    let product_int64 = (~(Int32)product) & MUTABLE_BIG_INTEGER_INT64_MASK;
    carry = (UInt64)product >> 32;
    carry += difference_int64 > product_int64 ? 1 : 0;
  }

  return (Int32)carry;
}

/*
 * A primitive used for division. This method adds in one multiple of the
 * divisor a back to the dividend result at a specified offset. It is used when
 * qhat was estimated too large, and must be adjusted.
 */
static Int32 mutable_big_integer_divadd(Int32* a,
                                        Int64 count,
                                        Int32* result,
                                        Int64 offset) {
  var carry = (Int64)0;

  var j = count - 1;
  for (; j >= 0; j -= 1) {
    var sum = a[j] & MUTABLE_BIG_INTEGER_INT64_MASK;
    sum += (result[j + offset] & MUTABLE_BIG_INTEGER_INT64_MASK) + carry;
    result[j + offset] = (Int32)sum;
    carry = (UInt64)sum >> 32;
  }

  return (Int32)carry;
}

/* Divide this MutableBigInteger by the divisor. */
static Void
mutable_big_integer_divide_magnitude(struct MutableBigInteger* dividend,
                                     struct MutableBigInteger* divisor,
                                     struct MutableBigInteger* quotient,
                                     struct MutableBigInteger* remainder) {
  /* assert divisor.magnitude_count > 1 */
  /* D1 normalize the divisor */
  let shift = __builtin_clz(divisor->_magnitude[divisor->_offset]);
  /* Copy divisor value to protect divisor */
  let divisor_magnitude_count = divisor->_magnitude_count;
  Int32* divisor_magnitude;
  if (shift > 0) {
    divisor_magnitude = malloc(sizeof(Int32) * divisor_magnitude_count);
    mutable_big_integer_primitive_left_shift(divisor,
                                             shift,
                                             divisor_magnitude,
                                             0);
    if (__builtin_clz(dividend->_magnitude[dividend->_offset]) >= shift) {
      let count = dividend->_magnitude_count + 1;
      var remainder_magnitude = remainder->_magnitude;
      remainder->_magnitude = realloc(remainder_magnitude,
                                      sizeof(Int32) * count);
      remainder->_magnitude_capacity = count;
      remainder->_magnitude_count = dividend->_magnitude_count;
      remainder->_offset = 1;
      mutable_big_integer_primitive_left_shift(dividend,
                                               shift,
                                               remainder->_magnitude,
                                               1);
    } else {
      let count = dividend->_magnitude_count + 2;
      var remainder_magnitude = remainder->_magnitude;
      remainder->_magnitude = realloc(remainder_magnitude,
                                      sizeof(Int32) * count);
      remainder->_magnitude_capacity = count;
      remainder->_magnitude_count = dividend->_magnitude_count + 1;
      remainder->_offset = 1;
      var r_from = dividend->_offset;
      var c = 0;
      var n2 = 32 - shift;
      var i = 1;
      for (; i < dividend->_magnitude_count + 1; i += 1, r_from += 1) {
        var b = c;
        c = dividend->_magnitude[r_from];
        remainder->_magnitude[i] = (b << shift) | ((UInt32)c >> n2);
      }
      let index = dividend->_magnitude_count + 1;
      remainder->_magnitude[index] = c << shift;
    }
  } else {
    divisor_magnitude = malloc(sizeof(Int32) * divisor->_magnitude_count);
    memcpy(divisor_magnitude,
           divisor->_magnitude + divisor->_offset,
           sizeof(Int32) * divisor->_magnitude_count);
    let count = dividend->_magnitude_count + 1;
    var remainder_magnitude = remainder->_magnitude;
    remainder->_magnitude = realloc(remainder_magnitude, sizeof(Int32) * count);
    memcpy(remainder->_magnitude + 1,
           dividend->_magnitude + dividend->_offset,
           dividend->_magnitude_count);
    remainder->_magnitude_count = dividend->_magnitude_count;
    remainder->_magnitude_capacity = count;
    remainder->_offset = 1;
  }

  let n_count = remainder->_magnitude_count;

  /* Set the quotient size */
  let limit = n_count - divisor_magnitude_count + 1;
  if (quotient->_magnitude_capacity < limit) {
    quotient->_magnitude = realloc(quotient->_magnitude,
                                   sizeof(Int32) * limit);
    quotient->_magnitude_capacity = limit;
    quotient->_offset = 0;
  }
  quotient->_magnitude_count = limit;

  /* Insert leading 0 in remainder */
  remainder->_offset = 0;
  remainder->_magnitude[0] = 0;
  remainder->_magnitude_count += 1;

  var dh = divisor_magnitude[0];
  var dh_int64 = dh & MUTABLE_BIG_INTEGER_INT64_MASK;
  var dl = divisor_magnitude[1];

  /* D2 Initialize j */
  var j = 0;
  for (; j < limit - 1; j += 1) {
    /*
     * D3 Calculate qhat
     * estimate qhat
     */
    var qhat = 0;
    var qrem = 0;
    var skip_correction = false;
    var index = j + remainder->_offset;
    var nh = remainder->_magnitude[index];
    var nh2 = (Int32)(nh + 0x80000000);
    var nm = remainder->_magnitude[index + 1];

    if (nh == dh) {
      qhat = ~0;
      qrem = nh + nm;
      skip_correction = (Int32)(qrem + 0x80000000) < nh2;
    } else {
      var n_chunk = (((Int64)nh) << 32) | (nm & MUTABLE_BIG_INTEGER_INT64_MASK);
      qhat = (Int32)((UInt64)n_chunk / (UInt64)dh_int64);
      qrem = (Int32)((UInt64)n_chunk % (UInt64)dh_int64);
    }

    if (qhat == 0) {
      continue;
    }

    if (!skip_correction) { /* Correct qhat */
      index = j + remainder->_offset + 2;
      var nl = remainder->_magnitude[index] & MUTABLE_BIG_INTEGER_INT64_MASK;
      var rs = ((qrem & MUTABLE_BIG_INTEGER_INT64_MASK) << 32) | nl;
      var est_product = dl & MUTABLE_BIG_INTEGER_INT64_MASK;
      est_product *= qhat & MUTABLE_BIG_INTEGER_INT64_MASK;

      if ((UInt64)est_product > (UInt64)rs) {
        qhat -= 1;
        qrem = (Int32)((qrem & MUTABLE_BIG_INTEGER_INT64_MASK) + dh_int64);
        if ((qrem & MUTABLE_BIG_INTEGER_INT64_MASK) >= dh_int64) {
          est_product -= (dl & MUTABLE_BIG_INTEGER_INT64_MASK);
          rs = (((qrem & MUTABLE_BIG_INTEGER_INT64_MASK)) << 32) | nl;
          if ((UInt64)est_product > (UInt64)rs) {
            qhat -= 1;
          }
        }
      }
    }

    /* D4 Multiply and subtract */
    index = j + remainder->_offset;
    remainder->_magnitude[index] = 0;
    var borrow = mutable_big_integer_mulsub(remainder->_magnitude,
                                            divisor_magnitude,
                                            qhat,
                                            divisor_magnitude_count,
                                            index);

    /* D5 Test remainder */
    if ((Int32)(borrow + 0x80000000) > nh2) {
      /* D6 Add back */
      mutable_big_integer_divadd(divisor_magnitude,
                                 divisor_magnitude_count,
                                 remainder->_magnitude,
                                 j + 1 + remainder->_offset);
      qhat -= 1;
    }

    /* Store the quotient digit */
    quotient->_magnitude[j] = qhat;
  } /* D7 loop on j */

  /*
   * D3 Calculate qhat
   * estimate qhat
   */
  var qhat = 0;
  var qrem = 0;
  var skip_correction = false;
  var index = limit - 1 + remainder->_offset;
  var nh = remainder->_magnitude[index];
  var nh2 = (Int32)(nh + 0x80000000);
  var nm = remainder->_magnitude[index + 1];

  if (nh == dh) {
    qhat = ~0;
    qrem = nh + nm;
    skip_correction = (Int32)(qrem + 0x80000000) < nh2;
  } else {
    var n_chunk = (((Int64)nh) << 32) | (nm & MUTABLE_BIG_INTEGER_INT64_MASK);
    qhat = (Int32)((UInt64)n_chunk / (UInt64)dh_int64);
    qrem = (Int32)((UInt64)n_chunk % (UInt64)dh_int64);
  }

  if (qhat != 0) {
    if (!skip_correction) { /* Correct qhat */
      index = limit + 1 + remainder->_offset;
      var nl = remainder->_magnitude[index] & MUTABLE_BIG_INTEGER_INT64_MASK;
      var rs = ((qrem & MUTABLE_BIG_INTEGER_INT64_MASK) << 32) | nl;
      var est_product = dl & MUTABLE_BIG_INTEGER_INT64_MASK;
      est_product *= qhat & MUTABLE_BIG_INTEGER_INT64_MASK;

      if ((UInt64)est_product > (UInt64)rs) {
        qhat -= 1;
        qrem = (Int32)((qrem & MUTABLE_BIG_INTEGER_INT64_MASK) + dh_int64);;
        if ((qrem & MUTABLE_BIG_INTEGER_INT64_MASK) >= dh_int64) {
          est_product -= dl & MUTABLE_BIG_INTEGER_INT64_MASK;
          rs = ((qrem & MUTABLE_BIG_INTEGER_INT64_MASK) << 32) | nl;
          if ((UInt64)est_product > (UInt64)rs) {
            qhat -= 1;
          }
        }
      }
    }

    /* D4 Multiply and subtract */
    index = limit - 1 + remainder->_offset;
    remainder->_magnitude[index] = 0;
    var borrow = mutable_big_integer_mulsub(remainder->_magnitude,
                                            divisor_magnitude,
                                            qhat,
                                            divisor_magnitude_count,
                                            index);

    /* D5 Test remainder */
    if ((Int32)(borrow + 0x80000000) > nh2) {
      /* D6 Add back */
      mutable_big_integer_divadd(divisor_magnitude,
                                 divisor_magnitude_count,
                                 remainder->_magnitude,
                                 limit - 1 + 1 + remainder->_offset);
      qhat -= 1;
    }

    /* Store the quotient digit */
    quotient->_magnitude[limit - 1] = qhat;
  }

  /* D8 Unnormalize */
  if (shift > 0) {
    mutable_big_integer_primitive_right_shift(remainder,
                                              shift,
                                              remainder->_magnitude,
                                              remainder->_offset);
  }
  mutable_big_integer_normalize(quotient);
  mutable_big_integer_normalize(remainder);
}

/*
 * Calculates the quotient of u div v and places the quotient and the remainder
 * object in the provided objects array.
 *
 * Uses Algorithm D from Knuth TAOCP Vol. 2, 3rd edition, section 4.3.1.
 * Many optimizations to that algorithm have been adapted from the Colin Plumb C
 * library.
 * It special cases one word divisors for speed. The content of v is not
 * changed.
 */
static
Void mutable_big_integer_divide_knuth(struct MutableBigInteger* u,
                                      struct MutableBigInteger* v,
                                      struct MutableBigInteger** result) {
  precondition(v->_magnitude_count != 0, "BigInt divide by zero");

  /* Dividend is zero */
  if (u->_magnitude_count == 0) {
    result[0] = mutable_big_integer_init();
    result[1] = mutable_big_integer_init();
    return;
  }

  let compare_result = mutable_big_integer_compare(u, v);
  /* Dividend less than divisor. */
  if (compare_result < 0) {
    result[0] = mutable_big_integer_init();
    result[1] = mutable_big_integer_copy(u);
    return;
  }
  /* Dividend equal to divisor. */
  if (compare_result == 0) {
    result[0] = mutable_big_integer_init_from_int64(1);
    result[1] = mutable_big_integer_init();
    return;
  }

  /* Special case one word divisor */
  if (v->_magnitude_count == 1) {
    result[0] = mutable_big_integer_init();
    var r = 0;
    mutable_big_integer_divide_one_word(u,
                                        v->_magnitude[v->_offset],
                                        result[0],
                                        &r);
    if (r == 0) {
      result[1] = mutable_big_integer_init();
    } else {
      result[1] = mutable_big_integer_init_from_int64(r);
    }
    return;
  }

  /* Cancel common powers of two if we're above the KNUTH_POW2_* thresholds. */
//  if (u->_magnitude_count >= MUTABLE_BIG_INTEGER_KNUTH_POW2_THRESHOLD_COUNT) {
//    let trailing_zero_bits = min(big_int_get_lowest_set_bit(lhs),
//                                 big_int_get_lowest_set_bit(rhs));
// TODO: add left/right shift here
//  }

  result[0] = mutable_big_integer_init();
  result[1] = mutable_big_integer_init();
  mutable_big_integer_divide_magnitude(u, v, result[0], result[1]);
}

/* MARK: - Creating and Destroying a MutableBigInteger */

/**
 * The default constructor. An empty MutableBigInteger is created with a one
 * word capacity.
 */
struct MutableBigInteger* mutable_big_integer_init() {
  var n = (struct MutableBigInteger*)malloc(sizeof(struct MutableBigInteger));

  n->_magnitude = malloc(sizeof(Int32));
  n->_magnitude_capacity = 1;
  n->_magnitude_count = 0;
  n->_offset = 0;

  return n;
}

/**
 * Construct a new MutableBigInteger with a magnitude specified by the int64
 * value.
 */
struct MutableBigInteger* mutable_big_integer_init_from_int64(Int64 value) {
  var n = (struct MutableBigInteger*)malloc(sizeof(struct MutableBigInteger));

  var high_word = (Int32)((UInt64)value >> 32);
  if (high_word == 0) {
    n->_magnitude = malloc(sizeof(Int32));
    n->_magnitude[0] = (Int32)value;
    n->_magnitude_capacity = 1;
    n->_magnitude_count = ((Int32)value) != 0 ? 1 : 0;
    n->_offset = 0;
  } else {
    n->_magnitude = malloc(sizeof(Int32) * 2);
    n->_magnitude[0] = high_word;
    n->_magnitude[1] = (Int32)value;
    n->_magnitude_capacity = 2;
    n->_magnitude_count = 2;
    n->_offset = 0;
  }

  return n;
}

/**
 * Construct a new MutableBigInteger with the specified value array
 * up to the length of the array supplied.
 */
struct MutableBigInteger* mutable_big_integer_init_from_words(Int32* magnitude,
                                                              Int64 count) {
  var n = (struct MutableBigInteger*)malloc(sizeof(struct MutableBigInteger));

  n->_magnitude = malloc(sizeof(Int32) * count);
  memcpy(n->_magnitude, magnitude, sizeof(Int32) * count);
  n->_magnitude_capacity = count;
  n->_magnitude_count = count;
  n->_offset = 0;

  return n;
}

/**
 * Creates a new MutableBigInteger containing the given value.
 */
struct MutableBigInteger*
mutable_big_integer_copy(struct MutableBigInteger* value) {
  var n = (struct MutableBigInteger*)malloc(sizeof(struct MutableBigInteger));

  n->_magnitude = malloc(sizeof(Int32) * value->_magnitude_count);
  n->_magnitude_capacity = value->_magnitude_count;
  memcpy(n->_magnitude,
         value->_magnitude + value->_offset,
         (value->_offset + value->_magnitude_count) * sizeof(Int32));
  n->_magnitude_count = value->_magnitude_count;
  n->_offset = 0;

  return n;
}

/**
 * Destroys a MutableBigInteger.
 */
Void mutable_big_integer_deinit(struct MutableBigInteger* value) {
  if (value == NULL) {
    return;
  }

  free(value->_magnitude);
  free(value);
}

/* MARK: - Performing Calculations */

/**
 * Returns the quotient and remainder of `lhs` divided by the `rhs`.
 */
struct MutableBigInteger**
mutable_big_integer_divide(struct MutableBigInteger* lhs,
                           struct MutableBigInteger* rhs) {
  let element_size = sizeof(struct MutableBigInteger*) * 2;
  var result = (struct MutableBigInteger**)malloc(element_size);

//  let difference = lhs->_magnitude_count - rhs->_magnitude_count;
//  if (rhs->_magnitude_count < MUTABLE_BIG_INTEGER_BURNIKEL_ZIEGLER_THRESHOLD ||
//      difference < MUTABLE_BIG_INTEGER_BURNIKEL_ZIEGLER_OFFSET) {
    mutable_big_integer_divide_knuth(lhs, rhs, result);
//  } else {
//    mutable_big_integer_divide_burnikel_ziegler(lhs, rhs, result);
//  }

  return result;
}

/**
 * Returns -1, 0 or 1 that indicates whether the number object's value is
 * greater than, equal to, or less than a given number.
 */
Int64 mutable_big_integer_compare(struct MutableBigInteger* lhs,
                                  struct MutableBigInteger* rhs) {
  if (lhs->_magnitude_count < rhs->_magnitude_count) {
    return -1;
  }
  if (lhs->_magnitude_count > rhs->_magnitude_count) {
    return 1;
  }

  var i = lhs->_offset;
  var j = rhs->_offset;
  for (; i < lhs->_magnitude_count + lhs->_offset; i += 1, j += 1) {
    /* Unsigned integer comparison. */
    let b1 = (UInt32)lhs->_magnitude[i];
    let b2 = (UInt32)rhs->_magnitude[j];
    if (b1 < b2) {
      return -1;
    }
    if (b1 > b2) {
      return 1;
    }
  }

  return 0;
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
