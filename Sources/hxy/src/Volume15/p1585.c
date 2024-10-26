/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p1585.c                                              /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 26, 2024                               \ \ \_/__ \_\ \_  __  */
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
 * 1585 Score
 *
 * There is an objective test result such as "OOXXOXXOOO". An 'O' means a
 * correct answer of a problem and an 'X' means a wrong answer. The score of
 * each problem of this test is calculated by itself and its just previous
 * consecutive 'O's only when the answer is correct. For example, the score of
 * the 10th problem is 3 that is obtained by itself and its two previous
 * consecutive 'O's.
 * Therefore, the score of "OOXXOXXOOO" is 10 which is calculated by
 * "1+2+0+0+1+0+0+1+2+3".
 * You are to write a program calculating the scores of test results.
 *
 * Input:
 * Your program is to read from standard input. The input consists of T test
 * cases. The number of test cases T is given in the first line of the input.
 * Each test case starts with a line containing a string composed by 'O' and 'X'
 * and the length of the string is more than 0 and less than 80. There is no
 * spaces between 'O' and 'X'.
 *
 * Output:
 * Your program is to write to standard output. Print exactly one line for each
 * test case. The line is to contain the score of the test case.
 *
 * Solution:
 * Very easy one pass algorithm.
 */

#include "Volume15/p1585.h"

Void p1585_main() {
  Int8 input[128];
  
  var case_count = 0;
  scanf("%d", &case_count);
  while (case_count--) {
    scanf("%s", input);
    
    var count = (Int)strlen(input);
    var score = 0;
    var consecutive_count = 0;
    var i = 0;
    for (i = 0; i < count; i += 1) {
      if (input[i] == 'X') {
        consecutive_count = 0;
      } else {
        consecutive_count += 1;
      }
      score += consecutive_count;
    }
    
    printf("%d\n", score);
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
