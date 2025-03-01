/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10783.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: February 12, 2025                              \ \ \_/__ \_\ \_  __  */
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
 * 10783 Odd Sum
 *
 * Given a range [a, b], you are to find the summation of all the odd integers
 * in this range. For example, the summation of all the odd integers in the
 * range [3, 9] is 3 + 5 + 7 + 9 = 24.
 *
 * Input:
 * There can be at multiple test cases. The first line of input gives you the
 * number of test cases, T (1 ≤ T ≤ 100). Then T test cases follow. Each test
 * case consists of 2 integers a and b (0 ≤ a ≤ b ≤ 100) in two separate lines.
 *
 * Output:
 * For each test case you are to print one line of output – the serial number of
 * the test case followed by the summation of the odd integers in the range
 * [a, b].
 */

#include "Volume107/p10783.h"

Void p10783_main() {
  var case_count = 0;
  scanf("%d", &case_count);

  var case_number = 1;
  for (; case_number <= case_count; case_number += 1) {
    var left = 0;
    var right = 0;
    scanf("%d %d", &left, &right);

    var sum = 0;
    var k = left;
    for (; k <= right; k += 1) {
      if (k % 2 != 0) {
        sum += k;
      }
    }

    printf("Case %d: %d\n", case_number, sum);
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
