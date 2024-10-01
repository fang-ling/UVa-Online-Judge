/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p12720.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: September 21, 2024                             \ \ \_/__ \_\ \_  __  */
/*                                                       \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the hxy open source project.
 *
 * Copyright (c) 2024 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */

/*
 * 12720 Algorithm of Phil
 *
 * Phil is learning a new algorithm which wasn’t taught in his algorithms
 * classes. However, he is not sure whether he implemented it the right way, so
 * he would really appreciate if you could implement it so that he can compare
 * the outputs.
 *
 * The algorithm starts with a binary string A and an empty string S. The
 * algorithm consists of multiple steps. In each step, A and S are modified as
 * follows:
 *   * If the number of bits in A is odd, then the middle bit of A is added to
 *     the end of S and removed from A.
 *   * If the number of bits in A is even, then both middle bits of A are
 *     compared. The bigger one (anyone in case of a tie) is added to the end of
 *     S and removed from A.
 *   * If after some step the string A gets empty, the algorithm terminates.
 *     The algorithm’s return is the decimal representation of the number
 *     represented by S.
 *
 * A bit a is bigger than a bit b if a is 1 and b is 0.
 *
 * Input:
 * The first line contains T (T ≤ 500) — the number of test cases, after this
 * line T test cases follows. Each test case consists of one line containing a
 * binary string A (1 ≤ |A| ≤ 10**5), representing the algorithm’s input.
 *
 * Output:
 * For each case print a line containing 'Case #X: Y', where X is the case
 * number, starting at 1, and Y is the algorithm’s return for the given input,
 * modulo 1000000007 (10**9 + 7).
 *
 * Solution:
 * We use two arrays: one for the first half of A and another for the
 * second half (in reverse order) to emulate the whole algorithm. Rebalance the
 * two arrays if either of them is empty.
 */

#include "Volume127/p12720.h"

/*
 *    index: 0123 45678
 * Example: "1234|56789", "" becomes
 * array1: "1234"
 * array2: "98765" (reversed)
 */
static Void p12720_rebalance(struct Array* full, struct Array* empty) {
  /* move the second half of full to empty */
  let empty_count = full->count / 2;
  var i = 0ll;
  for (i = full->count - 1; i >= empty_count; i -= 1) {
    var last_element = 0;
    array_remove_last(full, &last_element);
    array_append(empty, &last_element);
  }
}

static Int p12720_update_result(Int origin, Int8 c) {
  return ((origin << 1) | (c - '0')) % (1000000000ll + 7);
}

Void p12720_main() {
  var input = (Int8*)malloc(sizeof(Int8) * (100000 + 1));
  let left = array_init(sizeof(Int8));
  let right = array_init(sizeof(Int8));
  
  var T = 0;
  scanf("%d", &T);
  
  var case_number = 0;
  for (case_number = 1; case_number <= T; case_number += 1) {
    /* Init */
    array_remove_all(left, false);
    array_remove_all(right, false);
    
    /* Input */
    scanf("%s", input);
    var c = input;
    while (*c != '\0') {
      array_append(left, c);
      c += 1;
    }
    p12720_rebalance(left, right);
    
    var output = 0ll;
    while (left->count + right->count != 0) {
      if (left->count < right->count) {
        /* Odd case A: middle is in right */
        var middle = '0';
        array_remove_last(right, &middle);
        output = p12720_update_result(output, middle);
      } else if (left->count > right->count) {
        /* Odd case B: middle is in left */
        var middle = '0';
        array_remove_last(left, &middle);
        output = p12720_update_result(output, middle);
      } else {
        /* Even case */
        var middle_left = '0';
        var middle_right = '0';
        array_read(left, left->count - 1, &middle_left);
        array_read(right, right->count - 1, &middle_right);
        if (middle_left > middle_right) {
          array_remove_last(left, NULL);
          output = p12720_update_result(output, middle_left);
        } else {
          array_remove_last(right, NULL);
          output = p12720_update_result(output, middle_right);
        }
      }
      /* Rebalance arrays if needed */
      if (left->count == 0 && right->count != 0) {
        p12720_rebalance(right, left);
      } else if (left->count != 0 && right->count == 0) {
        p12720_rebalance(left, right);
      }
    }
    
    /* Output */
    printf("Case #%d: %lld\n", case_number, output);
  }
  
  free(input);
  free(left);
  free(right);
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
