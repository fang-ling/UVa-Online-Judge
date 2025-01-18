/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10106.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: January 14, 2025                               \ \ \_/__ \_\ \_  __  */
/*                                                       \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the hxy open source project.
 *
 * Copyright (c) 2024-2025 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */

/*
 * 10106 Product
 *
 * The problem is to multiply two integers X, Y . (0 ≤ X, Y < 10**250)
 *
 * Input:
 * The input will consist of a set of pairs of lines. Each line in pair contains
 * one multiplyer.
 *
 * Output:
 * For each input pair of lines the output line should consist one integer the
 * product.
 *
 * Solution:
 * A * B problem (BigInteger ver.)
 */

#include "Volume101/p10106.h"

Void p10106_main() {
  Char buffer1[256];
  Char buffer2[256];

  while (scanf("%s %s", buffer1, buffer2) == 2) {
    var lhs = big_integer_init_from_string(buffer1, 10);
    var rhs = big_integer_init_from_string(buffer2, 10);

    var product = big_integer_multiply(lhs, rhs);
    var result = big_integer_to_string(product, 10, false);

    printf("%s\n", result);

    big_integer_deinit(lhs);
    big_integer_deinit(rhs);
    big_integer_deinit(product);
    free(result);
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
