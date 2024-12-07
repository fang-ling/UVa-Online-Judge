/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* BigIntTests.swift                                    /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: December 1, 2024                               \ \ \_/__ \_\ \_  __  */
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

import Foundation
@testable import hxy
import Testing

@Suite
struct BigIntTests {
  @Test func testBigIntInitWhiteBox() async throws {
    let numberPointer = big_int_init("193581934212361123331930619348", 10)!
    #expect(numberPointer.pointee._magnitude_count == 2)
    #expect(numberPointer.pointee._magnitude_capacity == 2)
    /*
     * 193581934212361123331930619348 equals
     * 10494097681 * 2**64 + 6445224650915216852
     */
    #expect(numberPointer.pointee._magnitude[0] == 10494097681)
    #expect(numberPointer.pointee._magnitude[1] == 6445224650915216852)
    big_int_deinit(numberPointer)
  }

  @Test func testBigIntBitCount() async throws {
    var numberPointer = big_int_init("123611935819342123331934819306", 10)
    #expect(big_int_bit_count(numberPointer) == 97)
    big_int_deinit(numberPointer)

    numberPointer = big_int_init("-123611935819342123331934819306", 10)
    #expect(big_int_bit_count(numberPointer) == 97)
    big_int_deinit(numberPointer)

    numberPointer = big_int_init("0", 10)
    #expect(big_int_bit_count(numberPointer) == 0)
    big_int_deinit(numberPointer)
  }

  @Test func testDivideOneWord() async throws {
    let numberPointer = big_int_init("193581934212361123331930619348", 10)!
    let divisorPointer = big_int_init("19358", 10)!
    let results = big_int_divide(numberPointer, divisorPointer)!;

    #expect(
      results[0]!.pointee._magnitude[0] == 542106 &&
      results[0]!.pointee._magnitude[1] == UInt64(9275162996903914717)
    )
    #expect(results[1]!.pointee._magnitude[0] == 3694)
  }
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
