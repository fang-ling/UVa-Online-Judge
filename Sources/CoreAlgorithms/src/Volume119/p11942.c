/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11942.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: May 21, 2025                                   \ \ \_/__ \_\ \_  __  */
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
 * 11942 Lumberjack Sequencing
 *
 * Another tale of lumberjacks?. Let see ...
 *
 * The lumberjacks are rude, bearded workers, while foremen tend to be bossy and
 * simpleminded. The foremen like to harass the lumberjacks by making them line
 * up in groups of ten, ordered by the length of their beards. The lumberjacks,
 * being of different physical heights, vary their arrangements to confuse the
 * foremen. Therefore, the foremen must actually measure the beards in
 * centimeters to see if everyone is lined up in order.
 *
 * Your task is to write a program to assist the foremen in determining whether
 * or not the lumberjacks are lined up properly, either from shortest to longest
 * beard or from longest to shortest.
 *
 * Input:
 * The input starts with line containing a single integer N , 0 < N < 20, which
 * is the number of groups to process. Following this are N lines, each
 * containing ten distinct positive integers less than 100.
 *
 * Output:
 * There is a title line, then one line per set of beard lengths. See the sample
 * output for capitalization and punctuation.
 */

#include "Volume119/p11942.h"

Void p11942_main() {
  var breads = (Int32*)malloc(sizeof(Int32) * 10);

  var n = 0;
  scanf("%d", &n);

  printf("Lumberjacks:\n");

  while (n--) {
    var i = 0;
    for (; i < 10; i += 1) {
      scanf("%d", &breads[i]);
    }

    var is_increasing = true;
    var is_decreasing = true;
    i = 1;
    for (; i < 10; i += 1) {
      if (breads[i - 1] <= breads[i]) {
        is_decreasing = false;
      }
      if (breads[i - 1] >= breads[i]) {
        is_increasing = false;
      }
    }

    printf("%srdered\n", is_decreasing || is_increasing ? "O" : "Uno");
  }

  free(breads);
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
