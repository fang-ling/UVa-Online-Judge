/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10110.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: February 22, 2025                              \ \ \_/__ \_\ \_  __  */
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
 * 10110 Light, more light
 *
 * There is man named "mabu" for switching on-off light in our University. He
 * switches on-off the lights in a corridor. Every bulb has its own toggle
 * switch. That is, if it is pressed then the bulb turns on. Another press will
 * turn it off. To save power consumption (or may be he is mad or something
 * else) he does a peculiar thing. If in a corridor there is n bulbs, he walks
 * along the corridor back and forth n times and in i-th walk he toggles only
 * the switches whose serial is divisable by i. He does not press any switch
 * when coming back to his initial position. A i-th walk is defined as going
 * down the corridor (while doing the peculiar thing) and coming back again. Now
 * you have to determine what is the final condition of the last bulb. Is it on
 * or off?
 *
 * Input:
 * The input will be an integer indicating the n’th bulb in a corridor. Which is
 * less then or equals 2**32 - 1. A zero indicates the end of input. You should
 * not process this input.
 *
 * Output:
 * Output 'yes' if the light is on otherwise 'no', in a single line.
 */

#include "Volume101/p10110.h"

Void p10110_main() {
  var number = (UInt32)0;
  while (scanf("%u", &number) == 1 && number != 0) {
    var square_root = (UInt32)sqrt(number);
    printf("%s\n", square_root * square_root == number ? "yes" : "no");
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
