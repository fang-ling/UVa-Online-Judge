/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11614.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 6, 2024                                \ \ \_/__ \_\ \_  __  */
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
 * 11614 Etruscan Warriors Never Play Chess
 *
 * A troop of Etruscan warriors is organized as follows. In the first row, there
 * is only one warrior; then, the second row contains two warriors; the third
 * row contains three warriors, and so on. In general, each row i contains i
 * warriors.
 *
 * We know the number of Etruscan warriors of a given troop. You have to compute
 * the number of rows in which they are organized.
 *
 * Please note that there may be some remaining warriors (this could happen if
 * they are not enough to form the next row). For example, 3 warriors are
 * organized in 2 rows. With 6 warriors you can form 3 rows; but you can also
 * form 3 rows with 7, 8 or 9 warriors.
 *
 * Input:
 * The first line of the input contains an integer indicating the number of test
 * cases. For each test case, there is a single integer, n, indicating the
 * number of Etruscan warriors. You can assume that 0 ≤ n ≤ 10**18.
 *
 * Output:
 * For each test case, the output should contain a single integer indicating the
 * number of rows that can be formed.
 *
 * Solution:
 *       row
 * @      1
 * @@     2
 * @@@    3
 * @@@@   4
 * @...
 *
 * n = (1 + 2 + 3 + ... + j) + remainder, with 0 <= remainder <= j + 1
 * i.e. we need to find the max j such that (1 + j) * j / 2 <= n
 * Now we can do binary search.
 */

#include "Volume116/p11614.h"

Void p11614_main() {
  var cases = 0;
  scanf("%d", &cases);
  while (cases--) {
    var n = 0ll;
    scanf("%lld", &n);
    
    var lower_bound = 0ll;
    var upper_bound = (Int64)sqrt(n) * 2 + 1;
    var j = 0ll;
    /* Make sure that lower_bound < upper_bound */
    while (lower_bound + 1 < upper_bound) {
      j = (lower_bound + upper_bound) / 2;
      if ((1 + j) * j / 2 > n) {
        upper_bound = j;
      } else {
        lower_bound = j;
      }
    }
    printf("%lld\n", lower_bound);
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
