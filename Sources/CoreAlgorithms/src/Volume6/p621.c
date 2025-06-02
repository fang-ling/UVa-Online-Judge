/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p621.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: November 27, 2024                              \ \ \_/__ \_\ \_  __  */
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
 * 621 Secret Research
 *
 * At a certain laboratory results of secret research are thoroughly encrypted.
 * A result of a single experiment is stored as an information of its
 * completion:
 *   'positive result', 'negative result', 'experiment failed' or
 *   'experiment not completed'
 * The encrypted result constitutes a string of digits S, which may take one of
 * the following forms:
 *   - positive result            S = 1 or S = 4 or S = 78
 *   - negative result            S = S35
 *   - experiment failed          S = 9S4
 *   - experiment not completed   S = 190S
 * (A sample result S35 means that if we add digits 35 from the right hand side
 * to a digit sequence then we shall get the digit sequence corresponding to a
 * failed experiment)
 * You are to write a program which decrypts given sequences of digits.
 *
 * Input:
 * A integer n stating the number of encrypted results and then consecutive n
 * lines, each containing a sequence of digits given as ASCII strings.
 *
 * Output:
 * For each analysed sequence of digits the following lines should be sent to
 * output (in separate lines):
 *   + for a positive result
 *   - for a negative result
 *   * for a failed experiment
 *   ? for a not completed experiment
 * In case the analysed string does not determine the experiment result, a first
 * match from the above list should be outputted.
 *
 * Solution:
 * Simple if-else.
 */

#include "Volume6/p621.h"

Void p621_main() {
  var S = (Int8*)malloc(sizeof(Int8) * 128);

  var case_count = 0;
  scanf("%d", &case_count);
  while (case_count--) {
    scanf("%s", S);
    var count = strlen(S);

    var result = '?';
    if (count == 1 && (S[0] == '1' || S[0] == '4')) {
      result = '+';
    } else if (count == 2 && S[0] == '7' && S[1] == '8') {
      result = '+';
    } else if (S[count - 2] == '3' && S[count - 1] == '5') {
      result = '-';
    } else if (S[0] == '9' && S[count - 1] == '4') {
      result = '*';
    } else if (S[0] == '1' && S[1] == '9' && S[2] == '0') {
      result = '?';
    }

    printf("%c\n", result);
  }

  free(S);
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
