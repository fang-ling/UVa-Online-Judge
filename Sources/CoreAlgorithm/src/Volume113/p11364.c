/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11364.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: December 25, 2024                              \ \ \_/__ \_\ \_  __  */
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
 * 11364 Optimal Parking
 *
 * When shopping on Long Street, Michael usually parks his car at some random
 * location, and then walks to the stores he needs. Can you help Michael choose
 * a place to park which minimises the distance he needs to walk on his shopping
 * round?
 * Long Street is a straight line, where all positions are integer. You pay for
 * parking in a specific slot, which is an integer position on Long Street.
 * Michael does not want to pay for more than one parking though. He is very
 * strong, and does not mind carrying all the bags around.
 *
 * Input:
 * The first line of input gives the number of test cases, 1 ≤ t ≤ 100. There
 * are two lines for each test case. The first gives the number of stores
 * Michael wants to visit, 1 ≤ n ≤ 20, and the second gives their n integer
 * positions on Long Street, 0 ≤ xi ≤ 99.
 *
 * Output:
 * Output for each test case a line with the minimal distance Michael must walk
 * given optimal parking.
 *
 * Solution:
 * Find the smallest point and the largest point, then take the middle value.
 */

#include "Volume113/p11364.h"

Void p11364_main() {
  var case_count = 0;
  scanf("%d", &case_count);

  while (case_count--) {
    var n = 0;
    scanf("%d", &n);

    var alpha = 0;
    var min = 99;
    var max = 0;
    while (n--) {
      scanf("%d", &alpha);

      min = min(min, alpha);
      max = max(max, alpha);
    }

    printf("%d\n", (max - min) * 2);
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
