/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11764.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 15, 2024                               \ \ \_/__ \_\ \_  __  */
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
 * 11764 Jumping Mario
 *
 * Mario is in the final castle. He now needs to jump over few walls and then
 * enter the Koopa’s Chamber where he has to defeat the monster in order to save
 * the princess. For this problem, we are only concerned with the "jumping over
 * the wall" part. You will be given the heights of N walls from left to right.
 * Mario is currently standing on the first wall. He has to jump to the adjacent
 * walls one after another until he reaches the last one. That means, he will
 * make (N − 1) jumps. A high jump is one where Mario has to jump to a taller
 * wall, and similarly, a low jump is one where Mario has to jump to a shorter
 * wall. Can you find out the total number of high jumps and low jumps Mario has
 * to make?
 *
 * Input:
 * The first line of input is an integer T (T < 30) that indicates the number of
 * test cases. Each case starts with an integer N (0 < N < 50) that determines
 * the number of walls. The next line gives the height of the N walls from left
 * to right. Each height is a positive integer not exceeding 10.
 *
 * Output:
 * For each case, output the case number followed by 2 integers, total high
 * jumps and total low jumps, respectively. Look at the sample for exact format.
 *
 * Solution:
 * A linear scan to count high and low jumps.
 */

#include "Volume117/p11764.h"

Void p11764_main() {
  Int64 walls[64];
  
  var case_count = 0;
  scanf("%d", &case_count);
  var i = 0;
  for (i = 1; i <= case_count; i += 1) {
    var n = 0;
    scanf("%d", &n);
    var j = 0;
    for (j = 0; j < n; j += 1) {
      scanf("%lld", &walls[j]);
    }
    
    var high = 0;
    var low = 0;
    for (j = 0; j + 1 < n; j += 1) {
      if (walls[j] > walls[j + 1]) {
        low += 1;
      } else if (walls[j] < walls[j + 1]) {
        high += 1;
      }
    }
    
    printf("Case %d: %d %d\n", i, high, low);
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
