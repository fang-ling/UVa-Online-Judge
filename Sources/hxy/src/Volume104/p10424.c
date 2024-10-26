/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10424.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 21, 2024                               \ \ \_/__ \_\ \_  __  */
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
 * 10424 Love Calculator
 * One day I asked Saima that how much she loves me. Her answer was "71.43%". I
 * was surprised as well as shocked by her answer. I could not understand why
 * she didn't tell 100% and why she told a particular and peculiar fraction like
 * 71.43. Looking at my surprised, shocked and nervous face she burst out
 * laughing and told that she loves me more than any thing in this universe and
 * it was nothing but a silly and funny love calculation. Then she described me
 * the calculation. In this problem you will have to write a program so that any
 * one can calculate love between any two persons very quickly (of course a very
 * silly game).
 *
 * Rules: You will be given two names. These two names can have white space or
 * some other non-alphabetical characters like $ & % etc. But only the alphabets
 * from a to z or A to Z will participate in love calculation. Each alphabet has
 * a particular value. The values are from 1 to 26 in ascending order of the
 * alphabets. It’s like this, a = 1, b = 2, c = 3, ..., z = 26. Both upper case
 * and lower case holds the same values. Then make the sum of these numbers
 * until it comes in one digit. [For example, consider a name ‘bcz’. Here,
 * b = 2, c = 3 and z = 26. So, the sum is (2+3+26) = 31 = (3+1) = 4.] Then the
 * ratio of these two numbers in percentage will be the result.
 *
 * Remember: Result can not be more than 100% . Take the ratio carefully to
 * avoid this problem.
 *
 * Input:
 * Your input will be two names. Each name holds not more than 25 characters.
 * End of file will indicate the end of input.
 *
 * Output:
 * For each pair of names your program will have to calculate the love between
 * those two persons and give the result as output. In result two digits to be
 * displayed after the decimal point. All the results must be in new lines.
 *
 * Solution:
 * Use two functions.
 */

#include "Volume104/p10424.h"

static Int p10424_sum(Int8* name) {
  var sum = 0ll;
  var s = name;
  while (*s != '\0') {
    if (*s >= 'a' && *s <= 'z') {
      sum += *s - 'a' + 1;
    } else if (*s >= 'A' && *s <= 'Z') {
      sum += *s - 'A' + 1;
    }
    s += 1;
  }
  return sum;
}

static Int p10424_sum_digits(Int sum) {
  if (sum < 10) {
    return sum;
  }
  var result = 0ll;
  while (sum > 0) {
    result += sum % 10;
    sum /= 10;
  }
  return p10424_sum_digits(result);
}

Void p10424_main() {
  Int8* name1 = NULL;
  Int8* name2 = NULL;
  var line_capacity1 = 0ul;
  var line_capacity2 = 0ul;
  var line_count1 = 0l;
  var line_count2 = 0l;
  while (
    (line_count1 = getline(&name1, &line_capacity1, stdin)) > 0 &&
    (line_count2 = getline(&name2, &line_capacity2, stdin)) > 0
  ) {
    var sum1 = (Double)p10424_sum_digits(p10424_sum(name1));
    var sum2 = (Double)p10424_sum_digits(p10424_sum(name2));
    
    printf("%.2lf %%\n", (sum1 > sum2 ? sum2 / sum1 : sum1 / sum2) * 100.0);
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
