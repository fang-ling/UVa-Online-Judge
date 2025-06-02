/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p299.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: February 3, 2025                               \ \ \_/__ \_\ \_  __  */
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
 * 299 Train Swapping
 *
 * At an old railway station, you may still encounter one of the last remaining
 * "train swappers". A train swapper is an employee of the railroad, whose sole
 * job it is to rearrange the carriages of trains.
 *
 * Once the carriages are arranged in the optimal order, all the train driver
 * has to do, is drop the carriages off, one by one, at the stations for which
 * the load is meant.
 *
 * The title "train swapper" stems from the first person who performed this
 * task, at a station close to a railway bridge. Instead of opening up
 * vertically, the bridge rotated around a pillar in the center of the river.
 * After rotating the bridge 90 degrees, boats could pass left or right.
 *
 *
 * The first train swapper had discovered that the bridge could be operated with
 * at most two carriages on it. By rotating the bridge 180 degrees, the
 * carriages switched place, allowing him to rearrange the carriages (as a side
 * effect, the carriages then faced the opposite direction, but train carriages
 * can move either way, so who cares).
 *
 * Now that almost all train swappers have died out, the railway company would
 * like to automate their operation. Part of the program to be developed, is a
 * routine which decides for a given train the least number of swaps of two
 * adjacent carriages necessary to order the train. Your assignment is to create
 * that routine.
 *
 * Input:
 * The input contains on the first line the number of test cases (N). Each test
 * case consists of two input lines. The first line of a test case contains an
 * integer L, determining the length of the train (0 ≤ L ≤ 50). The second line
 * of a test case contains a permutation of the numbers 1 through L, indicating
 * the current order of the carriages. The carriages should be ordered such that
 * carriage 1 comes first, then 2, etc. with carriage L coming last.
 *
 * Output:
 * For each test case output the sentence:
 * 'Optimal train swapping takes S swaps.' where S is an integer.
 */

#include "Volume2/p299.h"

Void p299_main() {
  var array = (Int32*)malloc(sizeof(Int32) * 50);

  var n = 0;
  scanf("%d", &n);
  while (n--) {
    var l = 0;
    scanf("%d", &l);

    var i = 0;
    for (; i < l; i += 1) {
      scanf("%d", &array[i]);
    }

    var result = 0;
    for (i = 0; i < l; i += 1) {
      var j = i + 1;
      for (; j < l; j += 1) {
        if (array[i] > array[j]) {
          result += 1;
        }
      }
    }

    printf("Optimal train swapping takes %d swaps.\n", result);
  }

  free(array);
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
