/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Foundation.h                                         /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: September 15, 2024                             \ \ \_/__ \_\ \_  __  */
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

#ifndef Foundation_h
#define Foundation_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define var __auto_type
#define let const __auto_type

typedef void Void;

typedef char Int8;
typedef unsigned char UInt8;

typedef short Int16;
typedef unsigned short UInt16;

typedef int Int32;
typedef unsigned int UInt32;

typedef long long Int64;
typedef unsigned long long UInt64;

typedef Int64 Int;

typedef float Float;
typedef double Double;

typedef Int8 Bool;
#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

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
 *   `ONLINE_JUDGE` symbol is not defined: If `condition` evaluates to `false`,
 *   stop program execution after printing `message`.
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
#ifdef ONLINE_JUDGE
#define precondition(condition, message) ((void)0)
#else
#define precondition(condition, message)    \
        do {                                \
          if (!(condition)) {               \
            do {                            \
              fprintf(                      \
                stderr,                     \
                "%s:%d: Fatal error: %s\n", \
                __FILE__,                   \
                __LINE__,                   \
                (message)                   \
              );                            \
              abort();                      \
            } while (0);                    \
          }                                 \
        } while (0)
#endif

#endif /* Foundation_h */

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
