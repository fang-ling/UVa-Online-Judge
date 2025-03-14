/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p12289.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: December 4, 2024                               \ \ \_/__ \_\ \_  __  */
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
 * 12289 One-Two-Three
 *
 * Your little brother has just learnt to write one, two and three, in English.
 * He has written a lot of those words in a paper, your task is to recognize
 * them. Note that your little brother is only a child, so he may make small
 * mistakes: for each word, there might be at most one wrong letter. The word
 * length is always correct. It is guaranteed that each letter he wrote is in
 * lower-case, and each word he wrote has a unique interpretation.
 *
 * Input:
 * The first line contains the number of words that your little brother has
 * written. Each of the following lines contains a single word with all letters
 * in lower-case. The words satisfy the constraints above: at most one letter
 * might be wrong, but the word length is always correct. There will be at most
 * 10 words in the input.
 *
 * Output:
 * For each test case, print the numerical value of the word.
 *
 * Solution:
 * If-else + simple string compare.
 */

#include "Volume122/p12289.h"

Void p12289_main() {
  Int8 number[8];
  
  var case_count = 0;
  scanf("%d", &case_count);
  while (case_count--) {
    scanf("%s", number);

    var result = 0;
    var count = strlen(number);
    if (count == 5) {
      result = 3;
    } else if ((number[0] == 'o' && number[1] == 'n') ||
               (number[1] == 'n' && number[2] == 'e') ||
               (number[0] == 'o' && number[2] == 'e')) {
      result = 1;
    } else {
      result = 2;
    }

    printf("%d\n", result);
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
