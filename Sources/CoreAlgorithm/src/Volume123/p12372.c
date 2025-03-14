/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p12372.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 14, 2024                               \ \ \_/__ \_\ \_  __  */
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
 * 12372 Packing for Holiday
 *
 * Mr. Bean used to have a lot of problems packing his suitcase for holiday. So
 * he is very careful for this coming holiday. He is more serious this time
 * because he is going to meet his fiancée and he is also keeping frequent
 * communication with you as a programmer friend to have suggestions. He gets
 * confused when he buys a gift box for his fiancée because he can’t decide
 * whether it will fit in his suitcase or not. Sometimes a box doesn’t fit in
 * his suitcase in one orientation and after rotating the box to a different
 * orientation it fits in the suitcase. This type of behavior makes him puzzled.
 *
 * So to make things much simpler he bought another suitcase having same length,
 * width and height, which is 20 inches. This measurement is taken from inside
 * of the box. So a box which has length, width and height of 20 inches will
 * just fit in this suitcase. He also decided to buy only rectangular shaped
 * boxes and keep a measuring tape in his pocket. Whenever he chooses one gift
 * box, which must be rectangular shaped, he quickly measures the length, width
 * and height of the box. But still he can’t decide whether it will fit in his
 * suitcase or not. Now he needs your help. Please write a program for him which
 * calculates whether a rectangular box fits in his suitcase or not provided the
 * length, width and height of the box. Note that, sides of the box must be
 * parallel to the sides of the suitcase.
 *
 * Input:
 * Input starts with an integer T (T ≤ 100), which indicates the number of test
 * cases. Each of the next T line contains three integers L, W and H
 * (1 ≤ L, W, H ≤ 50) denoting the length, width and height of a rectangular
 * shaped box.
 *
 * Output:
 * For each test case, output a single line. If the box fits in the suitcase in
 * any orientation having the sides of the box is parallel to the sides of the
 * suitcase, this line will be 'Case #: good', otherwise it will be
 * 'Case #: bad'. In your output # will be replaced by the case number. Please
 * see the sample input and sample output for exact format.
 *
 * Solution:
 * Just check if all L, W, H ≤ 20.
 */

#include "Volume123/p12372.h"

Void p12372_main() {
  var case_count = 0;
  scanf("%d", &case_count);
  var i = 0;
  for (i = 1; i <= case_count; i += 1) {
    var l = 0;
    var w = 0;
    var h = 0;
    scanf("%d %d %d", &l, &w, &h);
    if (_max(_max(l, w), h) > 20) {
      printf("Case %d: bad\n", i);
    } else {
      printf("Case %d: good\n", i);
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
