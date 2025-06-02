/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10018.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: March 3, 2025                                  \ \ \_/__ \_\ \_  __  */
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
 * 10018 Reverse and Add
 *
 * The "reverse and add" method is simple: choose a number, reverse its digits
 * and add it to the original. If the sum is not a palindrome (which means, it
 * is not the same number from left to right and right to left), repeat this
 * procedure.
 *                    195    Initial number
 *                    591
 *                    ---
 *                    786
 *                    678
 *                    ---
 *   For example:    1473
 *                   3741
 *                   ----
 *                   5214
 *                   4125
 *                   ----
 *                   9339    Resulting palindrome
 *
 * In this particular case the palindrome '9339' appeared after the 4th
 * addition. This method leads to palindromes in a few step for almost all of
 * the integers. But there are interesting exceptions. 196 is the first number
 * for which no palindrome has been found. It is not proven though, that there
 * is no such a palindrome.
 *
 * You must write a program that give the resulting palindrome and the number of
 * iterations (additions) to compute the palindrome.
 *
 * You might assume that all tests data on this problem:
 *   - will have an answer,
 *   - will be computable with less than 1000 iterations (additions),
 *   - will yield a palindrome that is not greater than 4,294,967,295.
 *
 * Input:
 * The first line will have a number N (0 < N ≤ 100) with the number of test
 * cases, the next N lines will have a number P to compute its palindrome.
 *
 * Output:
 * For each of the N tests you will have to write a line with the following
 * data: minimum number of iterations (additions) to get to the palindrome and
 * the resulting palindrome itself separated by one space.
 */

#include "Volume100/p10018.h"

static Int64 p10018_reverse_int64(Int64 number) {
  var reversed = 0ll;
  while (number != 0) {
    reversed = reversed * 10 + number % 10;
    number /= 10;
  }
  return reversed;
}

Void p10018_main() {
  var case_count = 0;
  scanf("%d", &case_count);

  while (case_count--) {
    var number = 0ll;
    scanf("%lld", &number);

    var reversed = p10018_reverse_int64(number);
    var count = 0;
    do {
      count += 1;
      number += reversed;
      reversed = p10018_reverse_int64(number);
    } while (reversed != number);

    printf("%d %lld\n", count, number);
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
