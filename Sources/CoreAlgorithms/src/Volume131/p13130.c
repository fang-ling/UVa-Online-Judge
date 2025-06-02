/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p13130.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: May 5, 2025                                    \ \ \_/__ \_\ \_  __  */
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
 * 13130 Cacho
 *
 * In Bolivia there is a very popular game called "Cacho". The game consists
 * rolling five dices (a1, a2, a3, a4, a5) and then annotate the result
 * according to certain rules. This time we will focus on one case in
 * particular: "escala". A "escala" is the scene in which the dices form a
 * sequence of consecutive numbers. More formally a “escala” meets the property:
 *
 *   a_i + 1 = a_{i+1}, 1 ≤ i ≤ 4
 *
 * There are two types of "escala": a ordinary "escala" (it satisfy the property
 * described above), and a "Escala Real" (when the scenery is 1, 3, 4, 5, 6. In
 * the game this case is also a valid "scala").
 *
 * Cael is a boy who is learning to play and wants you to help develop a program
 * to check when five dices are forming a "escala". Note that the "Escala Real"
 * is not a valid "escala" for Cael.
 *
 * Input:
 * The input begins with a number T ≤ 100, the number of test cases. Below are T
 * lines, each with five numbers ai (1 ≤ a_i ≤ 6) in no-decreasing order.
 *
 * Output:
 * In each case, if the five dices form a scale print in one line 'Y'. Otherwise
 * print in one line 'N' (quotes for clarity).
 */

#include "Volume131/p13130.h"

Void p13130_main() {
  var case_count = 0;
  scanf("%d", &case_count);

  Int32 numbers[5];
  while (case_count--) {
    var i = 0;
    for (; i < 5; i += 1) {
      scanf("%d", &numbers[i]);
    }

    var is_escala = true;
    for (i = 1; i < 5; i += 1) {
      if (numbers[i] - numbers[i - 1] != 1) {
        is_escala = false;
        break;
      }
    }

    printf("%s\n", is_escala ? "Y" : "N");
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
