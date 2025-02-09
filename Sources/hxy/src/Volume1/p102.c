/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p102.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: February 7, 2025                               \ \ \_/__ \_\ \_  __  */
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
 * 102 Ecological Bin Packing
 *
 * Bin packing, or the placement of objects of certain weights into different
 * bins subject to certain constraints, is an historically interesting problem.
 * Some bin packing problems are NP-complete but are amenable to dynamic
 * programming solutions or to approximately optimal heuristic solutions.
 *
 * In this problem you will be solving a bin packing problem that deals with
 * recycling glass.
 *
 * Recycling glass requires that the glass be separated by color into one of
 * three categories: brown glass, green glass, and clear glass. In this problem
 * you will be given three recycling bins, each containing a specified number of
 * brown, green and clear bottles. In order to be recycled, the bottles will
 * need to be moved so that each bin contains bottles of only one color.
 *
 * The problem is to minimize the number of bottles that are moved. You may
 * assume that the only problem is to minimize the number of movements between
 * boxes.
 *
 * For the purposes of this problem, each bin has infinite capacity and the only
 * constraint is moving the bottles so that each bin contains bottles of a
 * single color. The total number of bottles will never exceed 2**31.
 *
 * Input:
 * The input consists of a series of lines with each line containing 9 integers.
 * The first three integers on a line represent the number of brown, green, and
 * clear bottles (respectively) in bin number 1, the second three represent the
 * number of brown, green and clear bottles (respectively) in bin number 2, and
 * the last three integers represent the number of brown, green, and clear
 * bottles (respectively) in bin number 3. For example, the line
 *
 *   10 15 20 30 12 8 15 8 31
 *
 * indicates that there are 20 clear bottles in bin 1, 12 green bottles in
 * bin 2, and 15 brown bottles in bin 3.
 *
 * Integers on a line will be separated by one or more spaces. Your program
 * should process all lines in the input file.
 *
 * Output:
 * For each line of input there will be one line of output indicating what color
 * bottles go in what bin to minimize the number of bottle movements. You should
 * also print the minimum number of bottle movements.
 *
 * The output should consist of a string of the three upper case characters 'G',
 * 'B', 'C' (representing the colors green, brown, and clear) representing the
 * color associated with each bin.
 *
 * The first character of the string represents the color associated with the
 * first bin, the second character of the string represents the color associated
 * with the second bin, and the third character represents the color associated
 * with the third bin.
 *
 * The integer indicating the minimum number of bottle movements should follow
 * the string. If more than one order of brown, green, and clear bins yields the
 * minimum number of movements then the alphabetically first string representing
 * a minimal configuration should be printed.
 */

#include "Volume1/p102.h"

struct Result {
  Int32 number;
  Char colors[4];
};

static Int32 compare(AnyConstantObject _a, AnyConstantObject _b) {
  var a = *(struct Result*)_a;
  var b = *(struct Result*)_b;

  if (a.number == b.number) {
    return strcmp(a.colors, b.colors);
  }
  return a.number - b.number;
}

Void p102_main() {
  var results = (struct Result*)malloc(sizeof(struct Result) * 6);

  var b1 = 0;
  var g1 = 0;
  var c1 = 0;
  var b2 = 0;
  var g2 = 0;
  var c2 = 0;
  var b3 = 0;
  var g3 = 0;
  var c3 = 0;

  while (true) {
    let read_count = scanf("%d %d %d %d %d %d %d %d %d",
                           &b1, &g1, &c1, &b2, &g2, &c2, &b3, &g3, &c3);
    if (read_count != 9) {
      break;
    }

    results[0] = (struct Result) {
      b2 + b3 + c1 + c3 + g1 + g2,
      "BCG"
    };
    results[1] = (struct Result) {
      b2 + b3 + c1 + c2 + g1 + g3,
      "BGC"
    };
    results[2] = (struct Result) {
      b1 + b3 + c2 + c3 + g1 + g2,
      "CBG"
    };
    results[3] = (struct Result) {
      b1 + b2 + c2 + c3 + g1 + g3,
      "CGB"
    };
    results[4] = (struct Result) {
      b1 + b3 + c1 + c2 + g2 + g3,
      "GBC"
    };
    results[5] = (struct Result) {
      b1 + b2 + c1 + c3 + g2 + g3,
      "GCB"
    };

    qsort(results, 6, sizeof(struct Result), compare);

    printf("%s %d\n", results[0].colors, results[0].number);
  }

  free(results);
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
