/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p591.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: January 30, 2025                               \ \ \_/__ \_\ \_  __  */
/*                                                       \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the hxy open source project.
 *
 * Copyright (c) 2024-2025 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */

/*
 * 591 Box of Bricks
 *
 * Little Bob likes playing with his box of bricks. He puts the bricks one upon
 * another and builds stacks of different height. "Look, I've built a wall!", he
 * tells his older sister Alice. "Nah, you should make all stacks the same
 * height. Then you would have a real wall.", she retorts. After a little
 * consideration, Bob sees that she is right. So he sets out to rearrange the
 * bricks, one by one, such that all stacks are the same height afterwards. But
 * since Bob is lazy he wants to do this with the minimum number of bricks
 * moved. Can you help?
 *
 * Input:
 * The input consists of several data sets. Each set begins with a line
 * containing the number n of stacks Bob has built. The next line contains n
 * numbers, the heights hi of the n stacks. You may assume 1 ≤ n ≤ 50 and
 * 1 ≤ hi ≤ 100.
 * The total number of bricks will be divisible by the number of stacks. Thus,
 * it is always possible to rearrange the bricks such that all stacks have the
 * same height.
 * The input is terminated by a set starting with n = 0. This set should not be
 * processed.
 *
 * Output:
 * For each set, first print the number of the set, as shown in the sample
 * output. Then print the line 'The minimum number of moves is k.', where k is
 * the minimum number of bricks that have to be moved in order to make all the
 * stacks the same height.
 * Output a blank line after each set.
 */

#include "Volume5/p591.h"

Void p591_main() {
  var block_height = (Int32*)malloc(sizeof(Int32) * 64);

  var set_count = 0;
  var stack_count = 0;
  while (scanf("%d", &stack_count) == 1 && stack_count != 0) {
    var average = 0;

    var i = 0;
    for (; i < stack_count; i += 1) {
      scanf("%d", &block_height[i]);
      average += block_height[i];
    }
    average /= stack_count;

    var sum = 0;
    for (i = 0; i < stack_count; i += 1) {
      sum += abs(block_height[i] - average);
    }

    set_count += 1;
    printf("Set #%d\n", set_count);
    printf("The minimum number of moves is %d.\n\n", sum / 2);
  }

  free(block_height);
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
