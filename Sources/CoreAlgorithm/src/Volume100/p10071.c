/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10071.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 6, 2024                                \ \ \_/__ \_\ \_  __  */
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

#include "Volume100/p10071.h"

/*
 * 10071 Back to High School Physics
 *
 * A particle has initial velocity and acceleration. If its velocity after
 * certain time is v then what will its displacement be in twice of that time?
 *
 * Input:
 * The input will contain two integers in each line. Each line makes one set of
 * input. These two integers denote the value of v (−100 ≤ v ≤ 100) and
 * t (0 ≤ t ≤ 200) (t means at the time the particle gains that velocity)
 *
 * Output:
 * For each line of input print a single integer in one line denoting the
 * displacement in double of that time.
 *
 * Solution:
 * Super simple: output 2 * v * t
 */

Void p10071_main() {
  var v = 0;
  var t = 0;
  while (scanf("%d %d", &v, &t) == 2) {
    printf("%d\n", 2 * v * t);
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
