/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10696.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: May 4, 2025                                    \ \ \_/__ \_\ \_  __  */
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
 * 10696 f91
 *
 * McCarthy is a famous theorician of computer science. In his work, he defined
 * a recursive function, called f91, that takes as input a positive integer N
 * and returns a positive integer defined as follows:
 *
 *   • If N ≤ 100, then f91(N) = f91(f91(N + 11));
 *   • If N ≥ 101, then f91(N) = N − 10.
 *
 * Write a program, that computes McCarthy's f91.
 *
 * Input:
 * The input tests will consist of a series of positive integers, each integer
 * is at most 1,000,000. There will be at most 250,000 test cases. Each number
 * is on a line on its own. The end of the input is reached when the number '0'
 * is met. The number '0' shall not be considered as part of the test set.
 *
 * Output:
 * The program shall output each result on a line by its own, following the
 * format given in the sample output.
 */

#include "Volume106/p10696.h"

Int32 p10696_f91(Int32 n) {
  if (n >= 101) {
    return n - 10;
  }

  return p10696_f91(p10696_f91(n + 11));
}

Void p10696_main() {
  var n = 0;
  while (scanf("%d", &n) == 1 && n != 0) {
    printf("f91(%d) = %d\n", n, p10696_f91(n));
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
