/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10189.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: January 26, 2025                               \ \ \_/__ \_\ \_  __  */
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
 * 10189 Minesweeper
 *
 * Have you ever played Minesweeper? It's a cute little game which comes within
 * a certain Operating System which name we can't really remember. Well, the
 * goal of the game is to find where are all the mines within a M × N field. To
 * help you, the game shows a number in a square which tells you how many mines
 * there are adjacent to that square. For instance, supose the following 4 × 4
 * field with 2 mines (which are represented by an '*' character):
 *
 *     *...
 *     ....
 *     .*..
 *     ....
 *
 * If we would represent the same field placing the hint numbers described
 * above, we would end up with:
 *
 *     *100
 *     2210
 *     1*10
 *     1110
 *
 * As you may have already noticed, each square may have at most 8 adjacent
 * squares.
 *
 * Input:
 * The input will consist of an arbitrary number of fields. The first line of
 * each field contains two integers n and m (0 < n, m ≤ 100) which stands for
 * the number of lines and columns of the field respectively. The next n lines
 * contains exactly m characters and represent the field.
 * Each safe square is represented by an '.' character (without the quotes) and
 * each mine square is represented by an '*' character (also without the
 * quotes). The first field line where n = m = 0 represents the end of input and
 * should not be processed.
 *
 * Output:
 * For each field, you must print the following message in a line alone:
 *
 *     Field #x:
 *
 * Where x stands for the number of the field (starting from 1). The next n
 * lines should contain the field with the '.' characters replaced by the number
 * of adjacent mines to that square. There must be an empty line between field
 * outputs.
 *
 * Solution:
 * Simple nested for loops.
 */

#include "Volume101/p10189.h"

Void p10189_main() {
  var field_count = 0;
  Int8 field[128][128];

  var n = 0;
  var m = 0;
  while (scanf("%d %d", &n, &m) == 2 && (n != 0 && m != 0)) {
    var i = 0;
    for (; i < n; i += 1) {
      scanf("%s", field[i]);
    }

    /* Initialize */
    for (i = 0; i < n; i += 1) {
      var j = 0;
      for (; j < m; j += 1) {
        if (field[i][j] != '*') {
          field[i][j] = '0';
        }
      }
    }
    /* Find the each bomb */
    for (i = 0; i < n; i += 1) {
      var j = 0;
      for (; j < m; j += 1) {
        if (field[i][j] == '*') {
          if (i - 1 >= 0) {
            if (j - 1 >= 0 && field[i - 1][j - 1] != '*') {
              field[i - 1][j - 1] += 1;
            }
            if (j + 1 < m && field[i - 1][j + 1] != '*') {
              field[i - 1][j + 1] += 1;
            }
            if (field[i - 1][j] != '*') {
              field[i - 1][j] += 1;
            }
          }
          if (i + 1 < n) {
            if (j - 1 >= 0 && field[i + 1][j - 1] != '*') {
              field[i + 1][j - 1] += 1;
            }
            if (j + 1 < m && field[i + 1][j + 1] != '*') {
              field[i + 1][j + 1] += 1;
            }
            if (field[i + 1][j] != '*') {
              field[i + 1][j] += 1;
            }
          }

          if (j - 1 >= 0 && field[i][j - 1] != '*') {
            field[i][j - 1] += 1;
          }
          if (j + 1 < m && field[i][j + 1] != '*') {
            field[i][j + 1] += 1;
          }
        }
      }
    }

    field_count += 1;
    if (field_count > 1) {
      printf("\n");
    }
    printf("Field #%d:\n", field_count);
    for (i = 0; i < n; i += 1) {
      printf("%s\n", field[i]);
    }
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
