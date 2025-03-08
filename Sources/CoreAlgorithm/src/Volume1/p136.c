/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p136.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: March 8, 2025                                  \ \ \_/__ \_\ \_  __  */
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
 * 136 Ugly Numbers
 *
 * Ugly numbers are numbers whose only prime factors are 2, 3 or 5. The sequence
 *
 *   1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, ...
 *
 * shows the first 11 ugly numbers. By convention, 1 is included.
 *
 * Write a program to find and print the 1500'th ugly number.
 *
 * Input:
 * There is no input to this program.
 *
 * Output:
 * Output should consist of a single line as shown below, with '<number>'
 * replaced by the number computed.
 */

#include "Volume1/p136.h"

static Int32 compare(AnyConstantObject _lhs, AnyConstantObject _rhs) {
  var lhs = *(Int64*)_lhs;
  var rhs = *(Int64*)_rhs;

  if (lhs < rhs) {
    return -1;
  } else if (lhs > rhs) {
    return 1;
  }
  return 0;
}

Void p136_main() {
  var set = red_black_tree_init(sizeof(Int64), 0, compare);

  var key = 1ll;
  red_black_tree_insert(set, &key, NULL);

  var i = 0;
  for (; i < 1500; i += 1) {
    var min = 0ll;
    red_black_tree_min(set, &min, NULL);
    red_black_tree_remove(set, &min, NULL);

    if (i == 1499) {
      printf("The 1500'th ugly number is %lld.\n", min);
      break;
    }

    key = min * 2;
    red_black_tree_insert(set, &key, NULL);
    key = min * 3;
    red_black_tree_insert(set, &key, NULL);
    key = min * 5;
    red_black_tree_insert(set, &key, NULL);
  }

  red_black_tree_deinit(set);
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
