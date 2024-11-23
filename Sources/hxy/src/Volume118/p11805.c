/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11805.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: November 23, 2024                              \ \ \_/__ \_\ \_  __  */
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
 * 11805 Bafana Bafana
 *
 * Team practice is very important not only for programming contest but also for
 * football. By team practice players can learn cooperating with team mates. For
 * playing as a team improvement of passing skill is very important. Passing is
 * a great way of getting the ball upfield and reduces the risk of giving the
 * ball away.
 *
 * Carlos Alberto Parreira, the coach of Bafana Bafana, also wants his players
 * to practice passing a lot. That's why, while in the training camp for soccer
 * world cup 2010, every day he asks all of the players who are present in
 * practice to stand in a circle and practice passing. If N players are in
 * practice, he gives each of the players a distinct number from 1 to N , and
 * asks them to stand sequentially, so that player 2 will stand in right side of
 * player 1 and player 3 will stand in right side of player 2, and so on. As
 * they are in a circle, player 1 will stand right to player N.
 *
 * The rule of passing practice is, Parreira will give the ball to player K, and
 * practice will start. Practice will come to an end after P passes. In each
 * pass, a player will give the ball to his partner who is in his immediate
 * right side. After P passes, the player who owns the ball at that moment will
 * give the ball back to Parreira.
 *
 * Parreira wants to be ensured that his players practice according the rule. So
 * he wants a program which will tell him which player will give him the ball
 * back. So after taking the ball from the same person he can be happy that,
 * the players play according to the rules. Otherwise he will ask them to start
 * from beginning.
 *
 * Input:
 * Input starts with an integer T (T ≤ 1000), the number of test cases. Each
 * test case will contain three integers, N (2 ≤ N ≤ 23), K (1 ≤ K ≤ N ),
 * P (1 ≤ P ≤ 200).
 *
 * Output:
 * For each test case, output a single line giving the case number followed by
 * the Bafana player number who will give the ball to Parreira. See sample
 * output for exact format.
 *
 * Solution:
 * Simple mod.
 */

#include "Volume118/p11805.h"

Void p11805_main() {
  var case_count = 0;
  scanf("%d", &case_count);

  var case_number = 1;
  for (; case_number <= case_count; case_number += 1) {
    var total_player = 0;
    var player = 0;
    var passes = 0;
    scanf("%d %d %d", &total_player, &player, &passes);

    let result = (player - 1 + passes) % total_player + 1;
    printf("Case %d: %d\n", case_number, result);
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
