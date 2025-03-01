/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11332.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 23, 2024                               \ \ \_/__ \_\ \_  __  */
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
 
/*
 * 11332 Summing Digits
 *
 * For a positive integer n, let f(n) denote the sum of the digits of n when
 * represented in base 10. It is easy to see that the sequence of numbers
 * n, f(n), f(f(n)), f(f(f(n))), ... eventually becomes a single digit number
 * that repeats forever. Let this single digit be denoted g(n).
 *
 * For example, consider n = 1234567892. Then:
 *   f(n) = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 2 = 47
 *   f(f(n)) = 4 + 7 = 11
 *   f(f(f(n))) = 1 + 1 = 2
 * Therefore, g(1234567892) = 2.
 *
 * Input:
 * Each line of input contains a single positive integer n at most
 * 2,000,000,000. Input is terminated by n = 0 which should not be processed.
 *
 * Output:
 * For each such integer, you are to output a single line containing g(n).
 *
 * Solution:
 * Simple recursion.
 */

#include "Volume113/p11332.h"

Int64 p11332_f(Int64 n) {
  var sum = 0ll;
  while (n > 0) {
    sum += n % 10;
    n /= 10;
  }
  return sum < 10 ? sum : p11332_f(sum);
}

Void p11332_main() {
  var n = 0;
  while (scanf("%d", &n) == 1 && n != 0) {
    printf("%lld\n", p11332_f(n));
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
