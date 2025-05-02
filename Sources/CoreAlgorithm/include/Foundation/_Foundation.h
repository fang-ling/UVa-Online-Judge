/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* _Foundation.h                                        /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: November 14, 2024                              \ \ \_/__ \_\ \_  __  */
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

#ifndef _Foundation_h
#define _Foundation_h

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define var __auto_type
#define let const __auto_type

/* MARK: - Type Aliases */

/**
 * The return type of functions that don't explicitly specify a return type.
 */
typedef void Void;

/**
 * A generic object type.
 */
typedef Void* AnyObject;

/**
 * A generic constant object type.
 */
typedef const void* AnyConstantObject;

/**
 * An 8-bit unsigned integer value type.
 */
typedef uint8_t UInt8;

/**
 * A 16-bit unsigned integer value type.
 */
typedef uint16_t UInt16;

/**
 * A 32-bit unsigned integer value type.
 */
typedef uint32_t UInt32;

/**
 * A 64-bit unsigned integer value type.
 */
typedef uint64_t UInt64;

/**
 * A 128-bit unsigned integer type.
 */
typedef unsigned __int128 UInt128;

/**
 * An 8-bit signed integer value type.
 */
typedef char Int8;

/**
 * A 16-bit signed integer value type.
 */
typedef int16_t Int16;

/**
 * A 32-bit signed integer value type.
 */
typedef int32_t Int32;

/**
 * A 64-bit signed integer value type.
 */
typedef int64_t Int64;

/**
 * A 128-bit signed integer type.
 */
typedef __int128 Int128;

/**
 * A single-precision, floating-point value type.
 */
typedef float Float;

/**
 * A double-precision, floating-point value type.
 */
typedef double Double;

/**
 * A value type whose instances are either `true` or `false`.
 */
typedef bool Bool;

/* MARK: - Protocols */

/**
 * A predicate type that returns an integer less than, equal to, or greater than
 * zero if the first argument is considered to be respectively less than, equal
 * to, or greater than the second.
 */
typedef Int32 (*Comparable)(AnyConstantObject, AnyConstantObject);

/* MARK: - Numeric Constants */

/* The maximum representable integer in Int32. */
#define _INT32_MAX 0x7FFFFFFF

/* The maximum representable integer in UInt32. */
#define _UINT32_MAX 0xFFFFFFFFu

/* MARK: - Global Function-like Macros */

/**
 * Checks a necessary condition for making forward progress.
 *
 * Use this function to detect conditions that must prevent the program from
 * proceeding, even in shipping code.
 *
 * * In `-O0` builds (the default for Xcode's Debug configuration) and
 *   `ONLINE_JUDGE` symbol is not defined: If `condition` evaluates to `false`,
 *   stop program execution in a debuggable state after printing `message`.
 *
 * * In `-O2` builds (the default for Xcode's Release configuration) and
 *   `ONLINE_JUDGE` symbol is not defined: `condition` is not evaluated. Failure
 *   to satisfy that assumption is a serious programming error.
 *
 * * In any builds with `ONLINE_JUDGE` symbol defined, `condition` is not
 *   evaluated. Failure to satisfy that assumption is a serious programming
 *   error.
 *
 * - Parameters:
 *   - condition: The condition to test. `condition` is not evaluated with
 *     `ONLINE_JUDGE` symbol defined.
 *   - message: A string to print if `condition` is evaluated to `false`.
 */
#if defined(ONLINE_JUDGE) || !defined(DEBUG)
#define _precondition(condition, message) ((void)0)
#else
#define _precondition(condition, message) \
  do {                                    \
    if (!(condition)) {                   \
      fprintf(stderr,                     \
              "%s:%d: Fatal error: %s\n", \
              __FILE__,                   \
              __LINE__,                   \
              (message));                 \
      abort();                            \
    }                                     \
  } while (0)
#endif

/**
 * Returns the greater of two comparable values.
 *
 * - Parameters:
 *   - x: A value to compare.
 *   - y: Another value to compare.
 *
 * - Returns: The greater of `x` and `y`. If `x` is equal to `y`, returns `y`.
 */
#define _max(x, y) ({ \
  var _x = (x);       \
  var _y = (y);       \
  _x > _y ? _x : _y;  \
})

/**
 * Returns the lesser of two comparable values.
 *
 * - Parameters:
 *   - x: A value to compare.
 *   - y: Another value to compare.
 *
 * - Returns: The lesser of `x` and `y`. If `x` is equal to `y`, returns `y`.
 */
