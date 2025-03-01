/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p12468.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: December 9, 2024                               \ \ \_/__ \_\ \_  __  */
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
 * 12468 Zapping
 *
 * I'm a big fan of watching TV. However, I don't like to watch a single
 * channel; I'm constantly zapping between different channels.
 *
 * My dog tried to eat my remote controller and unfortunately he partially
 * destroyed it. The numeric buttons I used to press to quickly change channels
 * are not working anymore. Now, I only have available two buttons to change
 * channels: one to go up to the next channel (the △ button) and one to go down
 * to the previous channel (the ▽ button). This is very annoying because if I'm
 * watching channel 3 and want to change to channel 9 I have to press the △
 * button 6 times!
 *
 * My TV has 100 channels conveniently numbered 0 through 99. They are cyclic,
 * in the sense that if I'm on channel 99 and press △ I'll go to channel 0.
 * Similarly, if I'm on channel 0 and press ▽ I'll change to channel 99.
 *
 * I would like a program that, given the channel I'm currently watching and the
 * channel I would like to change to, tells me the minimum number of button
 * presses I need to reach that channel.
 *
 * Input:
 * The input contains several test cases (at most 200).
 * Each test case is described by two integers a and b in a single line. a is
 * the channel I'm currently watching and b is the channel I would like to go to
 * (0 ≤ a, b ≤ 99).
 * The last line of the input contains two '-1's and should not be processed.
 *
 * Output:
 * For each test case, output a single integer on a single line — the minimum
 * number of button presses needed to reach the new channel (Remember, the only
 * two buttons I have available are △ and ▽).
 *
 * Solution:
 * Find the minimum distance between two points on a circle with a perimeter of
 * 100.
 *
 * compare b - a with 100 - (b - a)
 *         ....
 *     ..        ..
 *   .              .
 *  .                .
 * .                  .
 * .                  .
 *  .                .
 *   .              .
 *     ..        ..
 *    a    ....    b
 */

#include "Volume124/p12468.h"

Void p12468_main() {
  var a = 0;
  var b = 0;
  while (scanf("%d %d", &a, &b) == 2 && a != -1 && b != -1) {
    printf("%d\n", min(abs(b - a), 100 - abs(b - a)));
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
