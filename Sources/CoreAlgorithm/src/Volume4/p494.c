/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p494.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: March 1, 2025                                  \ \ \_/__ \_\ \_  __  */
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
 * 494 Kindergarten Counting Game
 *
 * Everybody sit down in a circle. Ok. Listen to me carefully.
 *   "Woooooo, you scwewy wabbit!"
 *   Now, could someone tell me how many words I just said?
 *
 * Input:
 * Input to your program will consist of a series of lines, each line containing
 * multiple words (at least one). A "word" is defined as a consecutive sequence
 * of letters (upper and/or lower case).
 *
 * Output:
 * Your program should output a word count for each line of input. Each word
 * count should be printed on a separate line.
 */
#include "Volume4/p494.h"

Void p494_main() {
  var line = (Int8*)NULL;
  var line_capacity = 0ul;
  var line_count = 0l;
  while ((line_count = getline(&line, &line_capacity, stdin)) > 0) {
    var count = 0;

    var i = 0;
    for (; i < line_count; i += 1) {
      if (isalpha(line[i]) && (i - 1 < 0 || !isalpha(line[i - 1]))) {
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
