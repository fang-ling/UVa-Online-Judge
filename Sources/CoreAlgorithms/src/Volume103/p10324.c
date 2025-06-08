/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10324.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: June 8, 2025                                   \ \ \_/__ \_\ \_  __  */
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
 * 10324 Zeros and Ones
 *
 * Given a string of 0's and 1's up to 1000000 characters long and indices i
 * and j, you are to answer a question whether all characters between position
 * min(i, j) and position max(i, j) (inclusive) are the same.
 *
 * Input:
 * There are multiple cases on input. The first line of each case gives a string
 * of 0's and 1's. The next line contains a positive integer n giving the number
 * of queries for this case. The next n lines contain queries, one per line.
 * Each query is given by two non-negative integers, i and j. For each query,
 * you are to print 'Yes' if all characters in the string between position
 * min(i, j) and position max(i, j) are the same, and 'No' otherwise.
 *
 * Output:
 * Each case on output should start with a heading as in the sample below. The
 * input ends with an empty string that is a line containing only the new line
 * character, this string should not be processed. The input may also with end
 * of file. So keep check for both.
 */

#include "Volume103/p10324.h"

Void p10324_main() {
  var string = (Int8*)malloc(sizeof(Int8) * 1000001);
  var group = (Int32*)malloc(sizeof(Int32) * 1000000);

  var case_number = 1;
  while (scanf("%s", string) == 1) {
    printf("Case %d:\n", case_number);

    /* Preprocess the input to groups. */
    var i = 0;
    var count = (Int32)strlen(string);
    var group_index = 0;
    var last_character = (Int8)-1;
    for (; i < count; i += 1) {
      if (last_character != string[i]) {
        group_index += 1;
        last_character = string[i];
      }
      group[i] = group_index;
    }

    var query_count = 0;
    scanf("%d", &query_count);
    while (query_count--) {
      var j = 0;
      scanf("%d %d", &i, &j);
      if (i > j) { /* Swap i, j if i > j. */
        var delta = i;
        i = j;
        j = delta;
      }
      printf("%s\n", group[i] == group[j] ? "Yes" : "No");
    }

    case_number += 1;
  }

  free(group);
  free(string);
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
