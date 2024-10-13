/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11547.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 9, 2024                                \ \ \_/__ \_\ \_  __  */
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
 * 11547 Automatic Answer
 *
 * Last month Alice nonchalantly entered her name in a draw for a Tapmaster
 * 4000. Upon checking her mail today, she found a letter that read:
 *
 * "Congratulations, Alice! You have won a Tapmaster 4000. To claim your prize,
 * you must answer the following skill testing question."
 *
 * Alice's initial feelings of surprised joy turned quickly to those of dismay.
 * Her lifetime record for skill testing questions is an abysmal 3 right and 42
 * wrong.
 *
 * Mad Skills, the leading skill testing question development company, was hired
 * to provide skill testing questions for this particular Tapmaster 4000 draw.
 * They decided to create a different skill testing question to each winner so
 * that the winners could not collaborate to answer the question.
 *
 * Can you help Alice win the Tapmaster 4000 by solving the skill testing
 * question?
 *
 * Input:
 * The input begins with t (1 ≤ t ≤ 100), the number of test cases. Each test
 * case contains an integer n (−1000 ≤ n ≤ 1000) on a line by itself. This n
 * should be substituted into the skill testing question below.
 *
 * Output:
 * For each test case, output the answer to the following skill testing question
 * on a line by itself: "Multiply n by 567, then divide the result by 9, then
 * add 7492, then multiply by 235, then divide by 47, then subtract 498. What is
 * the digit in the tens column?"
 *
 * Solution:
 * To get the digit in the tens column, simply divide that number by 10 and then
 * take the result modulo 10.
 */

#include "Volume115/p11547.h"

Void p11547_main() {
  var case_count = 0;
  scanf("%d", &case_count);
  while (case_count--) {
    var number = 0;
    scanf("%d", &number);
    printf("%d\n", abs(((number * 567 / 9 + 7492) * 235 / 47 - 498) / 10 % 10));
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
