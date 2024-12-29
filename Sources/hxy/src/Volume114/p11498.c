/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11498.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: December 26, 2024                              \ \ \_/__ \_\ \_  __  */
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
 * 11498 Division of Nlogonia
 *
 * After centuries of hostilities and skirmishes between the four nations living
 * in the land generally known as Nlogonia, and years of negotiations involving
 * diplomats, politicians and the armed forces of all interested parties, with
 * mediation by UN, NATO, G7 and SBC, it was at last agreed by all the way to
 * end the dispute, dividing the land into four independent territories.
 * It was agreed that one point, called division point, with coordinates
 * established in the negotiations, would define the country division, in the
 * following way. Two lines, both containing the division point, one in the
 * North-South direction and one in the East-West direction, would be drawn on
 * the map, dividing the land into four new countries. Starting from the
 * Western-most, Northern-most quadrant, in clockwise direction, the new
 * countries will be called Northwestern Nlogonia, Northeastern Nlogonia,
 * Southeastern Nlogonia and Southwestern Nlogonia.
 * The UN determined that a page in the Internet should exist so that the
 * inhabitants could check in which of the countries their homes are. You have
 * been hired to help implementing the system.
 *
 * Input:
 * The input contains several test cases. The first line of a test case contains
 * one integer K indicating the number of queries that will be made
 * (0 < K ≤ 10**3). The second line of a test case contains two integers N and M
 * representing the coordinates of the division point (−10**4 < N, M < 10**4).
 * Each of the K following lines contains two integers X and Y representing the
 * coordinates of a residence (−10**4 ≤ X, Y ≤ 10**4).
 * The end of input is indicated by a line containing only the number zero.
 *
 * Output:
 * For each test case in the input your program must print one line containing:
 *   - the word 'divisa' (means border in Portuguese) if the residence is on one
 *     of the border lines (North-South or East-West);
 *   - 'NO' (means NW in Portuguese) if the residence is in Northwestern
 *     Nlogonia;
 *   - 'NE' if the residence is in Northeastern Nlogonia;
 *   - 'SE' if the residence is in Southeastern Nlogonia;
 *   - 'SO' (means SW in Portuguese) if the residence is in Southwestern
 *     Nlogonia.
 *
 * Solution:
 * Given a reference point (X, Y) and another point (a, b), find its positional
 * relationship to the reference point.
 */

#include "Volume114/p11498.h"

Void p11498_main() {
  var k = 0;
  while (scanf("%d", &k) == 1 && k != 0) {

    var n = 0;
    var m = 0;
    scanf("%d %d", &n, &m);

    while (k--) {
      var x = 0;
      var y = 0;
      scanf("%d %d", &x, &y);

      if (x == n || y == m) {
        printf("divisa\n");
      } else if (x > n && y > m) {
        printf("NE\n");
      } else if (x < n && y < m) {
        printf("SO\n");
      } else if (x > n && y < m) {
        printf("SE\n");
      } else {
        printf("NO\n");
      }
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
