/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p374.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: May 2, 2025                                    \ \ \_/__ \_\ \_  __  */
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
 * 374 Big Mod
 *
 * Calculate
 *               R := B**P mod M
 * for large values of B, P , and M using an efficient algorithm. (That's right,
 * this problem has a time dependency !!!.)
 *
 * Input:
 * The input will contain several test cases, each of them as described below.
 * Consecutive test cases are separated by a single blank line.
 *
 * Three integer values (in the order B, P, M ) will be read one number per
 * line. B and P are integers in the range 0 to 2147483647 inclusive. M is an
 * integer in the range 1 to 46340 inclusive.
 *
 * Output:
 * For each test, the result of the computation. A single integer on a line by
 * itself.
 */

#include "Volume3/p374.h"

Void p374_main() {
  var b = 0ll;
  var p = 0ll;
  var m = 0ll;
  while (scanf("%lld %lld %lld", &b, &p, &m) == 3) {
    printf("%lld\n", _pow_mod(b, p, m));
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
