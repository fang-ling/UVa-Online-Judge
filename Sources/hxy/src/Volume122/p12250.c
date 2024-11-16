/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p12250.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 11, 2024                               \ \ \_/__ \_\ \_  __  */
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
 * 12250 Language Detection
 *
 * English, Spanish, German, French, Italian and Russian are the 6 most
 * prominent languages in the countries of European Union. Figure on the left
 * shows intensity of English speaking people in different European countries.
 * All of these languages have different words to represent the English word
 * "HELLO". For example in Spanish the word equivalent to "HELLO" is "HOLA".
 * In German, French, Italian and Russian language the word that means
 * (or similar to) "HELLO" is "HALLO", "BONJOUR", "CIAO" and "ZDRAVSTVUJTE"
 * respectively. In this problem your task is pretty simple. You will be given
 * one of the six words mentioned above or any other word and you will have to
 * try and detect the language it is from.
 *
 * Input:
 * Input file contains around 2000 lines of inputs. Each line contains a string
 * S. You can assume that all the letters of the string are uppercase English
 * letters and the maximum length of the string is 14. Input is terminated by a
 * line containing a single '#' character (without the quote). This line should
 * not be processed.
 *
 * Output:
 * For each line of input except the last one produce one line of output. This
 * line contains the serial of output followed by a language name. If the input
 * string is 'HELLO' or 'HOLA' or 'HALLO' or 'BONJOUR' or 'CIAO' or
 * 'ZDRAVSTVUJTE' then you should report the language it belongs to. If the
 * input string is something other than these 6 strings print the string
 * 'UNKNOWN' (without the quotes) instead. All characters in the output strings
 * are uppercase as well. Look at the output for sample input for formatting
 * details.
 *
 * Solution:
 * Use a structure similar to multiple if-else statements.
 */

#include "Volume122/p12250.h"

Void p12250_main() {
  var case_count = 0;
  Char word[16];
  while (scanf("%s", word) == 1 && word[0] != '#') {
    case_count += 1;
    if (strcmp(word, "HELLO") == 0) {
      printf("Case %d: ENGLISH\n", case_count);
    } else if (strcmp(word, "HOLA") == 0) {
      printf("Case %d: SPANISH\n", case_count);
    } else if (strcmp(word, "HALLO") == 0) {
      printf("Case %d: GERMAN\n", case_count);
    } else if (strcmp(word, "BONJOUR") == 0) {
      printf("Case %d: FRENCH\n", case_count);
    } else if (strcmp(word, "CIAO") == 0) {
      printf("Case %d: ITALIAN\n", case_count);
    } else if (strcmp(word, "ZDRAVSTVUJTE") == 0) {
      printf("Case %d: RUSSIAN\n", case_count);
    } else {
      printf("Case %d: UNKNOWN\n", case_count);
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
