/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p12503.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: November 13, 2024                              \ \ \_/__ \_\ \_  __  */
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
 * 12503 Robot Instructions
 *
 * You have a robot standing on the origin of x axis. The robot will be given
 * some instructions. Your task is to predict its position after executing all
 * the instructions.
 *
 *   - LEFT: move one unit left (decrease p by 1, where p is the position of the
 *     robot before moving)
 *   - RIGHT: move one unit right (increase p by 1)
 *   - SAME AS i: perform the same action as in the i-th instruction. It is
 *     guaranteed that i is a positive integer not greater than the number of
 *     instructions before this.
 *
 * Input:
 * The first line contains the number of test cases T (T ≤ 100). Each test case
 * begins with an integer n (1 ≤ n ≤ 100), the number of instructions. Each of
 * the following n lines contains an instruction.
 *
 * Output:
 * For each test case, print the final position of the robot. Note that after
 * processing each test case, the robot should be reset to the origin.
 *
 * Solution:
 * Simple problem: use an array to store the instructions.
 */

#include "Volume125/p12503.h"

enum P12503Instruction {
  LEFT,
  RIGHT
};

Void p12503_main() {
  enum P12503Instruction instructions[128];
  char instruction[8];
  char dummy[4];

  var case_count = 0;
  scanf("%d", &case_count);

  while (case_count--) {
    var n = 0;
    scanf("%d", &n);

    var p = 0;

    var previous = 0;
    var i = 0;
    for (; i < n; i += 1) {
      scanf("%s", instruction);
      if (instruction[0] == 'L') {
        p -= 1;
        instructions[i] = LEFT;
      } else if (instruction[0] == 'R') {
        p += 1;
        instructions[i] = RIGHT;
      } else {
        scanf("%s %d", dummy, &previous);
        previous -= 1; /* not zero-based */
        var previous_instruction = instructions[previous];
        if (previous_instruction == LEFT) {
          p -= 1;
          instructions[i] = LEFT;
        } else {
          p += 1;
          instructions[i] = RIGHT;
        }
      }
    }

    printf("%d\n", p);
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
