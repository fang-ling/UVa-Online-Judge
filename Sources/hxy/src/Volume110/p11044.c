/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11044.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 7, 2024                                \ \ \_/__ \_\ \_  __  */
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
 * 11044 Searching for Nessy
 *
 * In July 2003, the BBC reported an extensive investigation of Loch Ness by a
 * BBC team, using 600 separate sonar beams, found no trace of any "sea monster"
 * (i.e., any large animal, known or unknown) in the loch. The BBC team
 * concluded that Nessie does not exist. Now we want to repeat the experiment.
 *
 * Given a grid of n rows and m columns representing the loch, 6 ≤ n, m ≤ 10000,
 * find the minimum number s of sonar beams you must put in the square such that
 * we can control every position in the grid, with the following conditions:
 *   - one sonar occupies one position in the grid; the sonar beam controls its
 *     own cell and the contiguous cells;
 *   - the border cells do not need to be controlled, because Nessy cannot hide
 *     there (she is too big).
 *
 * Input:
 * The first line of the input contains an integer, t, indicating the number of
 * test cases. For each test case, there is a line with two numbers separated by
 * blanks, 6 ≤ n, m ≤ 10000, that is, the size of the grid (n rows and m
 * columns).
 *
 * Output:
 * For each test case, the output should consist of one line showing the minimum
 * number of sonars that verifies the conditions above.
 *
 * Solution:
 * row: ceil((n - 2) / 3)
 * column: ceil((m - 2) / 3)
 *   why minus 2? ==> (the border cells do not need to be controlled)
 * s = ceil((n - 2) / 3) * ceil((m - 2) / 3)
 */

#include "Volume110/p11044.h"

Void p11044_main() {
  var case_count = 0;
  scanf("%d", &case_count);
  while (case_count--) {
    var n = 0;
    var m = 0;
    scanf("%d %d", &n, &m);
    printf("%d\n", (Int32)(ceil((n - 2) / 3.0) * ceil((m - 2) / 3.0)));
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
