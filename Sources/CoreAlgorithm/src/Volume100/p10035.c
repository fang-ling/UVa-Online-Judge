/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10035.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: February 12, 2025                              \ \ \_/__ \_\ \_  __  */
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
 * 10035 Primary Arithmetic
 *
 * Children are taught to add multi-digit numbers from right-to-left one digit
 * at a time. Many find the "carry" operation - in which a 1 is carried from one
 * digit position to be added to the next - to be a significant challenge. Your
 * job is to count the number of carry operations for each of a set of addition
 * problems so that educators may assess their difficulty.
 *
 * Input:
 * Each line of input contains two unsigned integers less than 10 digits. The
 * last line of input contains '0 0'.
 *
 * Output:
 * For each line of input except the last you should compute and print the
 * number of carry operations that would result from adding the two numbers, in
 * the format shown below.
 */

#include "Volume100/p10035.h"

Void p10035_main() {
  var lhs = (Char*)malloc(sizeof(Char) * 16);
  var rhs = (Char*)malloc(sizeof(Char) * 16);

  while (scanf("%s %s", lhs, rhs) == 2) {
    var lhs_count = (Int32)strlen(lhs);
    var rhs_count = (Int32)strlen(rhs);

    if (lhs[0] == '0' && lhs_count == 1 && rhs[0] == '0' && rhs_count == 1) {
      break;
    }

    /* Make both lhs & rhs same length. */
    if (lhs_count < rhs_count) {
      let difference = rhs_count - lhs_count;
      memmove(lhs + difference, lhs, lhs_count * sizeof(Char));

      var i = 0;
      for (; i < difference; i += 1) {
        lhs[i] = '0';
      }
      lhs_count = rhs_count;
    } else if (rhs_count < lhs_count) {
      let difference = lhs_count - rhs_count;
      memmove(rhs + difference, rhs, rhs_count * sizeof(Char));

      var i = 0;
      for (; i < difference; i += 1) {
        rhs[i] = '0';
      }
      rhs_count = lhs_count;
    }

    var carry_count = 0;
    var carry = 0;
    var i = lhs_count - 1;
    for (; i >= 0; i -= 1) {
      carry += (lhs[i] - '0') + (rhs[i] - '0');

      if (carry >= 10) {
        carry_count += 1;
      }
      carry /= 10;
    }

    if (carry_count == 0) {
      printf("No carry operation.\n");
    } else {
      printf("%d carry operation%s.\n",
             carry_count,
             carry_count == 1 ? "" : "s");
    }
  }

  free(lhs);
  free(rhs);
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
