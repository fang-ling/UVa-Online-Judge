/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Int64.hpp                                            /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: July 19, 2025                                  \ \ \_/__ \_\ \_  __  */
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

#ifndef Int64_hpp
#define Int64_hpp

#include "Bool.hpp"
#include "../Internal/_CoreAlgorithms.hpp"

/**
 * A 64-bit signed integer value type.
 */
class Int64 {
  private: long long _value;

  /**
   * Adds two values and stores the result in the left-hand-side variable.
   *
   * - Parameters:
   *   - lhs: The first value to add.
   *   - rhs: The second value to add.
   */
  friend func operator += (Int64& lhs, const Int64& rhs) -> Void;

  /**
   * Creates a new instance from the given integer.
   *
   * - Parameter source: A value to convert to this type of integer.
   */
  public: Int64(long long source);

  /**
   * Returns a Boolean value indicating whether the value of the first argument
   * is greater than that of the second argument.
   *
   * - Parameters:
   *   - lhs: An integer to compare.
   *   - rhs: Another integer to compare.
   */
  friend func operator > (const Int64& lhs, const Int64& rhs) -> Bool;

  /**
   * Returns a Boolean value indicating whether the value of the first argument
   * is less than or equal to that of the second argument.
   *
   * - Parameters:
   *   - lhs: An integer to compare.
   *   - rhs: Another integer to compare.
   */
  friend func operator <= (const Int64& lhs, const Int64& rhs) -> Bool;

  /**
   * Returns the remainder of dividing the first value by the second.
   *
   * The result of the remainder operator (`%`) has the same sign as `lhs` and
   * has a magnitude less than `rhs`'s magnitude.
   *
   *     let x = Int64(22) % Int64(5)
   *     // x == 2
   *     let y = Int64(22) % Int64(-5)
   *     // y == 2
   *     let z = Int64(-22) % Int64(-5)
   *     // z == -2
   *
   * For any two integers `a` and `b`, their quotient `q`, and their remainder
   * `r`, `a == b * q + r`.
   *
   * - Parameters:
   *   - lhs: The value to divide.
   *   - rhs: The value to divide `lhs` by. `rhs` must not be zero.
   */
  friend func operator % (const Int64& lhs, const Int64& rhs) -> Int64;

  /**
   * Divides the first value by the second and stores the quotient in the
   * left-hand-side variable.
   *
   *     var x = Int64(21)
   *     x /= Int64(5)
   *     // x == 4
   *
   * - Parameters:
   *   - lhs: The value to divide.
   *   - rhs: The value to divide `lhs` by. `rhs` must not be zero.
   */
  friend func operator /= (Int64& lhs, const Int64& rhs) -> Void;

  /**
   * Multiplies two values and produces their product.
   *
   * - Parameters:
   *   - lhs: The first value to multiply.
   *   - rhs: The second value to multiply.
   */
  friend func operator * (const Int64& lhs, const Int64& rhs) -> Int64;

  /**
   * Adds two values and produces their sum.
   *
   * - Parameters:
   *   - lhs: The first value to add.
   *   - rhs: The second value to add.
   */
  friend func operator + (const Int64& lhs, const Int64& rhs) -> Int64;

  /**
   * Returns a Boolean value indicating whether two values are not equal.
   *
   * Inequality is the inverse of equality. For any values `a` and `b`, `a != b`
   * implies that `a == b` is `false`.
   *
   * - Parameters:
   *   - lhs: A value to compare.
   *   - rhs: Another value to compare.
   */
  friend func operator != (const Int64& lhs, const Int64& rhs) -> Bool;

  /**
   * Returns a Boolean value indicating whether the two given values are equal.
   *
   * - Parameters:
   *   - lhs: An integer to compare.
   *   - rhs: Another integer to compare.
   */
  friend func operator == (const Int64& lhs, const Int64& rhs) -> Bool;

  friend func operator >> (std::istream& stream, Int64& value) -> std::istream&;
  friend func operator << (std::ostream& stream,
                           const Int64& value) -> std::ostream&;
};

#endif /* Int64_hpp */

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
