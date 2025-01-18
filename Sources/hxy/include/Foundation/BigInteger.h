/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* BigInteger.h                                         /'___\ /\_ \          */
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

#ifndef BigInteger_h
#define BigInteger_h

#include "CFoundation.h"
#include "MutableBigInteger.h"
#include "Number.h"

enum BigIntegerSign {
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
 * operations can produce a `BigInteger` with a different sign from the
 * `BigInteger` being operated on, as they affect only a single bit, and the
 * arbitrarily large abstraction provided by this class ensures that
 * conceptually there are infinitely many "virtual sign bits" preceding each
 * `BigInteger`.
 *
 * For the sake of brevity and clarity, pseudo-code is used throughout the
 * descriptions of `BigInteger` methods.  The pseudo-code expression `(i + j)`
 * is shorthand for "a `BigInteger` whose value is that of the `BigInteger`
 * `i` plus that of the `BigInteger` `j`." The pseudo-code expression `(i == j)`
 * is shorthand for "true if and only if the `BigInteger` `i` represents the
 * same value as the `BigInteger` `j`."  Other pseudo-code expressions are
 * interpreted similarly.
 */
struct BigInteger {
  /**
   * The sign of this `BigInteger`: `minus` for negative, `none` for zero, or
   * `plus` for positive.  Note that the BigInteger zero **must** have
   * a sign of `none`.  This is necessary to ensures that there is exactly one
   * representation for each `BigInteger` value.
   */
  enum BigIntegerSign _sign;

  /**
   * The magnitude of this `BigInteger`, in *big-endian* order: the
   * zeroth element of this array is the most-significant int of the
   * magnitude.  The magnitude must be "minimal" in that the most-significant
   * word, `magnitude[0]` must be non-zero. This is necessary to ensure that
   * there is exactly one representation for each `BigInteger` value. Note that
   * this implies that the `BigInteger` zero has a zero-length magnitude array.
   */
  Int32* _magnitude;

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

/* MARK: - Creating and Destroying a BigInteger */

/**
 * Creates a new `BigInteger` value from the given string and radix.
 *
 * Translates the String representation of a `BigInteger` in the specified
 * `radix` into a `BigInteger`.  The String representation consists of an
 * optional minus or plus sign followed by a sequence of one or more digits in
 * the specified radix. The String may not contain any extraneous characters
 * (whitespace, for example).
 *
 * - Parameters:
 *   - text: The ASCII representation of a number in the radix passed as
 *   `radix`.
 *   - radix: The radix, or base, to use for converting text to an integer
 *   value. radix must be in the range 2 ... 36.
 */
struct BigInteger* big_integer_init_from_string(const Char* text, Int64 radix);

/**
 * Creates a new `BigInteger` containing the given value.
 */
struct BigInteger* big_integer_copy(struct BigInteger* value);

/**
 * Destroys a BigInteger.
 */
Void big_integer_deinit(struct BigInteger* value);

///**
// * Creates a new `BigInt` value with the specified value.
// */
//struct BigInt* big_int_init_from_int128(Int128 value);

/* MARK: - Converting Numeric Values */

/**
 * Creates a string representing the given value in base 10, or some other
 * specified base.
 *
 * If the radix is outside the range from 2 ... 36, it will default to 10.
 * A minus sign is prepended if appropriate.
 *
 * The resulting string is dynamically allocated and must be freed by the caller
 * using free().
 *
 * - Parameters:
 *   - value: The value to convert to a string.
 *   - radix: The base to use for the string representation. radix must be at
 *   least 2 and at most 36.
 *   - is_uppercase: Pass `true` to use uppercase letters to represent numerals
 *   greater than 9, or false to use lowercase letters.
 */
Char* big_integer_to_string(struct BigInteger* value,
                            Int64 radix,
                            Bool is_uppercase);

/* MARK: - Performing Calculations */

/**
 * Adds two values and produces their sum.
 *
 * - Parameters:
 *   - lhs: The first value to add.
 *   - rhs: The second value to add.
 *
 * - Returns: Returns a new BigInteger whose value is `lhs + rhs`.
 */
struct BigInteger* big_integer_add(struct BigInteger* lhs,
                                   struct BigInteger* rhs);

/**
 * Subtracts one value from another and produces their difference.
 *
 * - Parameters:
 *   - lhs: A numeric value.
 *   - rhs: The value to subtract from lhs.
 *
 * - Returns: Returns a new BigInteger whose value is `lhs - rhs`.
 */
struct BigInteger* big_integer_subtract(struct BigInteger* lhs,
                                        struct BigInteger* rhs);

/**
 * Multiplies two values and produces their product.
 *
 * - Parameters:
 *   - lhs: The first value to multiply.
 *   - rhs: The second value to multiply.
 *
 * - Returns: Returns a new BigInteger whose value is `lhs * rhs`.
 */
struct BigInteger* big_integer_multiply(struct BigInteger* lhs,
                                        struct BigInteger* rhs);

/**
 * Returns the quotient and remainder of one value divided by another value.
 *
 * - Parameters:
 *   - lhs: A numeric value.
 *   - rhs: The value to divide this value by.
 *
 * - Returns: Returns a tuple containing the quotient and remainder of `lhs`
 * divided by `rhs`.
 */
struct BigInteger** big_integer_divide_and_modulo(struct BigInteger* lhs,
                                                  struct BigInteger* rhs);

/* MARK: - Working with Binary Representation */

/**
 * Returns the number of bits in the minimal two's-complement representation of
 * this BigInt, **excluding** a sign bit.
 *
 * For positive BigIntegers, this is equivalent to the number of bits in the
 * ordinary binary representation.  For zero this method returns 0.
 *
 * (Computes: ceil(log2(this < 0 ? -this : this+1)).)
 */
Int64 big_integer_bit_count(struct BigInteger* value);

#endif /* BigInteger_h */

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
