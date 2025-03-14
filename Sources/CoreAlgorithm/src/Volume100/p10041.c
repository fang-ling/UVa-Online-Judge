/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10041.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: March 12, 2025                                 \ \ \_/__ \_\ \_  __  */
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
 * 10041 Vito's family
 *
 * The world-known gangster Vito Deadstone is moving to New York. He has a very
 * big family there, all of them living in Lamafia Avenue. Since he will visit
 * all his relatives very often, he is trying to find a house close to them.
 *
 * Vito wants to minimize the total distance to all of them and has blackmailed
 * you to write a program that solves his problem.
 *
 * Input:
 * The input consists of several test cases. The first line contains the number
 * of test cases.
 *
 * For each test case you will be given the integer number of relatives r
 * (0 < r < 500) and the street numbers (also integers) s1, s2, ..., si, ..., sr
 * where they live (0 < si < 30000). Note that several relatives could live in
 * the same street number.
 *
 * Output:
 * For each test case your program must write the minimal sum of distances from
 * the optimal Vito's house to each one of his relatives. The distance between
 * two street numbers si and sj is d_ij= |si − sj|.
 */

#include "Volume100/p10041.h"

static Int32 compare(AnyConstantObject _lhs, AnyConstantObject _rhs) {
  var lhs = *(Int32*)_lhs;
  var rhs = *(Int32*)_rhs;

  if (lhs < rhs) {
    return -1;
  } else if (lhs > rhs) {
    return 1;
  }
  return 0;
}

Void p10041_main() {
  var case_count = 0;
  scanf("%d", &case_count);

  var streets = array_init(sizeof(Int32));
  while (case_count--) {
    array_remove_all(streets, true);

    var r = 0;
    scanf("%d", &r);
    while (r--) {
      var delta = 0;
      scanf("%d", &delta);
      array_append(streets, &delta);
    }

    array_sort(streets, compare);
    var median = 0;
    if (streets->count % 2 != 0) {
      array_read(streets, streets->count / 2, &median);
    } else {
      array_read(streets, streets->count / 2 - 1, &median);
    }

    var sum = 0;
    var i = 0;
    for (; i < streets->count; i += 1) {
      var delta = 0;
      array_read(streets, i, &delta);
      sum += _abs(median - delta);
    }

    printf("%d\n", sum);
  }

  array_deinit(streets);
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
