/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p12658.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: November 17, 2024                              \ \ \_/__ \_\ \_  __  */
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
 * 12658 Character Recognition?
 *
 * Write a program that recognizes characters. Don’t worry, because you only
 * need to recognize three digits: 1, 2 and 3. Here they are:
 *
 *   .*. *** ***
 *   .*. ..* ..*
 *   .*. *** ***
 *   .*. *.. ..*
 *   .*. *** ***
 *
 * Input:
 * The input contains only one test case, consisting of 6 lines. The first line
 * contains n, the number of characters to recognize (1 ≤ n ≤ 10). Each of the
 * next 5 lines contains 4n characters. Each character contains exactly 5 rows
 * and 3 columns of characters followed by an empty column (filled with '.').
 *
 * Output:
 * The output should contain exactly one line, the recognized digits in one
 * line.
 *
 * Solution:
 * By checking the fourth row, we can uniquely identify the numbers.
 */

#include "Volume126/p12658.h"

Void p12658_main() {
  Char digits[5][10 * (3 + 1) + 1];

  var n = 0;
  scanf("%d", &n);

  var i = 0;
  for (; i < 5; i += 1) {
    scanf("%s", digits[i]);
  }

  var result = 0ll;
  let count = 4 * n;
  for (i = 0; i < count; i += 4) {
    if (digits[3][i] == '.' && digits[3][i + 2] == '.') {
      result = result * 10 + 1;
    } else if (digits[3][i] == '*' && digits[3][i + 2] == '.') {
      result = result * 10 + 2;
    } else {
      result = result * 10 + 3;
    }
  }
  
  printf("%lld\n", result);
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
