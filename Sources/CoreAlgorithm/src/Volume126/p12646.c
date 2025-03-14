/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p12646.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: December 11, 2024                              \ \ \_/__ \_\ \_  __  */
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
 * 12646 Zero or One
 *
 * Everyone probably knows the game Zero or One (in some regions in Brazil also
 * known as Two or One), used to determine a winner among three or more players.
 * For those unfamiliar, the game works as follows. Each player chooses a value
 * between zero or one; prompted by a command (usually one of the contestants
 * announces "Zero or... One!"), all participants show the value chosen using a
 * hand: if the value chosen is one, the contestant shows a hand with an
 * extended index finger; if the value chosen is zero, the contestant shows a
 * hand with all fingers closed. The winner is the one who has chosen a value
 * different from all others. If there is no player with a value different from
 * all others (e.g. all players choose zero, or some players choose zero and
 * some players choose one), there is no winner.
 *
 * Alice, Bob and Clara are great friends and play Zerinho all the time: to
 * determine who will buy popcorn during the movie session, who will enter the
 * swimming pool first, etc.. They play so much that they decided make a plugin
 * to play Zerinho on Facebook. But since the don’t know how to program
 * computers, they divided the tasks among friends who do know, including you.
 *
 * Given the three values chosen by Alice, Bob and Clara, each value zero or
 * one, write a program that determines if there is a winner, and in that case
 * determines who is the winner.
 *
 * Input:
 * The input contains several test cases. Each test case contains a single line,
 * with three integers A, B and C, indicating respectively the values chosen by
 * Alice, Beto and Clara.
 *
 * Output:
 * For each test case your program must output a single line, containing a
 * single character. If Alice is the winner the character must be 'A', if Beto
 * is the winner the character must be ‘B’, if Clara is the winner the character
 * must be 'C', and if there is no winner the character must be '*' (asterisc).
 *
 * Restrictions: A, B, C ∈ {0, 1}
 *
 * Solutions:
 * Simple branch.
 */

#include "Volume126/p12646.h"

Void p12646_main() {
  var a = 0;
  var b = 0;
  var c = 0;
  while (scanf("%d %d %d", &a, &b, &c) == 3) {
    if (a == b && a == c) {
      printf("*\n");
    } else if (a == b) {
      printf("C\n");
    } else if (b == c) {
      printf("A\n");
    } else {
      printf("B\n");
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
