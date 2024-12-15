/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* MutableBigInteger.h                                  /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: December 14, 2024                              \ \ \_/__ \_\ \_  __  */
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

#ifndef MutableBigInteger_h
#define MutableBigInteger_h

#include "CFoundation.h"
#include "Number.h"

/**
 * A class used to represent multiprecision integers that makes efficient use of
 * allocated space by allowing a number to occupy only part of an array so that
 * the arrays do not have to be reallocated as often.
 *
 * When performing an operation with many iterations the array used to hold a
 * number is only reallocated when necessary and does not have to be the same
 * size as the number it represents. A mutable number allows calculations to
 * occur on the same number without having to create a new number for every step
 * of the calculation as occurs with BigIntegers.
 */
struct MutableBigInteger {
  /**
   * Holds the magnitude of this MutableBigInteger in big endian order.
   * The magnitude may start at an offset into the array, and it may end before
   * the length of the value array.
   */
  UInt64* _magnitude;

  /**
   * The total number of words that the `_magnitude` can contain without
   * allocating new storage.
   */
  Int64 _magnitude_capacity;

  /**
   * The number of ints of the magnitude array that are currently used to hold
   * the magnitude of this MutableBigInteger. The magnitude starts at an offset
   * and `offset` + `_magnitude_count` may be less than `_magnitude_capacity`.
   */
  Int64 _magnitude_count;

  /**
   * The offset into the magnitude array where the magnitude of this
   * MutableBigInteger begins.
   */
  Int64 _offset;
};

/* MARK: - Creating and Destroying a MutableBigInteger */

/**
 * The default constructor. An empty MutableBigInteger is created with a one
 * word capacity.
 */
struct MutableBigInteger* mutable_big_integer_init();

/**
 * Construct a new MutableBigInteger with a magnitude specified by the int128
 * value.
 */
struct MutableBigInteger* mutable_big_integer_init_from_int128(Int128 value);

/**
 * Creates a new MutableBigInteger containing the given value.
 *
 * The `big_int_copy()` function allocates sufficient memory for a copy of the
 * given MutableBigInteger, does the copy, and returns a pointer to it. The
 * pointer may subsequently be used as an argument to the function
 * `mutable_big_integer_deinit()`.
 */
struct MutableBigInteger*
mutable_big_integer_copy(struct MutableBigInteger* value);

/* MARK: - Performing Calculations */

/**
 * Returns the quotient and remainder of `lhs` divided by the `rhs`.
 */
struct MutableBigInteger**
mutable_big_integer_divide(struct MutableBigInteger* lhs,
                           struct MutableBigInteger* rhs);

/**
 * Returns -1, 0 or 1 that indicates whether the number object's value is
 * greater than, equal to, or less than a given number.
 */
Int64 mutable_big_integer_compare(struct MutableBigInteger* lhs,
                                  struct MutableBigInteger* rhs);

#endif /* MutableBigInteger_h */

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
