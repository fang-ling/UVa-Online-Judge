/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10963.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: May 29, 2025                                   \ \ \_/__ \_\ \_  __  */
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
 * 10963 The Swallowing Ground
 *
 * Now that the wicked is punished, there is still work to do. For example, the
 * ground needs to seal itself up. (Otherwise, good people will accidentally
 * fall into Hell, which is not good.)
 *
 * The ground swallowed Don Giovanni by collapsing: Part of the ground
 * collapsed–fell off to Hell–and this created a gap that swallowed
 * Don Giovanni. The only way the ground can be fixed is by sliding landmasses
 * to close up the gap. Here is an example. The left diagram shows the ground
 * with a ravine. Assume that the ground extends infinitely to the north and to
 * the south, and there are seams on the east and west ends; so the northern
 * block can slide southward, and the southern block can slide northward. The
 * right diagram shows the gap closed.
 *
 *   |▢▢▢▢▢|        |     |
 *   |▣▢▢▢▣|        |     |
 *   |▣▣▣▢▣|        |▢▢▢▢▢|
 *   |▢▣▣▣▢|        |▢▢▢▢▢|
 *   |▢▢▢▣▢|        |▢▢▢▢▢|
 *   |▢▢▢▢▢|        |▢▢▢▢▢|
 *
 * Here is another example. The ravine in the left diagram cannot be closed
 * perfectly by sliding the ground northward and southward. The right diagram
 * shows the result of the best effort: there is still a hole.
 *
 *   |▢▢▢▢▢|        |     |
 *   |▢▢▢▢▣|        |▢▢▢▢▢|
 *   |▣▣▣▢▣|        |▢▢▢▢▣|
 *   |▢▢▢▣▢|        |▢▢▢▢▢|
 *   |▢▢▢▢▢|        |▢▢▢▢▢|
 *   |▢▢▢▢▢|        |▢▢▢▢▢|
 *
 * Write a program to determine if the gap can be closed. The ground is a grid
 * with rows (a row runs east-west) and columns (a column runs north-south).
 * Holes are cells on the grid, and the gap consists of holes.
 *
 * Input:
 * The input begins with a single positive integer on a line by itself
 * indicating the number of the cases following, each of them as described
 * below. This line is followed by a blank line, and there is also a blank line
 * between two consecutive inputs.
 *
 * The first line contains the number of columns W of the ground to be
 * considered. Then W lines follow, specifying the boundary of the gap by
 * columns: a line represents a column, and the order of the lines follows the
 * east-to-west order. Each line contains y1, the north-most row of the gap in
 * this column, and y2, the south-most row of the gap in this column. Row
 * numbers are integers between -100 and 100 inclusive.
 *
 * The input specifies a valid gap: the holes separate the ground into exactly a
 * northern block and a southern block. There are no holes embedded inside a
 * block. There are no islands.
 *
 *   Note: The sample input below corresponds to the first diagram.
 *
 * Output:
 *
 * For each test case, the output must follow the description below. The outputs
 * of two consecutive cases will be separated by a blank line.
 * Output the line 'yes' if the gap can be closed by sliding blocks north and
 * south; and 'no' otherwise.
 */

#include "Volume109/p10963.h"

Void p10963_main() {
  var case_count = 0;
  scanf("%d", &case_count);

  var is_first_output = true;
  while (case_count--) {
    var width = 0;
    scanf("%d", &width);

    var top = 0;
    var bottom = 0;
    scanf("%d %d", &top, &bottom);

    var can_close = true;
    var difference = top - bottom;
    width -= 1;
    while (width--) {
      scanf("%d %d", &top, &bottom);
      if (difference != top - bottom) {
        can_close = false;
      }
    }

    if (is_first_output) {
      is_first_output = false;
    } else {
      printf("\n");
    }
    printf("%s\n", can_close ? "yes" : "no");
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
