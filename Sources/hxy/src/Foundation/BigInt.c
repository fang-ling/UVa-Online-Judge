/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* BigInt.c                                             /'___\ /\_ \          */
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
 
#include "Foundation/BigInt.h"

/*
 * ceil(log2(radix) * 1024)
 * bitsPerDigit in the given radix times 1024.
 * Rounded up to avoid underallocation.
 */
Int32 BIG_INT_BITS_PER_DIGIT[] = {
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
Int32 BIG_INT_DIGITS_PER_UINT64[] = {
   0,  0, 63, 40, 31, 27, /*  0 ...  5 */
  24, 22, 21, 20, 19, 18, /*  6 ... 11 */
  17, 17, 16, 16, 15, 15, /* 12 ... 17 */
  15, 15, 14, 14, 14, 14, /* 18 ... 23 */
  13, 13, 13, 13, 13, 13, /* 24 ... 29 */
  13, 12, 12, 12, 12, 12, /* 30 ... 35 */
  12                      /* 36 */
};

UInt64 BIG_INT_UINT64_RADIX[] = {
  0x0000000000000000ull,
  0x0000000000000000ull,
  0x8000000000000000ull,
  0xa8b8b452291fe821ull,
  0x4000000000000000ull,
  0x6765c793fa10079dull,
  0x41c21cb8e1000000ull,
  0x3642798750226111ull,
  0x8000000000000000ull,
  0xa8b8b452291fe821ull,
  0x8ac7230489e80000ull,
  0x4d28cb56c33fa539ull,
  0x1eca170c00000000ull,
  0x780c7372621bd74dull,
  0x1e39a5057d810000ull,
  0x5b27ac993df97701ull,
  0x1000000000000000ull,
  0x27b95e997e21d9f1ull,
  0x5da0e1e53c5c8000ull,
  0xd2ae3299c1c4aedbull,
  0x16bcc41e90000000ull,
  0x2d04b7fdd9c0ef49ull,
  0x5658597bcaa24000ull,
  0xa0e2073737609371ull,
  0x0c29e98000000000ull,
  0x14adf4b7320334b9ull,
  0x226ed36478bfa000ull,
  0x383d9170b85ff80bull,
  0x5a3c23e39c000000ull,
  0x8e65137388122bcdull,
  0xdd41bb36d259e000ull,
  0x0aee5720ee830681ull,
  0x1000000000000000ull,
  0x172588ad4f5f0981ull,
  0x211e44f7d02c1000ull,
  0x2ee56725f06e5c71ull,
  0x41c21cb8e1000000ull
};

/* Multiply x array times word y in place, and add word z. */
static Void big_int_destructive_multiply_add(UInt64* x,
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

/**
 * Creates a new `BigInt` value from the given string and radix.
 */
struct BigInt* big_int_init(Char* text, Int64 radix) {
  var cursor = 0;
  var text_count = strlen(text);

  precondition(radix >= 2 && radix <= 36, "Radix out of range");
  precondition(text_count > 0, "Zero length BigInt");

  var bigInt = (struct BigInt*)malloc(sizeof(struct BigInt));

  /* Check for at most one leading sign. */
  bigInt->_sign = plus;
  let index1 = (Int64)(strrchr(text, '-') - text); /* lastIndexOf */
  let index2 = (Int64)(strrchr(text, '+') - text); /* lastIndexOf */
  if (index1 >= 0) {
    precondition(index1 == 0 && index2 < 0, "Illegal embedded sign character");
    bigInt->_sign = minus;
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
    bigInt->_sign = none;
    bigInt->_magnitude_count = 1;
    bigInt->_magnitude = (UInt64*)malloc(sizeof(UInt64) * 1);
    return bigInt;
  }
  let digits_count = (Int64)text_count - cursor;

  /*
   * Pre-allocate array of expected size. May be too large but can never be too
   * small. Typically exact.
   */
  let bits_count = ((digits_count * BIG_INT_BITS_PER_DIGIT[radix]) >> 10) + 1;
  /* Add 63 to make sure that count is bigger than 64. */
  let magnitude_count = (bits_count + 63) >> 6;
  bigInt->_magnitude_count = magnitude_count;
  bigInt->_magnitude = (UInt64*)malloc(sizeof(UInt64) * magnitude_count);

  /* Process first (potentially short) digit group. */
  var first_group_count = digits_count % BIG_INT_DIGITS_PER_UINT64[radix];
  if (first_group_count == 0) {
    first_group_count = BIG_INT_DIGITS_PER_UINT64[radix];
  }
  Char group[64];
  memcpy(group, text + cursor * sizeof(Char), first_group_count);
  group[first_group_count] = '\0';
  cursor += first_group_count;
  bigInt->_magnitude[magnitude_count - 1] = ansi_strtoull(group,
                                                          NULL,
                                                          (Int32)radix);
  /* Process remaining digit groups */
  let super_radix = BIG_INT_UINT64_RADIX[radix];
  var group_value = 0ull;
  while (cursor < text_count) {
    memcpy(group,
           text + cursor * sizeof(Char),
           BIG_INT_DIGITS_PER_UINT64[radix]);
    group[BIG_INT_DIGITS_PER_UINT64[radix]] = '\0';
    cursor += BIG_INT_DIGITS_PER_UINT64[radix];
    group_value = ansi_strtoull(group, NULL, (Int32)radix);
    big_int_destructive_multiply_add(bigInt->_magnitude,
                                     bigInt->_magnitude_count,
                                     super_radix,
                                     group_value);
  }

  /*
   * Required for cases where the array was overallocated.
   * Remove leading zeros.
   */
  var count = bigInt->_magnitude_count;
  var keep = 0;
  /* Find first nonzero byte. */
  for (; keep < count && bigInt->_magnitude[keep] == 0; keep += 1);
  if (keep != 0) {
    bigInt->_magnitude_count = count - keep;

    /* Copy value[keep ..< count] */
    let magnitude = (UInt64*)malloc(bigInt->_magnitude_count * sizeof(UInt64));
    memcpy(magnitude,
           bigInt->_magnitude,
           bigInt->_magnitude_count * sizeof(UInt64));
    free(bigInt->_magnitude);
    bigInt->_magnitude = magnitude;
  }
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
