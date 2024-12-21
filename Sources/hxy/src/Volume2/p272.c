/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p272.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: December 17, 2024                              \ \ \_/__ \_\ \_  __  */
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
 * 272 TEX Quotes
 *
 * TEX is a typesetting language developed by Donald Knuth. It takes source text
 * together with a few typesetting instructions and produces, one hopes, a
 * beautiful document. Beautiful documents use “ and ” to delimit quotations,
 * rather than the mundane " which is what is provided by most keyboards.
 * Keyboards typically do not have an oriented double-quote, but they do have a
 * left-single-quote ` and a right-single-quote '. Check your keyboard now to
 * locate the left-single-quote key ` (sometimes called the "backquote key") and
 * the right-single-quote key ' (sometimes called the "apostrophe" or just
 * "quote"). Be careful not to confuse the left-single-quote ` with the
 * "backslash" key \. TEX lets the user type two left-single-quotes `` to create
 * a left-double-quote “ and two right-single-quotes '' to create a
 * right-double-quote ”. Most typists, however, are accustomed to delimiting
 * their quotations with the un-oriented double-quote ".
 *
 * If the source contained
 * "To be or not to be," quoth the bard, "that is the question."
 * then the typeset document produced by TEX would not contain the desired form:
 * “To be or not to be,” quoth the bard, “that is the question.”
 * In order to produce the desired form, the source file must contain the
 * sequence:
 * ``To be or not to be,'' quoth the bard, ``that is the question.''
 *
 * You are to write a program which converts text containing double-quote (")
 * characters into text that is identical except that double-quotes have been
 * replaced by the two-character sequences required by TEX for delimiting
 * quotations with oriented double-quotes. The double-quote (") characters
 * should be replaced appropriately by either`` if the " opens a quotation and
 * by '' if the " closes a quotation.
 * Notice that the question of nested quotations does not arise: The first "
 * must be replaced by ``, the next by '', the next by ``, the next by '', the
 * next by ``, the next by '', and so on.
 *
 * Input:
 * Input will consist of several lines of text containing an even number of
 * double-quote (") characters.
 * Input is ended with an end-of-file character.
 *
 * Output:
 * The text must be output exactly as it was input except that:
 *   - the first " in each pair is replaced by two ` characters: `` and
 *   - the second " in each pair is replaced by two ' characters: ''.
 *
 * Solution:
 * Use a boolean variable to indicate whether we are on the left or not.
 */

#include "Volume2/p272.h"

Void p272_main() {
  var is_left = true;
  var c = (Char)0;
  while ((c = getchar()) != EOF) {
    if (c == '"') {
      printf("%s", is_left ? "``" : "''");
      is_left = !is_left;
    } else {
      printf("%c", c);
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
