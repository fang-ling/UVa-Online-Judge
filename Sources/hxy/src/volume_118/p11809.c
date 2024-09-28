/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11809.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: September 28, 2024                             \ \ \_/__ \_\ \_  __  */
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
 * 11809 Floating-Point Numbers
 *
 * Floating-point numbers are represented differently in computers than
 * integers. That is why a 32-bit floating-point number can represent values in
 * the magnitude of 10**38 while a 32-bit integer can only represent values as
 * high as 2**32.
 *
 * Although there are variations in the ways floating-point numbers are stored
 * in Computers, in this problem we will assume that floating-point numbers are
 * stored in the following way:
 *
 * ┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐
 * │0│1│1│1│1│1│1│1│1│0│1│1│1│1│1│1│
 * └─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘
 *    M A N T I S S A    \EXPONENT/
 *
 * Floating-point numbers have two parts mantissa and exponent. M bits are
 * allotted for mantissa and E bits are allotted for exponent. There is also one
 * bit that denotes the sign of number (If this bit is 0 then the number is
 * positive and if it is 1 then the number is negative) and another bit that
 * denotes the sign of exponent (If this bit is 0 then exponent is positive
 * otherwise negative). The value of mantissa and exponent together make the
 * value of the floating-point number. If the value of mantissa is m then it
 * maintains the constraints 0.5 ≤ m < 1. The left most digit of mantissa must
 * always be 1 to maintain the constraint 0.5 ≤ m < 1. So this bit is not stored
 * as it is always 1. So the bits in mantissa actually denote the digits at the
 * right side of decimal point of a binary number (Excluding the digit just to
 * the right of decimal point).
 *
 * In the figure above we can see a floating-point number where M = 8 and E = 6.
 * The largest value this floating-point number can represent is (in binary)
 * 0.(111111111)_2 × 2**((111111)_2) . The decimal equivalent to this number is:
 * 0.998046875 × 2**63 = (9205357638345293824)_10. Given the maximum possible
 * value represented by a certain floating point type, you will have to find how
 * many bits are allotted for mantissa (M) and how many bits are allotted for
 * exponent (E) in that certain type.
 *
 * Input:
 * The input file contains around 300 line of input. Each line contains a
 * floating-point number F that denotes the maximum value that can be
 * represented by a certain floating-point type. The floating point number is
 * expressed in decimal exponent format. So a number AeB actually denotes the
 * value A × 10**B. A line containing '0e0' terminates input. The value of A
 * will satisfy the constraint 0 < A < 10 and will have exactly 15 digits after
 * the decimal point.
 *
 * Output:
 * For each line of input produce one line of output. This line contains the
 * value of M and E. You can assume that each of the inputs (except the last
 * one) has a possible and unique solution. You can also assume that inputs will
 * be such that the value of M and E will follow the constraints: 9 ≥ M ≥ 0 and
 * 30 ≥ E ≥ 1. Also there is no need to assume that (M + E + 2) will be a
 * multiple of 8.
 *
 * Solution:
 *
 * Logarithmic identities:
 *   ┌────────┬───────────────────────┐
 *   │Product │ln(xy) = ln(x) + ln(y) │
 *   ├────────┼───────────────────────┤
 *   │Power   │ln(x**p) = p × ln(x)   │
 *   └────────┴───────────────────────┘
 *
 *   (1 - 1/(2**(M+1))) × 2**(2**E-1) = A × 10**B        (1)
 * Check: For M = 8, E = 6.
 *        (1 - 1/(2**(M+1))) = 0.998046875
 *        2**E-1 = 63
 * Taking the natural logarithm of both sides of equation (1) (since 2**(2**E-1)
 * is too large to be stored in integers), we get:
 *   ln(2**(M+1)-1) + ((2**E-1)-(M+1)) × ln(2) = ln(A) + B × ln(10)
 *
 * At this time, we can enumerate all the possible values of M and E to check if
 * there is a match.
 */

#include "volume_118/p11809.h"

Void p11809_main() {
  /* Calculate results in log-scale */
  Double results[10][31];
  var M = 0;
  var E = 0;
  for (M = 0; M <= 9; M += 1) {
    for (E = 1; E <= 30; E += 1) {
      results[M][E] = log((1 << (M + 1)) - 1) + log(2) * ((1 << E) - 1 - M - 1);
    }
  }
  
  Int8 input_string[32];
  while (scanf("%s", input_string) == 1 && strcmp(input_string, "0e0") != 0) {
    /* Input */
    var a_i = 0;
    var a_f = 0ll;
    var e = (UInt8)0;
    var A = 0.0;
    var B = 0;
    sscanf(input_string, "%d%c%lld%c%d", &a_i, &e, &a_f, &e, &B);
    A = a_i + a_f * 1.0e-15;
    
    let result = log(A) + B * log(10);
    /* Find the result in results */
    for (M = 0; M <= 9; M += 1) {
      for (E = 1; E <= 30; E += 1) {
        if (fabs(results[M][E] - result) <= 1e-5) {
          printf("%d %d\n", M, E);
          break;
        }
      }
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
