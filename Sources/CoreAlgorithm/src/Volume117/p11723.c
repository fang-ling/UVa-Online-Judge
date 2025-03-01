/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11723.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: December 1, 2024                               \ \ \_/__ \_\ \_  __  */
/*                                                       \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the CoreAlgorithm open source project.
 *
 * Copyright (c) 2024 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */

/*
 * 11723 Numbering Roads!
 *
 * In my country, streets dont have names, each of them are just given a number
 * as name. These numbers are supposed to be unique but that is not always the
 * case. The local government allocates some integers to name the roads and in
 * many case the number of integers allocated is less that the total number of
 * roads. In that case to make road names unique some single character suffixes
 * are used. So roads are named as 1, 2, 3, 1A, 2B, 3C, etc. Of course the
 * number of suffixes is also always limited to 26 (A, B, ..., Z). For example
 * if there are 4 roads and 2 different integers are allocated for naming then
 * some possible assignments of names can be:
 *   1, 2, 1A, 2B
 *   1, 2, 1A, 2C
 *   3, 4, 3A, 4A
 *   1, 2, 1B, 1C
 * Given the number of roads (R) and the numbers of integers allocated for
 * naming (N), your job is to determine minimum how many different suffixes will
 * be required (of all possible namings) to name the streets assuming that no
 * two streets can have same names.
 *
 * Input:
 * The input file can contain up to 10002 lines of inputs. Each line contains
 * two integers R and N (0 < N, R < 10001). Here R is the total number of
 * streets to be named and N denotes number integers allocated for naming.
 *
 * Output:
 * For each line of input produce one line of output. This line contains the
 * serial of output followed by an integer D which denotes the minimum number of
 * suffixes required to name the streets. If it is not possible to name all the
 * streets print 'impossible' instead (without the quotes).
 *
 * Solution:
 * We have (x + 1) * N = R, therefore x = R / N - 1.
 */

#include "Volume117/p11723.h"

Void p11723_main() {
  var integers = 0;
  var roads = 0;
  var case_number = 1;
  while (scanf("%d %d", &roads, &integers) == 2 && roads != 0) {
    let count = (Int32)ceil((Double)roads / integers) - 1;

    if (count >= 27) {
      printf("Case %d: impossible\n", case_number);
    } else {
      printf("Case %d: %d\n", case_number, count);
    }

    case_number += 1;
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
