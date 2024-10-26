/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11078.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 22, 2024                               \ \ \_/__ \_\ \_  __  */
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
 * 11078 Open Credit System
 *
 * In an open credit system, the students can choose any course they like, but
 * there is a problem. Some of the students are more senior than other students.
 * The professor of such a course has found quite a number of such students who
 * came from senior classes (as if they came to attend the pre requisite course
 * after passing an advanced course). But he wants to do justice to the new
 * students. So, he is going to take a placement test (basically an IQ test) to
 * assess the level of difference among the students. He wants to know the
 * maximum amount of score that a senior student gets more than any junior
 * student. For example, if a senior student gets 80 and a junior student gets
 * 70, then this amount is 10. Be careful that we don’t want the absolute value.
 * Help the professor to figure out a solution.
 *
 * Input:
 * Input consists of a number of test cases T (less than 20). Each case starts
 * with an integer n which is the number of students in the course. This value
 * can be as large as 100,000 and as low as 2. Next n lines contain n integers
 * where the i’th integer is the score of the i’th student. All these integers
 * have absolute values less than 150000. If i < j, then i’th student is senior
 * to the j’th student.
 *
 * Output:
 * For each test case, output the desired number in a new line. Follow the
 * format shown in sample input-output section.
 *
 * Solution:
 * Same as p1709. Find the maximum difference between current max and current
 * number.
 */

#include "Volume110/p11078.h"

Void p11078_main() {
  var case_count = 0;
  scanf("%d", &case_count);
  while (case_count--) {
    var n = 0;
    scanf("%d", &n);
    
    var current_max = -150000-1;
    var current_score = 0;
    var result = -150000-1;
    while (n--) {
      scanf("%d", &current_score);
      result = max(result, current_max - current_score);
      current_max = max(current_max, current_score);
    }
    
    printf("%d\n", result);
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
