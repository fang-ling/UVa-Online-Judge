/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p108.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: May 1, 2025                                    \ \ \_/__ \_\ \_  __  */
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
 * 108 Maximum Sum
 *
 * A problem that is simple to solve in one dimension is often much more
 * difficult to solve in more than one dimension. Consider satisfying a boolean
 * expression in conjunctive normal form in which each conjunct consists of
 * exactly 3 disjuncts. This problem (3-SAT) is NP-complete. The problem 2-SAT
 * is solved quite efficiently, however. In contrast, some problems belong to
 * the same complexity class regardless of the dimensionality of the problem.
 *
 * Given a 2-dimensional array of positive and negative integers, find the
 * sub-rectangle with the largest sum. The sum of a rectangle is the sum of all
 * the elements in that rectangle. In this problem the sub-rectangle with the
 * largest sum is referred to as the maximal sub-rectangle.
 *
 * A sub-rectangle is any contiguous sub-array of size 1 × 1 or greater located
 * within the whole array. As an example, the maximal sub-rectangle of the
 * array:
 *
 *      0 −2 −7  0
 *      9  2 −6  2
 *     −4  1 −4  1
 *     −1  8  0 −2
 *
 * is in the lower-left-hand corner:
 *
 *         9 2
 *        −4 1
 *        −1 8
 *
 * and has the sum of 15.
 *
 * Input:
 * The input consists of an N × N array of integers.
 *
 * The input begins with a single positive integer N on a line by itself
 * indicating the size of the square two dimensional array. This is followed by
 * N**2 integers separated by white-space (newlines and spaces). These N**2
 * integers make up the array in row-major order (i.e., all numbers on the first
 * row, left-to-right, then all numbers on the second row, left-to-right, etc.).
 * N may be as large as 100. The numbers in the array will be in the range
 * [−127, 127].
 *
 * Output:
 * The output is the sum of the maximal sub-rectangle.
 */

#include "Volume1/p108.h"

Void p108_main() {
  var n = 0;
  scanf("%d", &n);
  var array = array_init(sizeof(Int32));
  var prefix_sum = array_init(sizeof(Int32));

  var count = n * n;
  var i = 0;
  for (; i < count; i += 1) {
    var delta = 0;
    scanf("%d", &delta);
    array_append(array, &delta);
  }

  /* Fill 0 in prefix sum array */
  for (i = 0; i <= n; i += 1) {
    var j = 0;
    for (; j <= n; j += 1) {
      var zero = 0;
      array_append(prefix_sum, &zero);
    }
  }

  /* Compute 2d prefix sum  */
  for (i = 1; i <= n; i += 1) {
    var j = 1;
    for (; j <= n; j += 1) {
      var a = 0;
      var b = 0;
      var c = 0;
      var d = 0;
      array_read(prefix_sum, (i - 1) * (n + 1) + j, &a);
      array_read(prefix_sum, i * (n + 1) + j - 1, &b);
      array_read(prefix_sum, (i - 1) * (n + 1) + j - 1, &c);
      array_read(array, (i - 1) * n + j - 1, &d);

      var s_ij = d + a + b - c;
      array_write(prefix_sum, i * (n + 1) + j, &s_ij);
    }
  }

  var max_sum = 0;
  array_read(array, 0, &max_sum);
  var r1 = 0;
  for (r1 = 0; r1 < n; r1 += 1) {
    var c1 = 0;
    for (; c1 < n; c1 += 1) {
      var r2 = r1;
      for (; r2 < n; r2 += 1) {
        var c2 = c1;
        for (; c2 < n; c2 += 1) {
          var a = 0;
          var b = 0;
          var c = 0;
          var d = 0;
          array_read(prefix_sum, (r2 + 1) * (n + 1) + c2 + 1, &a);
          array_read(prefix_sum, r1 * (n + 1) + c2 + 1, &b);
          array_read(prefix_sum, (r2 + 1) * (n + 1) + c1, &c);
          array_read(prefix_sum, r1 * (n + 1) + c1, &d);
          max_sum = _max(max_sum, a - b - c + d);
        }
      }
    }
  }

  printf("%d\n", max_sum);

  array_deinit(array);
  array_deinit(prefix_sum);
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
