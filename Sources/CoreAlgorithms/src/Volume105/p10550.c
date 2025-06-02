/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10550.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: May 20, 2025                                   \ \ \_/__ \_\ \_  __  */
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
 * 10550 Combination Lock
 *
 * Now that you're back to school for another term, you need to remember how to
 * work the combination lock on your locker. A common design is that of the
 * Master Brand, shown at right. The lock has a dial with 40 calibration marks
 * numbered 0 to 39. A combination consists of 3 of these numbers; for example:
 * 15-25-8. To open the lock, the following steps are taken:
 *
 *   1. turn the dial clockwise 2 full turns
 *   2. stop at the first number of the combination
 *   3. turn the dial counter-clockwise 1 full turn
 *   4. continue turning counter-clockwise until the 2nd number is reached
 *   5. turn the dial clockwise again until the 3rd number is reached
 *   6. pull the shank and the lock will open.
 *
 * Given the initial position of the dial and the combination for the lock, how
 * many degrees is the dial rotated in total (clockwise plus counter-clockwise)
 * in opening the lock?
 *
 * Input:
 * Input consists of several test cases. For each case there is a line of input
 * containing 4 numbers between 0 and 39. The first number is the position of
 * the dial. The next three numbers are the combination. Consecutive numbers in
 * the combination will be distinct. A line containing '0 0 0 0' follows the
 * last case.
 *
 * Output:
 * For each case, print a line with a single integer: the number of degrees that
 * the dial must be turned to open the lock.
 */

#include "Volume105/p10550.h"

Void p10550_main() {
  var start = 0;
  var combination = (Int32*)malloc(sizeof(Int32) * 3);

  while (true) {
    scanf("%d", &start);
    scanf("%d %d %d", &combination[0], &combination[1], &combination[2]);
    if (start == 0 && combination[0] + combination[1] + combination[2] == 0) {
      break;
    }

    var result = 0;
    /* Step 1. */
    result += 720;
    /* Step 2. */
    result += (start - combination[0] + 40) % 40 * 360 / 40;
    /* Step 3. */
    result += 360;
    /* Step 4. */
    result += (combination[1] - combination[0] + 40) % 40 * 360 / 40;
    /* Step 5. */
    result += (combination[1] - combination[2] + 40) % 40 * 360 / 40;

    printf("%d\n", result);
  }

  free(combination);
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
