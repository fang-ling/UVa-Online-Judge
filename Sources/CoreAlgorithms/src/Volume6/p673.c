/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p673.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: April 27, 2025                                 \ \ \_/__ \_\ \_  __  */
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
 * 673 Parentheses Balance
 *
 * You are given a string consisting of parentheses () and []. A string of this
 * type is said to be correct:
 *
 *   (a) if it is the empty string
 *   (b) if A and B are correct, AB is correct,
 *   (c) if A is correct, (A) and [A] is correct.
 *
 * Write a program that takes a sequence of strings of this type and check their
 * correctness. Your program can assume that the maximum string length is 128.
 *
 * Input:
 * The file contains a positive integer n and a sequence of n strings of
 * parentheses '()' and '[]', one string a line.
 *
 * Output:
 * A sequence of 'Yes' or 'No' on the output file.
 */

#include "Volume6/p673.h"

Void p673_main() {
  var n = 0;
  scanf("%d", &n);
  /* Read the extra \n! */
  getchar();

  var buffer = (Int8*)malloc(sizeof(Int8) * 256);
  var stack = array_init(sizeof(Int8));

  var parenthesis = ')';
  var bracket = ']';

  while (n--) {
    array_remove_all(stack, true);

    var line_capacity = 0ul;
    getline(&buffer, &line_capacity, stdin);
    var s = buffer;

    var is_matched = true;

    while (*s != '\0' && is_matched) {
      if (*s == '(') {
        array_append(stack, &parenthesis);
      } else if (*s == '[') {
        array_append(stack, &bracket);
      } else if (*s == ')' || *s == ']') {
        if (stack->count <= 0) {
          is_matched = false;
        } else {
          var top = (Int8)0;
          array_remove_last(stack, &top);
          is_matched = (top == *s);
        }
      }

      s += 1;
    }

    if (stack->count > 0) {
      is_matched = false;
    }

    printf("%s\n", is_matched ? "Yes" : "No");
  }

  free(buffer);
  array_deinit(stack);
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
