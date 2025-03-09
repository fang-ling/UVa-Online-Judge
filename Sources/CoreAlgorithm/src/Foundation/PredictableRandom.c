/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* PredictableRandom.c                                  /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: March 9, 2025                                  \ \ \_/__ \_\ \_  __  */
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

#include "Foundation/PredictableRandom.h"

/* MARK: - Private methods */

/* Returns a single 32-bit predictable random value. */
static UInt32 __predictable_random_word() {
  static UInt64 seed = 8682522807148012ull;
  seed = (seed * 0x5deece66dull + 0xbull) & ((1ull << 48) - 1);
  return (UInt32)(seed >> 16);
}

/*
 * Copyright (c) 2008, Damien Miller <djm@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Modified from OpenBSD: arc4random_uniform.c
 */
/*
 * Returns a single 32-bit predictable random value, uniformly distributed but
 * less than upper_bound, avoiding "modulo bias" when the upper bound is not a
 * power of two.
 */
static UInt32 _predictable_random_word(UInt32 upper_bound) {
  if (upper_bound < 2) {
    return 0;
  }

  /* 2**32 % x == (2**32 - x) % x */
  var min = -upper_bound % upper_bound;

  /*
   * This could theoretically loop forever but each retry has p > 0.5 (worst
   * case, usually far better) of selecting a number inside the range we need,
   * so it should rarely need to re-roll.
   */
  var value = 0u;
  while (true) {
    value = __predictable_random_word();
    if (value >= min) {
      break;
    }
  }

  return value % upper_bound;
}

/* MARK: - Creating a Random Value */

/* Returns a predictable random value within the specified range. */
Int64 int64_predictable_random(Int64 minimum, Int64 maximum) {
  precondition(minimum <= maximum, "Range requires lowerBound <= upperBound.");
  
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
