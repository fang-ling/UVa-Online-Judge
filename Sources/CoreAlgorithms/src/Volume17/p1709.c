/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p1709.c                                              /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 20, 2024                               \ \ \_/__ \_\ \_  __  */
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
 * 1709 Amalgamated Artichokes
 *
 * Fatima Cynara is an analyst at Amalgamated Artichokes (AA). As with any
 * company, AA has had some very good times as well as some bad ones. Fatima
 * does trending analysis of the stock prices for AA, and she wants to determine
 * the largest decline in stock prices over various time spans.
 * For example, if over a span of time the stock prices were 19, 12, 13, 11, 20
 * and 14, then the largest decline would be 8 between the first and fourth
 * price. If the last price had been 10 instead of 14, then the largest decline
 * would have been 10 between the last two prices.
 *
 * Fatima has done some previous analyses and has found that the stock price
 * over any period of time can be modelled reasonably accurately with the
 * following equation:
 *
 *   price(k) = p * (sin(a * k + b) + cos(c * k + d) + 2)
 *
 * where p, a, b, c and d are constants. Fatima would like you to write a
 * program to determine the largest price decline over a given sequence of
 * prices. You have to consider the prices only for integer values of k.
 *
 * Input:
 * The input file contains several test cases, each of them as described below.
 * The input consists of a single line containing 6 integers p (1 ≤ p ≤ 1000),
 * a, b, c, d (0 ≤ a, b, c, d ≤ 1000) and n (1 ≤ n ≤ 10**6). The first 5
 * integers are described above. The sequence of stock prices to consider is
 * price(1), price(2), . . . , price(n).
 *
 * Output:
 * For each test case, display the maximum decline in the stock prices. If there
 * is no decline, display the number '0'. Your output should have an absolute or
 * relative error of at most 10**−6.
 *
 * Solution:
 * A linear scan.
 */

#include "Volume17/p1709.h"

#define price(k, p, a, b, c, d)                                   \
          (p) * (sin((a) * (k) + (b)) + cos((c) * (k) + (d)) + 2)

Void p1709_main() {
  var p = 0;
  var a = 0;
  var b = 0;
  var c = 0;
  var d = 0;
  var n = 0;
  while (scanf("%d %d %d %d %d %d", &p, &a, &b, &c, &d, &n) == 6) {
    var current_max = 0.0;
    var result = 0.0;
    
    var i = 0;
    for (i = 1; i <= n; i += 1) {
      var current_price = price(i, p, a, b, c, d);
      current_max = _max(current_max, current_price);
      result = _max(result, current_max - current_price);
    }
    
    printf("%.6lf\n", result);
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
