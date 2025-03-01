/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p113.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: February 25, 2025                              \ \ \_/__ \_\ \_  __  */
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
 * 113 Power of Cryptography
 *
 * Current work in cryptography involves (among other things) large prime
 * numbers and computing powers of numbers modulo functions of these primes.
 * Work in this area has resulted in the practical use of results from number
 * theory and other branches of mathematics once considered to be of only
 * theoretical interest.
 *
 * This problem involves the efficient computation of integer roots of numbers.
 *
 * Given an integer n ≥ 1 and an integer p ≥ 1 you are to write a program that
 * determines n√p, the positive n-th root of p. In this problem, given such
 * integers n and p, p will always be of the form k**n for an integer k (this
 * integer is what your program must find).
 *
 * Input:
 * The input consists of a sequence of integer pairs n and p with each integer
 * on a line by itself. For all such pairs 1 ≤ n ≤ 200, 1 ≤ p < 10**101 and
 * there exists an integer k, 1 ≤ k ≤ 10**9 such that k**n = p.
 *
 * Output:
 * For each integer pair n and p the value n√p should be printed, i.e., the
 * number k such that k**n = p.
 */

#include "Volume1/p113.h"

Void p113_main() {
  var n = 0.0;
  var p = 0.0;
  while (scanf("%lf %lf", &n, &p) == 2) {
    printf("%.0lf\n", pow(p, 1.0 / n));
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
