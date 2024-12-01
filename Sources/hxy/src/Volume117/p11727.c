/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11727.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: December 1, 2024                               \ \ \_/__ \_\ \_  __  */
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
 * 11727 Cost Cutting
 *
 * Company XYZ have been badly hit by recession and is taking a lot of cost
 * cutting measures. Some of these measures include giving up office space,
 * going open source, reducing incentives, cutting on luxuries and issuing pink
 * slips.
 * They have got three (3) employees working in the accounts department and are
 * going to lay-off two (2) of them. After a series of meetings, they have
 * decided to dislodge the person who gets the most salary and the one who gets
 * the least. This is usually the general trend during crisis like this.
 * You will be given the salaries of these 3 employees working in the accounts
 * department. You have to find out the salary of the person who survives.
 *
 * Input:
 * The first line of input is an integer T (T < 20) that indicates the number of
 * test cases. Each case consists of a line with 3 distinct positive integers.
 * These 3 integers represent the salaries of the three employees. All these
 * integers will be in the range [1000, 10000].
 *
 * Output:
 * For each case, output the case number followed by the salary of the person
 * who survives.
 *
 * Solution:
 * Find the middle in three numbers.
 */

#include "Volume117/p11727.h"

Void p11727_main() {
  var case_count = 0;
  scanf("%d", &case_count);

  var case_number = 1;
  for (; case_number <= case_count; case_number += 1) {
    var a = 0;
    var b = 0;
    var c = 0;
    scanf("%d %d %d", &a, &b, &c);

    var result = 0;
    if ((a <= b && a >= c) || (a <= c && a >= b)) {
      result = a;
    } else if ((b <= a && b >= c) || (b <= c && b >= a)) {
      result = b;
    } else {
      result = c;
    }

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
