/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* String.h                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: March 13, 2025                                 \ \ \_/__ \_\ \_  __  */
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

#ifndef String_h
#define String_h

#include "_Foundation.h"

/**
 * A Unicode string value that is a collection of characters.
 *
 * A string is a series of characters, such as "`CoreAlgorithm`", that forms a
 * collection. Strings are Unicode correct and locale insensitive, and are
 * designed to be efficient.
 *
 * You can create new strings using ``string_init``, which accepts C string
 * literals as its parameter. A C _string literal_ is a series of characters
 * enclosed in quotes.
 *
 * ```objectivec
 * var greeting = string_init("Welcome!")
 *
 * // ...
 *
 * string_deinit(greeting) // Deallocates the object when it is no longer needed
 * ```
 *
 * Modifying and Comparing Strings
 * ===============================
 *
 * Strings always have reference semantics because they are implemented using
 * pointers.
 *
 * Comparing strings for equality using ``string_compare`` is always performed
 * using the UTF-32 representation of the strings. As a result, different
 * representations of a string are considered not equal. It is the caller's
 * responsibility to normalize the given C string.
 *
 * Accessing String Elements
 * =========================
 *
 * A string is a collection of _extended grapheme clusters_, which approximate
 * human-readable characters. Many individual characters, such as "é", "김", and
 * "🇯🇵", can be made up of multiple Unicode scalar values. These scalar values
 * are combined by Unicode's boundary algorithms into extended grapheme
 * clusters, represented by the `UInt32` type. Each element of a string is
 * represented by a `UInt32` value.
 *
 * ```objectivec
 * var cafe = string_init("Cafe 🌍")
 *
 * printf("%u\n", string_get(cafe, 5))
 * // Prints 127757
 * ```
 */
struct String {
  /**
   * The string's value represented as a collection of UTF-32 code units.
   */
  UInt32* _utf32;

  /**
   * The total number of UTF-32 code units that the array can contain without
   * allocating new storage.
   */
  Int64 _capacity;

  /**
   * The number of characters in a string.
   */
  Int64 count;
};

/* MARK: - Creating and Destroying a String */

/**
 * Creates a new string by copying the null-terminated UTF-8 data referenced by
 * the given pointer.
 *
 * - Parameter c_string: A pointer to a null-terminated sequence of UTF-8 code
 *                       units.
 *
 * - Returns: The newly created string object.
 */
struct String* string_init(Int8* c_string);

/**
 * Destroys a string.
 *
 * - Parameter string: The string object to be deinitialized.
 */
Void string_deinit(struct String* string);

/* MARK: - Accessing Characters */



#endif /* String_h */

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
