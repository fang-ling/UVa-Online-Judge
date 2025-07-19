/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Algorithm.hpp                                        /'___\ /\_ \          */
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

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include "../Internal/_CoreAlgorithms.hpp"

/**
 * Returns the greater of two comparable values.
 *
 * - Parameters:
 *   - x: A value to compare.
 *   - y: Another value to compare.
 *
 * - Returns: The greater of `x` and `y`. If `x` is equal to `y`, returns `y`.
 */
template <class T>
func max(const T& x, const T& y) -> const T& {
  return x > y ? x : y;
}

/**
 * Returns the lesser of two comparable values.
 *
 * - Parameters:
 *   - x: A value to compare.
 *   - y: Another value to compare.
 *
 * - Returns: The lesser of `x` and `y`. If `x` is equal to `y`, returns `x`.
 */
template <class T>
func min(const T& x, const T& y) -> const T& {
  return y > x ? x : y;
}

#endif /* Algorithm_hpp */

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
