/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11559.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: November 19, 2024                              \ \ \_/__ \_\ \_  __  */
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
 * 11559 Event Planning
 *
 * As you didn't show up to the yearly general meeting of the Nordic Club of Pin
 * Collectors, you were unanimously elected to organize this years excursion to
 * Pin City. You are free to choose from a number of weekends this autumn, and
 * have to find a suitable hotel to stay at, preferably as cheap as possible.
 *
 * You have some constraints: The total cost of the trip must be within budget,
 * of course. All participants must stay at the same hotel, to avoid last years
 * catastrophe, where some members got lost in the city, never being seen again.
 *
 * Input:
 * The input file contains several test cases, each of them as described below.
 *
 * The first line of input consists of four integers: 1 ≤ N ≤ 200, the number of
 * participants, 1 ≤ B ≤ 500000, the budget, 1 ≤ H ≤ 18, the number of hotels to
 * consider, and 1 ≤ W ≤ 13, the number of weeks you can choose between. Then
 * follow two lines for each of the H hotels. The first gives 1 ≤ p ≤ 10000, the
 * price for one person staying the weekend at the hotel. The second contains W
 * integers, 0 ≤ a ≤ 1000, giving the number of available beds for each weekend
 * at the hotel.
 *
 * Output:
 * For each test case, write to the output the minimum cost of the stay for your
 * group, or "stay home" if nothing can be found within the budget, on a line by
 * itself.
 *
 * Solution:
 * Simple greedy algorithm.
 */

#include "Volume115/p11559.h"

Void p11559_main() {
  var participant_count = 0;
  var budget = 0;
  var hotel_count = 0;
  var week_count = 0;
  while (
    scanf(
      "%d %d %d %d",
      &participant_count,
      &budget,
      &hotel_count,
      &week_count
    ) == 4
  ) {
    var result = INT32_MAXIMUM;

    var i = 0;
    for(; i < hotel_count; i += 1) {
      var price = 0; /* price per person */
      scanf("%d", &price);

      var j = 0;
      for(; j < week_count; j += 1) {
        var bed_count = 0;
        scanf("%d", &bed_count);

        if (bed_count >= participant_count) {
          result = min(result, price * participant_count);
        }
      }
    }
    if (result <= budget) {
      printf("%d\n", result);
    } else {
      printf("stay home\n");
    }
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
