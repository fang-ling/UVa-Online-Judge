/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10300.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: December 17, 2024                              \ \ \_/__ \_\ \_  __  */
/*                                                       \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the hxy open source project.
 *
 * Copyright (c) 2024 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */

/*
 * 10300 Ecological Premium
 *
 * German farmers are given a premium depending on the conditions at their
 * farmyard. Imagine the following simplified regulation: you know the size of
 * each farmer's farmyard in square meters and the number of animals living at
 * it. We won't make a difference between different animals, although this is
 * far from reality. Moreover you have information about the degree the farmer
 * uses environment-friendly equipment and practices, expressed in a single
 * integer greater than zero. The amount of money a farmer receives can be
 * calculated from these parameters as follows. First you need the space a
 * single animal occupies at an average. This value (in square meters) is then
 * multiplied by the parameter that stands for the farmer's
 * environment-friendliness, resulting in the premium a farmer is paid per
 * animal he owns.
 * To compute the final premium of a farmer just multiply this premium per
 * animal with the number of animals the farmer owns.
 *
 * Input:
 * The first line of input contains a single positive integer n (< 20), the
 * number of test cases. Each test case starts with a line containing a single
 * integer f (0 < f < 20), the number of farmers in the test case. This line is
 * followed by one line per farmer containing three positive integers each: the
 * size of the farmyard in square meters, the number of animals he owns and the
 * integer value that expresses the farmers environment-friendliness. Input is
 * terminated by end of file. No integer in the input is greater than 100000 or
 * less than 0.
 *
 * Output:
 * For each test case output one line containing a single integer that holds the
 * summed burden for Germany's budget, which will always be a whole number. Do
 * not output any blank lines.
 *
 * Solution:
 * Compute: sum_{k=1}^f(a_k \times c_k)
 */

#include "Volume103/p10300.h"

Void p10300_main() {
  var n = 0;
  scanf("%d", &n);

  while (n--) {
    var f = 0;
    scanf("%d", &f);

    var a = 0;
    var b = 0;
    var c = 0;
    var sum = (Int128)0;
    while (f--) {
      scanf("%d %d %d", &a, &b, &c);
      sum += (Int128)a * c;
    }

    printf("%lld\n", (Int64)sum);
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
