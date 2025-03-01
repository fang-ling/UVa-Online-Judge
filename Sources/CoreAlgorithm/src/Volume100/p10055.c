/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10055.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: November 20, 2024                              \ \ \_/__ \_\ \_  __  */
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
 * 10055 Hashmat the brave warrior
 *
 * Hashmat is a brave warrior who with his group of young soldiers moves from
 * one place to another to fight against his opponents. Before Fighting he just
 * calculates one thing, the difference between his soldier number and the
 * opponent's soldier number. From this difference he decides whether to fight
 * or not. Hashmat’s soldier number is never greater than his opponent.
 *
 * Input:
 * The input contains two numbers in every line. These two numbers in each line
 * denotes the number soldiers in Hashmat's army and his opponent's army or vice
 * versa. The input numbers are not greater than 2**32. Input is terminated by
 * 'End of File'.
 *
 * Output:
 * For each line of input, print the difference of number of soldiers between
 * Hashmat's army and his opponent's army. Each output should be in seperate
 * line.
 *
 * Solution:
 * A - B problem.
 */

#include "Volume100/p10055.h"

Void p10055_main() {
  var lhs = 0ll;
  var rhs = 0ll;
  while (scanf("%lld %lld", &lhs, &rhs) == 2) {
    printf("%lld\n", abs(lhs - rhs));
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
