/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p1203.c                                              /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: February 6, 2025                               \ \ \_/__ \_\ \_  __  */
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
 * 1203 Argus
 *
 * A data stream is a real-time, continuous, ordered sequence of items. Some
 * examples include sensor data, Internet traffic, financial tickers, on-line
 * auctions, and transaction logs such as Web usage logs and telephone call
 * records. Likewise, queries over streams run continuously over a period of
 * time and incrementally return new results as new data arrives. For example, a
 * temperature detection system of a factory warehouse may run queries like the
 * following.
 *
 *   Query-1: "Every five minutes, retrieve the maximum temperature over the
 *            past five minutes."
 *   Query-2: "Return the average temperature measured on each floor over the
 *            past 10 minutes."
 *
 * We have developed a Data Stream Management System called Argus, which
 * processes the queries over the data streams. Users can register queries to
 * the Argus. Argus will keep the queries running over the changing data and
 * return the results to the corresponding user with the desired frequency.
 *
 * For the Argus, we use the following instruction to register a query:
 *
 *   Register Q_num Period
 *
 * Q_num (0 < Qnum ≤ 3000) is query ID-number, and Period (0 < P eriod ≤ 3000)
 * is the interval between two consecutive returns of the result. After Period
 * seconds of register, the result will be returned for the first time, and
 * after that, the result will be returned every P eriod seconds.
 *
 * Here we have several different queries registered in Argus at once. It is
 * confirmed that all the queries have diﬀerent Q num. Your task is to tell the
 * first K queries to return the results. If two or more queries are to return
 * the results at the same time, they will return the results one by one in the
 * ascending order of Q num.
 *
 * Input:
 * The first part of the input are the register instructions to Argus, one
 * instruction per line. You can assume the number of the instructions will not
 * exceed 1000, and all these instructions are executed at the same time. This
 * part is ended with a line of '#'.
 *
 * The second part is your task. This part contains only one line, which is one
 * positive integer K (≤ 10000).
 *
 * Output:
 * You should output the Q num of the first K queries to return the results, one
 * number per line.
 */

#include "Volume12/p1203.h"

struct Query {
  Int32 id;
  Int32 timestamp;
  Int32 period;
};

static Int32 compare(AnyConstantObject _a, AnyConstantObject _b) {
  var a = *(struct Query*)_a;
  var b = *(struct Query*)_b;

  if (a.timestamp == b.timestamp) {
    return b.id - a.id;
  }
  return b.timestamp - a.timestamp;
}

Void p1203_main() {
  var operator = (Int8*)malloc(sizeof(Int8) * 16);
  var heap = binary_heap_init(sizeof(struct Query), compare);

  while (scanf("%s", operator) == 1 && operator[0] != '#') {
    var query = (struct Query) { };
    scanf("%d %d", &query.id, &query.period);
    query.timestamp = query.period;

    binary_heap_insert(heap, &query);
  }

  var k = 0;
  scanf("%d", &k);
  while (k--) {
    var query = (struct Query) { };
    binary_heap_pop_max(heap, &query);
    printf("%d\n", query.id);
    query.timestamp += query.period;
    binary_heap_insert(heap, &query);
  }

  binary_heap_deinit(heap);
  free(operator);
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
