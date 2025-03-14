/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p424.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: January 1, 2025                                \ \ \_/__ \_\ \_  __  */
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
 * 424 Integer Inquiry
 *
 * One of the first users of BIT's new supercomputer was Chip Diller. He
 * extended his exploration of powers of 3 to go from 0 to 333 and he explored
 * taking various sums of those numbers.
 *
 * "This supercomputer is great," remarked Chip. "I only wish Timothy were here
 * to see these results." (Chip moved to a new apartment, once one became
 * available on the third floor of the Lemon Sky apartments on Third Street.)
 *
 * Input:
 * The input will consist of at most 100 lines of text, each of which contains a
 * single VeryLongInteger. Each VeryLongInteger will be 100 or fewer characters
 * in length, and will only contain digits (no VeryLongInteger will be
 * negative). The final input line will contain a single zero on a line by
 * itself.
 *
 * Output:
 * Your program should output the sum of the VeryLongIntegers given in the
 * input.
 *
 * Solution:
 * A + B problem (BigInteger ver).
 */

#include "Volume4/p424.h"

Void p424_main() {
  Int8 buffer[128];

  var sum = big_integer_init_from_string("0", 10);
  while (scanf("%s", buffer) == 1) {
    var number = big_integer_init_from_string(buffer, 10);

    var delta = big_integer_add(sum, number);
    big_integer_deinit(sum);
    sum = delta;
  }

  var result = big_integer_to_string(sum, 10, false);
  printf("%s\n", result);

  free(result);
  big_integer_deinit(sum);
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
