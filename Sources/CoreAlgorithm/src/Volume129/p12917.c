/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p12917.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: December 12, 2024                              \ \ \_/__ \_\ \_  __  */
/*                                                       \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the CoreAlgorithm open source project.
 *
 * Copyright (c) 2024 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */

/*
 * 12917 Prop hunt!
 *
 * Prop hunt is a game modification (or simply a mod), similar to the famous
 * hide and seek, where two teams play against each other. One team are the
 * props, they are players that can choose any object of the scenario to
 * disguise themselves as, so they could be a table, a book, a barrel, a paper,
 * whatever they want. They must be completely calm or the other team, the
 * hunters, will kill them. As a hunter, you must be careful: if you shoot
 * something that is not a disguised player, you start losing life. At the end,
 * if any prop survives they will win, otherwise the hunters will win.
 *
 * Your mission is to determine who is going to be the winner of the game, but
 * thankfully, with a couple of simplifications. You will get three numbers:
 * P — the quantity of players in the props team, H — the number of hunters and
 * O — the objects to disguise as. Assume that all the hunters are bots (that
 * is, controlled by the computer) and they’re pretty bad: the hunters will
 * shoot everything in the scenario, starting by the less suspicious objects and
 * ending with the disguised players. If every hunter has 1 point of life, what
 * team will win?
 *
 * Input:
 * The input consists of several test cases, each one on a single line that
 * contains 3 integers P (1 ≤ P ≤ 5), H (1 ≤ H ≤ 5) and O (1 ≤ P ≤ O ≤ 10).
 *
 * Output:
 * Print on a single line the text 'Props win!' if the props survive, otherwise
 * print 'Hunters win!'.
 *
 * Explanation: On the first case, there are 2 props and 2 hunters, but 3
 * objects to disguise as. The first hunter dies trying to kill the object that
 * is not a player, but the second hunter shoots to the other objects that are
 * the disguised players. In the second case, the first hunter shoots a
 * non-player object, and the second one does the same, so the props survive.
 *
 * Solution:
 * Hunters win iff h > o - p
 */

#include "Volume129/p12917.h"

Void p12917_main() {
  var p = 0;
  var h = 0;
  var o = 0;
  while (scanf("%d %d %d", &p, &h, &o) == 3) {
    printf("%s win!\n", h > o - p ? "Hunters" : "Props");
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
