/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11687.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 26, 2024                               \ \ \_/__ \_\ \_  __  */
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
 * 11687 Digits
 *
 * A googol written out in decimal has 101 digits. A googolplex has one plus a
 * googol digits. That’s a lot of digits!
 *
 * Given any number x0, define a sequence using the following recurrence:
 * x_{i+1} = the number of digits in the decimal representation of x_i
 *
 * Your task is to determine the smallest positive i such that x_i = x_{i−1}.
 *
 * Input:
 * Input consists of several lines. Each line contains a value of x_0. Every
 * value of x_0 is non-negative and has no more than one million digits. The
 * last line of input contains the word 'END'.
 *
 * Output:
 * For each value of x_0 given in the input, output one line containing the
 * smallest positive i such that
 * x_i = x{i−1}.
 *
 * Solution:
 * For example:
 *   x_0 = 42
 *   x_1 = # digits of 42 = 2
 *   x_2 = # digits of 2 = 1
 *   x_3 = # digits of 1 = 1, now we have x_3 == x_2
 *
 * Simple recursion.
 */

#include "Volume116/p11687.h"

var p11687_depth = 0;

Void p11687_count_digits(Char* number) {
  p11687_depth += 1;
  
  var count = (Int64)strlen(number);
  if (count == 1 && number[0] == '1') {
    return;
  }
  
  var string = (Char*)malloc(32 * sizeof(Int8));
  sprintf(string, "%lld", count);
  p11687_count_digits(string);
  
  free(string);
}

Void p11687_main() {
  var input = (Char*)malloc(1000000 * sizeof(Int8));
  
  while (scanf("%s", input) == 1 && input[0] != 'E') {
    p11687_depth = 0;
    p11687_count_digits(input);
    printf("%d\n", p11687_depth);
  }
  
  free(input);
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
