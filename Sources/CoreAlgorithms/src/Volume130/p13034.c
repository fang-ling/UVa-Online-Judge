/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p13034.c                                             /'___\ /\_ \          */
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
 * 13034 Solve Everything :-)
 *
 * In recent ACM ICPC World Finals (2015), there were 13 problems and each of
 * those were solved by at least one team. Well, we will not discuss about how
 * it happened or who did that.
 *
 * In this contest, SIUPC'2015, we are expecting to have at most 128 teams
 * onsite. Three cheers for you for becoming one of the participating teams!
 *
 * Now, we will discuss what we wanted to prepare for you. From the World Finals
 * 2015, we are just inspired to have a set of 13 problems each of which can be
 * solved by at least one participating team.
 *
 * Luckily, we have come to know about an artificial intelligence system named
 * "PAUL". Given a set of problems, for each individual problem, it can foretell
 * the number of teams that are going to solve that problem.
 *
 * Now, we need your help. We are going to give you the predictions of PAUL for
 * some problemsets. For each of the problemsets (with 13 problems), we request
 * you to tell us whether we can consider the set so that each problem from that
 * set can be solved by at least one team.
 *
 * Input:
 * First line of input consists of an integer S (≤ 23), the number of
 * problemsets with 13 problems. Each of next S lines consists of 13 space
 * separated integers, the predicted number of teams to solve each problem.
 *
 * Output:
 * For each problem set, output a line formatted as 'Set #N : Ans'. Here N is an
 * integer which is the serial number of set. And Ans is your answer which is
 * either 'Yes' or 'No' (without quotes).
 */

#include "Volume130/p13034.h"

Void p13034_main() {
  var case_count = 0;
  scanf("%d", &case_count);

  var case_number = 1;
  for (; case_number <= case_count; case_number += 1) {
    var is_solved = true;

    var solved_count = -1;
    var B = 13;
    while (B--) {
      scanf("%d", &solved_count);
      if (solved_count == 0) {
        is_solved = false;
      }
    }

    printf("Set #%d: %s\n", case_number, is_solved ? "Yes" : "No");
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
