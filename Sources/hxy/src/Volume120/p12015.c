/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p12015.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: November 12, 2024                              \ \ \_/__ \_\ \_  __  */
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
 * 12015 Google is Feeling Lucky
 *
 * Google is one of the most famous Internet search engines which hosts and
 * develops a number of Internet-based services and products. On its search
 * engine website, an interesting button "I'm feeling lucky" attracts our eyes.
 * This feature could allow the user skip the search result page and goes
 * directly to the first ranked page. Amazing! It saves a lot of time.
 *
 * The question is, when one types some keywords and presses "I’m feeling lucky"
 * button, which web page will appear? Google does a lot and comes up with
 * excellent approaches to deal with it. In this simplified problem, let us just
 * consider that Google assigns every web page an integer-valued relevance.
 *
 * The most related page will be chosen. If there is a tie, all the pages with
 * the highest relevance are possible to be chosen. Your task is simple, given
 * 10 web pages and their relevance. Just pick out all the possible candidates
 * which will be served to the user when "I’m feeling lucky".
 *
 * Input:
 * The input contains multiple test cases. The number of test cases T is in the
 * first line of the input file.
 * For each test case, there are 10 lines, describing the web page and the
 * relevance. Each line contains a character string without any blank characters
 * denoting the URL of this web page and an integer V_i denoting the relevance
 * of this web page. The length of the URL is between 1 and 100 inclusively.
 * (1 ≤ V_i ≤ 100)
 *
 * Output:
 * For each test case, output several lines which are the URLs of the web pages
 * which are possible to be chosen. The order of the URLs is the same as the
 * input. Please look at the sample output for further information of output
 * format.
 *
 * Solution:
 * First, scan to find the maximum relevance; second, print the URL that has the
 * maximum relevance.
 */

#include "Volume120/p12015.h"

struct P12015Tuple {
  Int8 url[128];
  Int64 relevance;
};

Void p12015_main() {
  var case_count = 0;
  scanf("%d", &case_count);

  struct P12015Tuple urls[10];

  var case_number = 1;
  for (; case_number <= case_count; case_number += 1) {
    var max_relevance = 0ll;
    var i = 0;
    for (; i < 10; i += 1) {
      scanf("%s %lld", urls[i].url, &urls[i].relevance);
      max_relevance = max(max_relevance, urls[i].relevance);
    }

    /* Output */
    printf("Case #%d:\n", case_number);
    for (i = 0; i < 10; i += 1) {
      if (urls[i].relevance == max_relevance) {
        printf("%s\n", urls[i].url);
      }
    }
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
