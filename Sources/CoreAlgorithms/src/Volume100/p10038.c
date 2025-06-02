/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10038.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: February 2, 2025                               \ \ \_/__ \_\ \_  __  */
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
 * 10038 Jolly Jumpers
 *
 * A sequence of n > 0 integers is called a jolly jumper if the absolute values
 * of the difference between successive elements take on all the values 1
 * through n − 1. For instance,
 *
 *   1 4 2 3
 *
 * is a jolly jumper, because the absolutes differences are 3, 2, and 1
 * respectively. The definition implies that any sequence of a single integer is
 * a jolly jumper. You are to write a program to determine whether or not each
 * of a number of sequences is a jolly jumper.
 *
 * Input:
 * Each line of input contains an integer n ≤ 3000 followed by n integers
 * representing the sequence.
 *
 * Output:
 * For each line of input, generate a line of output saying 'Jolly' or
 * 'Not jolly'.
 */

#include "Volume100/p10038.h"

static Int32 compare(AnyConstantObject lhs, AnyConstantObject rhs) {
  var a = *(Int32*)lhs;
  var b = *(Int32*)rhs;
  return a - b;
}

Void p10038_main() {
  var difference = array_init(sizeof(Int32));
  var array = array_init(sizeof(Int32));

  var n = 0;
  while (scanf("%d", &n) == 1) {
    array_remove_all(array, true);
    array_remove_all(difference, true);

    var delta = 0;
    while (n--) {
      scanf("%d", &delta);
      array_append(array, &delta);
    }

    var i = 1;
    for (; i < array->count; i += 1) {
      var alpha = 0;
      var beta = 0;
      array_read(array, i - 1, &alpha);
      array_read(array, i, &beta);

      delta = _abs(beta - alpha);
      array_append(difference, &delta);
    }

    array_sort(difference, compare);

    var is_jolly = true;
    for (i = 0; i < difference->count; i += 1) {
      array_read(difference, i, &delta);
      if (i + 1 != delta) {
        is_jolly = false;
        break;
      }
    }

    printf("%s\n", is_jolly ? "Jolly" : "Not jolly");
  }

  array_deinit(difference);
  array_deinit(array);
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