#define _min(x, y) ({ \
  var _x = (x);       \
  var _y = (y);       \
  _x < _y ? _x : _y;  \
})

/**
 * Returns the absolute value of the given number.
 *
 * - Parameter x: A signed number.
 *
 * - Returns: The absolute value of `x`.
 */
#define _abs(x) ({   \
  var _x = (x);      \
  _x > 0 ? _x : -_x; \
})

/**
 * Returns a pointer to a null-terminated byte string, which is a duplicate of
 * the given string.
 *
 * This function allocates sufficient memory for a copy of the given string,
 * does the copy, and returns a pointer to it. The pointer may subsequently be
 * used as an argument to the function `free`.
 *
 * - Parameter string: A pointer to the null-terminated string to be duplicated.
 *
 * - Returns: A pointer to the duplicated string. If insufficient memory is
 *            available, `NULL` is returned.
 */
#define _strdup(string) ({                \
  var _count = strlen((string)) + 1;      \
  Int8* _copy;                            \
  if ((_copy = malloc(_count)) != NULL) { \
    memcpy(_copy, (string), _count);      \
  }                                       \
  _copy;                                  \
})

/**
 * Returns the reversed string.
 *
 * - Parameter string: A string to reverse.
 */
#define _strrev(string)                 \
  do {                                  \
    var _i = 0;                         \
    var _j = strlen((string)) - 1;      \
    var _c = (Int8)0;                   \
    for (; _i < _j; _i += 1, _j -= 1) { \
      _c = string[_i];                  \
      string[_i] = string[_j];          \
      string[_j] = _c;                  \
    }                                   \
  } while (0)

/**
 * Converts an integer value to a null-terminated string using the specified
 * base and stores the result in the string.
 *
 * - Parameters:
 *   - value: The integer to convert to a string.
 *   - text: A buffer that is large enough to store the converted string.
 *   - radix: The base to use for the string representation. radix must be at
 *            least 2 and at most 36.
 *   - is_uppercase: Pass `true` to use uppercase letters to represent numerals
 *                   greater than 9, or `false` to use lowercase letters.
 */
#define _itoa(value, text, radix, is_uppercase)                   \
  do {                                                            \
    var _sum = (value);                                           \
    var _i = 0;                                                   \
    var _digit = 0;                                               \
    do {                                                          \
      _digit = _sum % (radix);                                    \
      if (_digit < 0xA) {                                         \
        (text)[_i] = '0' + _digit;                                \
      } else {                                                    \
        (text)[_i] = ((is_uppercase) ? 'A' : 'a') + _digit - 0xA; \
      }                                                           \
      _i += 1;                                                    \
      _sum /= (radix);                                            \
    } while (_sum);                                               \
    (text)[_i] = '\0';                                            \
    _strrev((text));                                              \
} while (0)

/**
 * Swaps two blocks of memory.
 *
 * This function exchanges the contents of two memory areas. The areas must not
 * overlap.
 *
 * - Parameters:
 *   - lhs: A pointer to the first memory block.
 *   - rhs: A pointer to the second memory block.
 *   - count: The number of bytes to swap.
 */
#define _memswap(lhs, rhs, count) \
  do {                            \
    var _p = (Int8*)(lhs);        \
    var _q = (Int8*)(rhs);        \
    var _p_end = _p + (count);    \
    while (_p < _p_end) {         \
      var _delta = *_p;           \
      *_p = *_q;                  \
      *_q = _delta;               \
      _p += 1;                    \
      _q += 1;                    \
    }                             \
  } while (0)

/**
 * Returns a number raised to a specified power then taken modulo a given
 * modulus.
 *
 * - Parameters:
 *   - x: The base value.
 *   - y: The power by which to raise `x`.
 *   - m: The modulus to apply after exponentiation.
 *
 * - Returns: The result of *x \*\* y mod m*.
 *
 * - Complexity: *O(log y)*
 */
#define _pow_mod(x, y, m) ({    \
  var _x = x % m;               \
  var _y = y;                   \
  var result = x;               \
  result = 1; /* For type */    \
  while (_y > 0) {              \
    if (_y % 2 != 0) {          \
      result = result * _x % m; \
    }                           \
    _x = _x * _x % m;           \
    _y /= 2;                    \
  }                             \
  result % m;                   \
})

#endif /* _Foundation_h */

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
