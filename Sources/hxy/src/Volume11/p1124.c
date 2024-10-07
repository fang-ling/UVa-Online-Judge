/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p1124.c                                              /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 7, 2024                                \ \ \_/__ \_\ \_  __  */
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
 * 1124 Celebrity jeopardy
 *
 * It’s hard to construct a problem that’s so easy that everyone will get it,
 * yet still diﬃcult enough to be worthy of some respect. Usually, we err on
 * one side or the other. How simple can a problem really be?
 *
 * Here, as in Celebrity Jepoardy, questions and answers are a bit confused,
 * and, because the participants are celebrities, there’s a real need to make
 * the challenges simple. Your program needs to prepare a question to be
 * solved — an equation to be solved — given the answer. Specifically, you have
 * to write a program which finds the simplest possible equation to be solved
 * given the answer, considering all possible equations using the standard
 * mathematical symbols in the usual manner. In this context, simplest can be
 * defined unambiguously several different ways leading to the same path of
 * resolution. For now, find the equation whose transformation into the desired
 * answer requires the least effort.
 *
 * For example, given the answer X = 2, you might create the equation 9 − X = 7.
 * Alternately, you could build the system X > 0; X**2 = 4. These may not be the
 * simplest possible equations. Solving these mind-scratchers might be hard for
 * a celebrity.
 *
 * Input:
 * Each input line contains a solution in the form <symbol> = <value>
 *
 * Output:
 * For each input line, print the simplest system of equations which would to
 * lead to the provided solution, respecting the use of space exactly as in the
 * input.
 *
 * Solution:
 * The simplest system of equations will be the input itself; just echo the
 * input again.
 */
 
#include "Volume11/p1124.h"

Void p1124_main() {
  Int8* line;
  var line_capacity = 0ul;
  var line_count = 0l;
  while ((line_count = getline(&line, &line_capacity, stdin)) > 0) {
    fwrite(line, line_count, 1, stdout);
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
