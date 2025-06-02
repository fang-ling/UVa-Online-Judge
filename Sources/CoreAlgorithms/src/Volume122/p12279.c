/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p12279.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 17, 2024                               \ \ \_/__ \_\ \_  __  */
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
 * 12279 Emoogle Balance
 *
 * We have a very famous and popular fellow in our problemsetters' panel. He is
 * so famous that his name is immaterial. Some of his admirers have recently
 * given him the nickname 'Emoogle'. Let’s stick to that name in our discussion
 * for now. Being such a kind, friendly and generous person as he is, Emoogle is
 * often known to give treats to the other problemsetters. Some times, there is
 * a strange rumor in the air that his treats are mostly due to the fact that,
 * if he is not sparing enough for those treats, 'problems' are likely to be
 * created. But let’s not pay heed to such nonsense! Now, there is another word
 * in the air that this remarkable man is going to get married soon. To observe
 * this special occasion with proper respect, his fellow troublemakers have
 * decided to compile a book named '99 reasons why Emoogle should give us a
 * treat'. Every single reason mentioned in this book is denoted by a number.
 * For example, Emoogle should give us a treat because:
 *
 * 1. If he does not, problems will be created. :)
 * 2. His giveaway problem has been solved by less than 10 teams in the recent
 *    programming contest.
 * 3. He is going to join a world famous goggles manufacturing company soon.
 * 4. He has found a ticket of a soccer world cup game while digging his
 *    backyard garden in the morning.
 * 5. He has just got a new Facebook fan club.
 * 6. Having forgotten about a date with his wife-to-be which collided with a
 *    Topcoder SRM (Single Round Match), he participated in the SRM. (May God
 *    bless his soul!)
 * 7. A programming contest (may be this one?) is being arranged celebrating his
 *    marriage.
 * 8. He is getting engaged soon.
 * ...
 * 99. Solely because he is the great and kind and sweet Emoogle.
 *
 * If you have any more ideas about why he should throw a party, we would love
 * to know. Drop us a line at emoogle.party gmail.com.
 * At this point, Dear brother Emoogle might want to remind us about the number
 * of times he has already thrown a party. Hence we introduce the term Emoogle
 * Balance. This is defined as:
 *
 * Emoogle Balance = number of times Emoogle is supposed to give a treat
 * according to the book - number of times he has actually given the treat.
 *
 * In this problem, we want you to find Emoogle Balance. We also wish that
 * Emoogle Balance always keeps a healthy negative value and may dear brother
 * Emoogle have a very happy married life forever.
 *
 * Input:
 * There are around 75 test cases in the input file. Each test case describes a
 * series of events. A test case starts with an integer N (1 ≤ N ≤ 1000)
 * denoting the number of events in this test case. This integer is followed by
 * a line with N integers, each describing an event. These integers have values
 * between 0 and 99 (inclusive). A value between 1 and 99 means a reason for
 * Emoogle's giving a treat has occurred while a 0 means he has given a treat.
 * The end of input will be denoted by a case with N = 0. This case should not
 * be processed.
 *
 * Output:
 * For each test case, print a line in the format, 'Case X: Y', where X is the
 * case number and Y is the Emoogle Balance for this case.
 *
 * Solution:
 * Simple linear scan.
 */

#include "Volume122/p12279.h"

Void p12279_main() {
  var case_number = 1;
  while (true) {
    var n = 0;
    scanf("%d", &n);
    if (n == 0) {
      break;
    }
    
    var give = 0;
    var given = 0;
    var alpha = 0;
    while (n--) {
      scanf("%d", &alpha);
      if (alpha == 0) {
        given += 1;
      } else {
        give += 1;
      }
    }
    printf("Case %d: %d\n", case_number, give - given);
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
