/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p13012.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: May 4, 2025                                    \ \ \_/__ \_\ \_  __  */
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
 * 13012 Identifying tea
 *
 * Blind tea tasting is the skill of identifying a tea by using only your senses
 * of smell and taste.
 *
 * As part of the Ideal Challenge of Pure-Tea Consumers (ICPC), a local TV show
 * is organized. During the show, a full teapot is prepared and five contestants
 * are handed a cup of tea each. The participants must smell, taste and assess
 * the sample so as to identify the tea type, which can be: (1) white tea; (2)
 * green tea; (3) black tea; or (4) herbal tea. At the end, the answers are
 * checked to determine the number of correct guesses.
 *
 * Given the actual tea type and the answers provided, determine the number of
 * contestants who got the correct answer.
 *
 * Input:
 * The input contains several test cases; each test case is formatted as
 * follows. The first line contains an integer T representing the tea type
 * (1 ≤ T ≤ 4). The second line contains five integers A, B, C, D and E,
 * indicating the answer given by each contestant (1 ≤ A, B, C, D, E ≤ 4).
 *
 * Output:
 * For each test case in the input, output a line with an integer representing
 * the number of contestants who got the correct answer.
 */

#include "Volume130/p13012.h"

Void p13012_main() {
  var tea_type = 0;
  while (scanf("%d", &tea_type) == 1) {
    var count = 0;

    var i = 0;
    for (; i < 5; i += 1) {
      var guess = 0;
      scanf("%d", &guess);

      if (guess == tea_type) {
        count += 1;
      }
    }

    printf("%d\n", count);
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
