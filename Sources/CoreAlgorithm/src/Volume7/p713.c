/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p713.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: January 15, 2025                               \ \ \_/__ \_\ \_  __  */
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
 * 713 Adding Reversed Numbers
 *
 * The Antique Comedians of Malidinesia prefer comedies to tragedies.
 * Unfortunately, most of the ancient plays are tragedies. Therefore the
 * dramatic advisor of ACM has decided to transfigure some tragedies into
 * comedies. Obviously, this work is very hard because the basic sense of the
 * play must be kept intact, although all the things change to their opposites.
 * For example the numbers: if any number appears in the tragedy, it must be
 * converted to its reversed form before being accepted into the comedy play.
 *
 * Reversed number is a number written in arabic numerals but the order of
 * digits is reversed. The first digit becomes last and vice versa. For example,
 * if the main hero had 1245 strawberries in the tragedy, he has 5421 of them
 * now. Note that all the leading zeros are omitted. That means if the number
 * ends with a zero, the zero is lost by reversing (e.g. 1200 gives 21). Also
 * note that the reversed number never has any trailing zeros.
 *
 * ACM needs to calculate with reversed numbers. Your task is to add two
 * reversed numbers and output their reversed sum. Of course, the result is not
 * unique because any particular number is a reversed form of several numbers
 * (e.g. 21 could be 12, 120 or 1200 before reversing). Thus we must assume that
 * no zeros were lost by reversing (e.g. assume that the original number was
 * 12).
 *
 * Input:
 * The input consists of N cases. The first line of the input contains only
 * positive integer N. Then follow the cases. Each case consists of exactly one
 * line with two positive integers separated by space. These are the reversed
 * numbers you are to add. Numbers will be at most 200 characters long.
 *
 * Output:
 * For each case, print exactly one line containing only one integer — the
 * reversed sum of two reversed numbers. Omit any leading zeros in the output.
 *
 * Solution:
 * Print rev(rev(a) + rev(b)).
 */

#include "Volume7/p713.h"

Void p713_main() {
  Char bufffer1[256];
  Char bufffer2[256];

  var case_count = 0;
  scanf("%d", &case_count);

  while (case_count--) {
    scanf("%s %s", bufffer1, bufffer2);
    ansi_strrev(bufffer1);
    ansi_strrev(bufffer2);

    var a = big_integer_init_from_string(bufffer1, 10);
    var b = big_integer_init_from_string(bufffer2, 10);
    var sum = big_integer_add(a, b);

    var result = big_integer_to_string(sum, 10, false);
    ansi_strrev(result);
    var reversed = big_integer_init_from_string(result, 10);
    free(result);
    result = big_integer_to_string(reversed, 10, false);

    printf("%s\n", result);

    big_integer_deinit(a);
    big_integer_deinit(b);
    big_integer_deinit(sum);
    big_integer_deinit(reversed);
    free(result);
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
