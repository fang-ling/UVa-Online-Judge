/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11172.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 10, 2024                               \ \ \_/__ \_\ \_  __  */
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
 * 11172 Relational Operators
 *
 * Some operators checks about the relationship between two values and these
 * operators are called relational operators. Given two numerical values your
 * job is just to find out the relationship between them that is (i) First one
 * is greater than the second (ii) First one is less than the second or (iii)
 * First and second one is equal.
 *
 * Input:
 * First line of the input file is an integer t (t < 15) which denotes how many
 * sets of inputs are there. Each of the next t lines contain two integers a and
 * b (|a|, |b| < 1000000001).
 *
 * Output:
 * For each line of input produce one line of output. This line contains any one
 * of the relational operators '>', '<' or '=', which indicates the relation
 * that is appropriate for the given two numbers.
 *
 * Solution:
 * Super easy problem.
 */

#include "Volume111/p11172.h"

Void p11172_main() {
  var case_count = 0;
  scanf("%d", &case_count);
  while (case_count--) {
    var a = 0;
    var b = 0;
    scanf("%d %d", &a, &b);
    if (a == b) {
      printf("=\n");
    } else {
      printf("%s\n", a < b ? "<" : ">");
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
