/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* UVa100.cpp                                           /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: July 19, 2025                                  \ \ \_/__ \_\ \_  __  */
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
 * 100 The 3n + 1 problem
 *
 * Problems in Computer Science are often classified as belonging to a certain
 * class of problems (e.g., NP, Unsolvable, Recursive). In this problem you will
 * be analyzing a property of an algorithm whose classification is not known for
 * all possible inputs.
 *
 * Consider the following algorithm:
 *   1 input n
 *   2 print n
 *   3 if n = 1 then STOP
 *   4   if n is odd then n ←− 3n + 1
 *   5   else n ←− n/2
 *   6 GOTO 2
 *
 * Given the input 22, the following sequence of numbers will be printed
 *   22 11 34 17 52 26 13 40 20 10 5 16 8 4 2 1
 *
 * It is conjectured that the algorithm above will terminate (when a 1 is
 * printed) for any integral input value. Despite the simplicity of the
 * algorithm, it is unknown whether this conjecture is true. It has been
 * verified, however, for all integers n such that 0 < n < 1, 000, 000 (and, in
 * fact, for many more numbers than this.)
 *
 * Given an input n, it is possible to determine the number of numbers printed
 * before and including the 1 is printed. For a given n this is called the
 * cycle-length of n. In the example above, the cycle length of 22 is 16.
 *
 * For any two numbers i and j you are to determine the maximum cycle length
 * over all numbers between and including both i and j.
 *
 * Input:
 * The input will consist of a series of pairs of integers i and j, one pair of
 * integers per line. All integers will be less than 10,000 and greater than 0.
 *
 * You should process all pairs of integers and for each pair determine the
 * maximum cycle length over all integers between and including i and j.
 *
 * You can assume that no operation overflows a 32-bit integer.
 *
 * Output:
 * For each pair of input integers i and j you should output i, j, and the
 * maximum cycle length for integers between and including i and j. These three
 * numbers should be separated by at least one space with all three numbers on
 * one line and with one line of output for each line of input. The integers i
 * and j must appear in the output in the same order in which they appeared in
 * the input and should be followed by the maximum cycle length (on the same
 * line).
 */

#include "UVa100.hpp"

func calculate_cycle_count(Int64 x) -> Int64 {
  var count = Int64(0);

  while (x != 1) {
    count += 1;
    if (x % 2 == 0) {
      x /= 2;
    } else {
      x = 3 * x + 1;
    }
  }

  return count;
}

func uva100() -> Void {
  var i = Int64(0);
  var j = Int64(0);
  while (scan(&i) && scan(&j)) {
    let left = min(i, j);
    let right = max(i, j);

    var max_cycle_count = Int64(0);
    for (var k = left; k <= right; k += 1) {
      max_cycle_count = max(max_cycle_count, calculate_cycle_count(k));
    }

    print(i, " ");
    print(j, " ");
    print(max_cycle_count + 1);
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
