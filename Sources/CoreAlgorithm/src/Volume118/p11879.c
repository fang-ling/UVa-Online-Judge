/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11879.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: January 18, 2025                               \ \ \_/__ \_\ \_  __  */
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
 * 11879 Multiple of 17
 *
 * Theorem: If you drop the last digit d of an integer n (n ≥ 10), subtract 5d
 * from the remaining integer, then the difference is a multiple of 17 if and
 * only if n is a multiple of 17.
 *
 * For example, 34 is a multiple of 17, because 3-20=-17 is a multiple of 17;
 * 201 is not a multiple of 17, because 20-5=15 is not a multiple of 17.
 *
 * Given a positive integer n, your task is to determine whether it is a
 * multiple of 17.
 *
 * Input:
 * There will be at most 10 test cases, each containing a single line with an
 * integer n (1 ≤ n ≤ 10**100). The input terminates with n = 0, which should
 * not be processed.
 *
 * Output:
 * For each case, print 1 if the corresponding integer is a multiple of 17,
 * print 0 otherwise.
 *
 * Solution:
 * A / B problem (BigInteger ver.)
 */

#include "Volume118/p11879.h"

Void p11879_main() {
  var seventeen = big_integer_init_from_string("17", 10);

  Int8 buffer[128];
  while (scanf("%s", buffer) == 1) {
    if (strlen(buffer) == 1 && buffer[0] == '0') { /* End of input */
      break;
    }

    var number = big_integer_init_from_string(buffer, 10);
    var quotient_and_remainder = big_integer_divide_and_modulo(number,
                                                               seventeen);

    if (quotient_and_remainder[1]->_sign == none) {
      printf("1\n");
    } else {
      printf("0\n");
    }

    big_integer_deinit(quotient_and_remainder[0]);
    big_integer_deinit(quotient_and_remainder[1]);
    big_integer_deinit(number);
  }

  big_integer_deinit(seventeen);
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
