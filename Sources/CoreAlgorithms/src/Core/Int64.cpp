/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Int64.cpp                                            /'___\ /\_ \          */
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

#include "Int64.hpp"

/* MARK: - AdditiveArithmetic Implementations */
func operator += (Int64& lhs, const Int64& rhs) -> Void {
  lhs._value += rhs._value;
}

/* MARK: - BinaryInteger Implementations */
Int64::Int64(long long source) {
  this->_value = source;
}

func operator > (const Int64& lhs, const Int64& rhs) -> Bool {
  return Bool(lhs._value > rhs._value);
}

func operator <= (const Int64& lhs, const Int64& rhs) -> Bool {
  return Bool(lhs._value <= rhs._value);
}

func operator % (const Int64& lhs, const Int64& rhs) -> Int64 {
  return Int64(lhs._value % rhs._value);
}

func operator /= (Int64& lhs, const Int64& rhs) -> Void {
  lhs._value /= rhs._value;
}

func operator * (const Int64& lhs, const Int64& rhs) -> Int64 {
  return Int64(lhs._value * rhs._value);
}

func operator + (const Int64& lhs, const Int64& rhs) -> Int64 {
  return Int64(lhs._value + rhs._value);
}

/* MARK: - Equatable Implementations */
func operator != (const Int64& lhs, const Int64& rhs) -> Bool {
  return Bool(lhs._value != rhs._value);
}

func operator == (const Int64& lhs, const Int64& rhs) -> Bool {
  return Bool(lhs._value == rhs._value);
}

/* MARK: - IO */
func operator >> (std::istream& stream, Int64& value) -> std::istream& {
  stream >> value._value;
  return stream;
}

func operator << (std::ostream& stream, const Int64& value) -> std::ostream& {
  stream << value._value;
  return stream;
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
