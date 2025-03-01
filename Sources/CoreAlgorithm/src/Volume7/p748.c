/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p748.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: January 20, 2025                               \ \ \_/__ \_\ \_  __  */
/*                                                       \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the CoreAlgorithm open source project.
 *
 * Copyright (c) 2024-2025 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */

/*
 * 748 Exponentiation
 *
 * Problems involving the computation of exact values of very large magnitude
 * and precision are common. For example, the computation of the national debt
 * is a taxing experience for many computer systems.
 *
 * This problem requires that you write a program to compute the exact value of
 * R**n where R is a real number (0.0 < R < 99.999) and n is an integer such
 * that 0 < n ≤ 25.
 *
 * Input:
 * The input will consist of a set of pairs of values for R and n. The R value
 * will occupy columns 1 through 6, and the n value will be in columns 8 and 9.
 *
 * Output:
 * The output will consist of one line for each line of input giving the exact
 * value of R**n. Leading zeros and insignificant trailing zeros should be
 * suppressed in the output.
 *
 * Solution:
 * R**n = (R*100/100)**n = (100R)**n / 100**n
 */

#include "Volume7/p748.h"

Void p748_main() {
  var ZEROS = "00000000";

  Char buffer[8];
  Char buffer2[512];
  var n = 0;

  while (scanf("%s %d", buffer, &n) == 2) {
    /* Compute R * 100 */
    var index = strchr(buffer, '.') - buffer;
    memmove(buffer + index, buffer + index + 1, strlen(buffer) - index);

    var r100 = big_integer_init_from_string(buffer, 10);
    var r100_original = big_integer_copy(r100);

    index = strlen(buffer) - index;
    buffer2[0] = '1';
    buffer2[1] = '\0';
    strncat(buffer2, ZEROS, index);

    var zero_count = index;
    n -= 1;
    while (n--) {
      var delta = big_integer_multiply(r100, r100_original);
      big_integer_deinit(r100);
      r100 = delta;

      strncat(buffer2, ZEROS, index);
      zero_count += index;
    }
    var hundred_n = big_integer_init_from_string(buffer2, 10);

    var tmp1 = big_integer_to_string(r100, 10, false);

    var quotient_and_remainder = big_integer_divide_and_modulo(r100, hundred_n);
    var integer = big_integer_to_string(quotient_and_remainder[0], 10, false);
    var fraction = big_integer_to_string(quotient_and_remainder[1], 10, false);
    if (integer[0] != '0') {
      printf("%s", integer);
    }
    printf(".");
    /* Leading zeros */
    if (strlen(fraction) < zero_count) {
      var difference = zero_count - strlen(fraction);
      while (difference--) {
        printf("0");
      }
    }
    /* Trailing zeros */
    var i = strlen(fraction) - 1;
    for (; i >= 0 && fraction[i] == '0'; i -= 1) {
      fraction[i] = '\0';
    }
    printf("%s\n", fraction);

    big_integer_deinit(r100_original);
    free(integer);
    free(fraction);
    big_integer_deinit(quotient_and_remainder[0]);
    big_integer_deinit(quotient_and_remainder[1]);
    big_integer_deinit(hundred_n);
    big_integer_deinit(r100);
    free(quotient_and_remainder);
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
