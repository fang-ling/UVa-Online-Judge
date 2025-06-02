/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10370.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: May 3, 2025                                    \ \ \_/__ \_\ \_  __  */
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
 * 10370 Above Average
 *
 * It is said that 90% of frosh expect to be above average in their class. You
 * are to provide a reality check.
 *
 * Input:
 * The first line of standard input contains an integer C, the number of test
 * cases. C datasets follow. Each data set begins with an integer, N, the number
 * of people in the class (1 ≤ N ≤ 1000). N integers follow, separated by spaces
 * or newlines, each giving the final grade (an integer between 0 and 100) of a
 * student in the class.
 *
 * Output:
 * For each case you are to output a line giving the percentage of students
 * whose grade is above average, rounded to 3 decimal places.
 */

#include "Volume103/p10370.h"

Void p10370_sum_closure(AnyObject accumulator,
                        AnyConstantObject element,
                        AnyObject* closure_capture_list,
                        AnyObject result) {
  var _accumulator = (Int32*)accumulator;
  var _element = (Int32*)element;

  *_accumulator += *_element;

  memcpy(result, _accumulator, sizeof(Int32));
}

Void p10370_main() {
  var case_count = 0;
  scanf("%d", &case_count);

  var scores = array_init(sizeof(Int32));

  while (case_count--) {
    var n = 0;
    scanf("%d", &n);

    array_remove_all(scores, true);

    while (n--) {
      var score = 0;
      scanf("%d", &score);
      array_append(scores, &score);
    }

    /* Find average */
    var sum = 0;
    array_reduce(scores, &sum, p10370_sum_closure, NULL, &sum);
    var average = (Double)sum / scores->count;

    var above_count = 0;
    var i = 0;
    for (; i < scores->count; i += 1) {
      var score = 0;
      array_read(scores, i, &score);
      if ((Double)score > average) {
        above_count += 1;
      }
    }

    printf("%.3lf%%\n", ((Double)above_count / scores->count) * 100);
  }

  array_deinit(scores);
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
