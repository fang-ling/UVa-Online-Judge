/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Number.h                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: November 14, 2024                              \ \ \_/__ \_\ \_  __  */
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

#ifndef Number_h
#define Number_h

#include "CFoundation.h"

/* MARK: - Numeric Values */

/* An 8-bit unsigned integer value type. */
typedef uint8_t UInt8;
/* A 16-bit unsigned integer value type. */
typedef uint16_t UInt16;
/* A 32-bit unsigned integer value type. */
typedef uint32_t UInt32;
/* A 64-bit unsigned integer value type. */
typedef uint64_t UInt64;
/* A 128-bit unsigned integer type. */
typedef unsigned __int128 UInt128;

/* An 8-bit signed integer value type. */
typedef int8_t Int8;
/* A 16-bit signed integer value type. */
typedef int16_t Int16;
/* A 32-bit signed integer value type. */
typedef int32_t Int32;
/* A 64-bit signed integer value type. */
typedef int64_t Int64;
/* A 128-bit signed integer type. */
typedef __int128 Int128;

/* A single-precision, floating-point value type. */
typedef float Float;
/* A double-precision, floating-point value type. */
typedef double Double;

/* The C 'char' type. */
typedef char Char;

/* MARK: - Logical Values */

/* A value type whose instances are either true or false. */
typedef bool Bool;

/* MARK: - Accessing Numeric Constants */

/* The maximum representable integer in Int32 */
#define INT32_MAXIMUM 0x7FFFFFFF

/* MARK: - Global Numeric Functions */
/* Use these functions with numeric values and other comparable types. */

/**
 * Returns the greater of two comparable values.
 *
 * - Parameters:
 *   - x: A value to compare.
 *   - y: Another value to compare.
 *
 * - Returns: The greater of `x` and `y`. If `x` is equal to `y`, returns `y`.
 */
#ifndef max
#define max(x, y)            \
        ({                   \
          var _x = (x);      \
          var _y = (y);      \
          _x > _y ? _x : _y; \
        })
#endif

/**
 * Returns the lesser of two comparable values.
 *
 * - Parameters:
 *   - x: A value to compare.
 *   - y: Another value to compare.
 *
 * - Returns: The lesser of `x` and `y`. If `x` is equal to `y`, returns `y`.
 */
#ifndef min
#define min(x, y)            \
        ({                   \
          var _x = (x);      \
          var _y = (y);      \
          _x < _y ? _x : _y; \
        })
#endif

/**
 * Returns the absolute value of the given number.
 *
 * - Parameter x: A signed number.
 *
 * - Returns: The absolute value of `x`.
 */
#define abs(x)               \
        ({                   \
          var _x = (x);      \
          _x > 0 ? _x : -_x; \
        })

#endif /* Number_h */

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
