/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* BigInt.h                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: November 30, 2024                              \ \ \_/__ \_\ \_  __  */
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

#ifndef BigInt_h
#define BigInt_h

#include "CFoundation.h"
#include "Number.h"

enum BigIntSign {
  plus,
  minus,
  none
};

/**
 * An arbitary precision signed integer type, also known as a "big integer".
 *
 * Operations on big integers never overflow, but they might take a long time to
 * execute. The amount of memory (and address space) available is the only
 * constraint to the magnitude of these numbers.
 *
 * Semantics of arithmetic operations exactly mimic those of C's integer
 * arithmetic operators. For example, division of a negative by a positive
 * yields a negative (or zero) remainder.
 *
 * Semantics of shift operations extend those of C's shift operators
 * to allow for negative shift distances. A right-shift with a negative
 * shift distance results in a left shift, and vice-versa.
 *
 * Semantics of bitwise logical operations exactly mimic those of C's
 * bitwise integer operators.  The binary operators `and`,
 * `or`, `xor` implicitly perform sign extension on the shorter
 * of the two operands prior to performing the operation.
 *
 * Comparison operations perform signed integer comparisons, analogous to
 * those performed by C's relational and equality operators.
 *
 * Modular arithmetic operations are provided to compute residues, perform
 * exponentiation, and compute multiplicative inverses.  These methods always
 * return a non-negative result, between `0` and `(modulus - 1), inclusive.
 *
 * Bit operations operate on a single bit of the two's-complement
 * representation of their operand.  If necessary, the operand is sign-extended
 * so that it contains the designated bit.  None of the single-bit
 * operations can produce a `BigInt` with a different sign from the
 * `BigInt` being operated on, as they affect only a single bit, and the
 * arbitrarily large abstraction provided by this class ensures that
 * conceptually there are infinitely many "virtual sign bits" preceding each
 * `BigInt`.
 *
 * For the sake of brevity and clarity, pseudo-code is used throughout the
 * descriptions of `BigInt` methods.  The pseudo-code expression
 * `(i + j)` is shorthand for "a `BigInt` whose value is that of the `BigInt`
 * `i` plus that of the `BigInt` `j`." The pseudo-code expression `(i == j)` is
 * shorthand for "true if and only if the `BigInt` `i` represents the same
 * value as the `BigInt` `j`."  Other pseudo-code expressions are interpreted
 * similarly.
 */
struct BigInt {
  /**
   * The sign of this `BigInt`: `minus` for negative, `none` for zero, or
   * `plus` for positive.  Note that the BigInteger zero **must** have
   * a sign of `none`.  This is necessary to ensures that there is exactly one
   * representation for each `BigInt` value.
   */
  enum BigIntSign _sign;

  /**
   * The magnitude of this `BigInt`, in *big-endian* order: the
   * zeroth element of this array is the most-significant int of the
   * magnitude.  The magnitude must be "minimal" in that the most-significant
   * word, `magnitude[0]` must be non-zero. This is necessary to ensure that
   * there is exactly one representation for each `BigInt` value.  Note that
   * this implies that the `BigInt` zero has a zero-length magnitude array.
   */
  UInt64* _magnitude;

  /**
   * The number of words in the `magnitude`.
   */
  Int64 _magnitude_count;

  /**
   * The total number of words that the `magnitude` can contain without
   * allocating new storage.
   */
  Int64 _magnitude_capacity;
};

/* MARK: - Converting Strings */

/**
 * Creates a new `BigInt` value from the given string and radix.
 *
 * Translates the String representation of a `BigInt` in the specified `radix`
 * into a `BigInt`.  The String representation consists of an optional minus or
 * plus sign followed by a sequence of one or more digits in the specified
 * radix. The String may not contain any extraneous characters (whitespace, for
 * example).
 *
 * - Parameters:
 *   - text: The ASCII representation of a number in the radix passed as
 *   `radix`.
 *   - radix: The radix, or base, to use for converting text to an integer
 *   value. radix must be in the range 2 ... 36.
 */
struct BigInt* big_int_init(Char* text, Int64 radix);

#endif /* BigInt_h */

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
