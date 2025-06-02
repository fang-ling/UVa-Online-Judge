/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10812.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: March 30, 2025                                 \ \ \_/__ \_\ \_  __  */
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
 * 10812 Beat the Spread!
 *
 * Superbowl Sunday is nearly here. In order to pass the time waiting for the
 * half-time commercials and wardrobe malfunctions, the local hackers have
 * organized a betting pool on the game. Members place their bets on the sum of
 * the two final scores, or on the absolute difference between the two scores.
 *
 * Given the winning numbers for each type of bet, can you deduce the final
 * scores?
 *
 * Input:
 * The first line of input contains n, the number of test cases. n lines follow,
 * each representing a test case. Each test case gives s and d, non-negative
 * integers representing the sum and (absolute) difference between the two final
 * scores.
 *
 * Output:
 * For each test case, output a line giving the two final scores, largest first.
 * If there are no such scores, output a line containing "impossible". Recall
 * that football scores are always non-negative integers.
 */

#include "Volume108/p10812.h"

Void p10812_main() {
  var case_count = 0;
  scanf("%d", &case_count);

  while (case_count--) {
    var sum = (Int64)0;
    var difference = (Int64)0;
    scanf("%lld %lld", &sum, &difference);

    /* Case1: a - b >= 0 */
    var a = (sum + difference) / 2;
    var b = sum - a;
    if (a >= 0 && b >= 0 && (sum + difference) % 2 == 0) {
      printf("%lld %lld\n", _max(a, b), _min(a, b));
      continue;
    }

    /* Case2: a - b < 0 */
    b = (sum + difference) / 2;
    a = sum - b;
    if (a >= 0 && b >= 0 && (sum + difference) % 2 == 0) {
      printf("%lld %lld\n", _max(a, b), _min(a, b));
      continue;
    }

    /* Case3: impossible */
    printf("impossible\n");
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
