/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p465.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 2, 2024                                \ \ \_/__ \_\ \_  __  */
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
 * 465 Overflow
 *
 * Write a program that reads an expression consisting of two non-negative
 * integer and an operator. Determine if either integer or the result of the
 * expression is too large to be represented as a "normal" signed integer (type
 * integer if you are working Pascal, type int if you are working in C).
 *
 * Input:
 * An unspecified number of lines. Each line will contain an integer, one of the
 * two operators '+' or '*', and another integer.
 *
 * Output:
 * For each line of input, print the input followed by 0-3 lines containing as
 * many of these three messages as are appropriate: 'first number too big',
 * 'second number too big', 'result too big'.
 *
 * Solution:
 * We first determine if the integer is convertible to Int64 (by a simple
 * strlen() check with removal of leading zeros), then check if it is
 * convertible to Int32 (by comparing it with Int32.max), and finally verify
 * that the result is convertible to Int32 without overflow.
 */

#include "Volume4/p465.h"

Bool p465_is_int64_convertible(Int8* number) {
  /*
   * Remove leading zeros
   * For all zero number, this function still returns true, so it's OK.
   */
  while (*number == '0' && *number != '\0') {
    number += 1;
  }
  return strlen(number) <= 17;
}

Bool p465_is_int32_convertible(Int64 number) {
  return number <= INT32_MAX;
}

Void p465_main() {
  Int8 lhs_string[256];
  Int8 operator[2];
  Int8 rhs_string[256];
  while (scanf("%s %s %s", lhs_string, operator, rhs_string) == 3) {
    printf("%s %s %s\n", lhs_string, operator, rhs_string);
    
    var is_result_overflow = false;
    
    /* Is lhs Int64 convertible? */
    var lhs = -1ll;
    if (p465_is_int64_convertible(lhs_string)) {
      sscanf(lhs_string, "%lld", &lhs);
    } else {
      printf("first number too big\n");
      is_result_overflow = true;
    }
    /* Is lhs Int32 convertible? */
    if (!p465_is_int32_convertible(lhs)) {
      printf("first number too big\n");
      is_result_overflow = true;
    }
    
    /* Is rhs Int64 convertible? */
    var rhs = -1ll;
    if (p465_is_int64_convertible(rhs_string)) {
      sscanf(rhs_string, "%lld", &rhs);
    } else {
      printf("second number too big\n");
      is_result_overflow = true;
    }
    /* Is rhs Int32 convertible? */
    if (!p465_is_int32_convertible(rhs)) {
      printf("second number too big\n");
      is_result_overflow = true;
    }
    
    if (lhs == 0 || rhs == 0) { /* Special case */
      is_result_overflow = false;
    }
    
    /* Is result Int32 convertible? */
    if (!is_result_overflow) {
      is_result_overflow = !p465_is_int32_convertible(
        operator[0] == '+' ? lhs + rhs : lhs * rhs
      );
    }
    if (is_result_overflow) {
      printf("result too big\n");
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
