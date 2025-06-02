/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10082.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: January 28, 2025                               \ \ \_/__ \_\ \_  __  */
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
 * 10082 WERTYU
 *
 * A common typing error is to place the hands on the keyboard one row to the
 * right of the correct position. So 'Q' is typed as 'W' and 'J' is typed
 * as 'K' and so on. You are to decode a message typed in this manner.
 *
 * Input:
 * Input consists of several lines of text. Each line may contain digits,
 * spaces, upper case letters (except Q, A, Z), or punctuation shown above
 * [except back-quote (`)]. Keys labelled with words [Tab, BackSp, Control,
 * etc.] are not represented in the input.
 *
 * Output:
 * You are to replace each letter or punction symbol by the one immediately to
 * its left on the 'QWERTY' keyboard shown above. Spaces in the input should be
 * echoed in the output.
 *
 * Solution:
 * Very easy.
 */

#include "Volume100/p10082.h"

Void p10082_main() {
  Int8 table[128];

  table['Q'] = 'Q';
  table['W'] = 'Q';
  table['E'] = 'W';
  table['R'] = 'E';
  table['T'] = 'R';
  table['Y'] = 'T';
  table['U'] = 'Y';
  table['I'] = 'U';
  table['O'] = 'I';
  table['P'] = 'O';
  table['['] = 'P';
  table[']'] = '[';
  table['A'] = 'A';
  table['S'] = 'A';
  table['D'] = 'S';
  table['F'] = 'D';
  table['G'] = 'F';
  table['H'] = 'G';
  table['J'] = 'H';
  table['K'] = 'J';
  table['L'] = 'K';
  table[';'] = 'L';
  table['\''] = ';';
  table['Z'] = 'Z';
  table['X'] = 'Z';
  table['C'] = 'X';
  table['V'] = 'C';
  table['B'] = 'V';
  table['N'] = 'B';
  table['M'] = 'N';
  table[','] = 'M';
  table['.'] = ',';
  table['/'] = '.';
  table['\\']=']';
  table['`'] = '`';
  table['1'] = '`';
  table['2'] = '1';
  table['3'] = '2';
  table['4'] = '3';
  table['5'] = '4';
  table['6'] = '5';
  table['7'] = '6';
  table['8'] = '7';
  table['9'] = '8';
  table['0'] = '9';
  table['-'] = '0';
  table['='] = '-';
  table[' '] = ' ';
  table['\n'] = '\n';

  var c = (Int8)0;
  while (scanf("%c", &c) == 1) {
    printf("%c", table[c]);
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
