/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* BigIntegerTests.swift                                /'___\ /\_ \          */
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
struct BigIntegerTests {
  @Test func testBigIntegerInitWhiteBox() async throws {
    var numberPointer = big_integer_init_from_string(
      "193581934212361123331930619348",
      10
    )!
    #expect(numberPointer.pointee._magnitude_count == 4)
    #expect(numberPointer.pointee._magnitude_capacity == 4)
    /*
     * 193581934212361123331930619348 equals
     * 2 * 2**96 + 1904163089 * 2 ** 64 + 1500645803 * 2 ** 32 + U(-144409132)
     *
     * U(-144409132) = 4150558164
     */
    #expect(numberPointer.pointee._magnitude[0] == 2)
    #expect(numberPointer.pointee._magnitude[1] == 1904163089)
    #expect(numberPointer.pointee._magnitude[2] == 1500645803)
    #expect(numberPointer.pointee._magnitude[3] == -144409132)
    big_integer_deinit(numberPointer)

    numberPointer = big_integer_init_from_string("de0b6b3a7640000", 16)!
    #expect(numberPointer.pointee._magnitude_count == 2)
    #expect(numberPointer.pointee._magnitude_capacity == 2)
    /*
     * 0xde0b6b3a7640000 equals 232830643 * 2**32 + 2808348672
     *
     * U(-1486618624) = 2808348672
     */
    #expect(numberPointer.pointee._magnitude[0] == 232830643)
    #expect(numberPointer.pointee._magnitude[1] == -1486618624)
    big_integer_deinit(numberPointer)
  }

  @Test func testBigIntegerToString() async throws {
    var numberPointer = big_integer_init_from_string(
      "193581934212361123331930619348",
      10
    )!

    var stringPointer = big_integer_to_string(numberPointer, 10, false)!
    var string = String(cString: stringPointer);
    #expect(string == "193581934212361123331930619348")
    stringPointer.deallocate()
    numberPointer.deallocate()

    var longString =
      "1935819342123611233319306193481" + "193581934212361123331930619348" +
      "193581934212361123331930619348" + "193581934212361123331930619348" +
      "193581934212361123331930619348" + "193581934212361123331930619348" +
      "193581934212361123331930619348" + "193581934212361123331930619348" +
      "193581934212361123331930619348" + "193581934212361123331930619348" +
      "193581934212361123331930619348" + "193581934212361123331930619348" +
      "193581934212361123331930619348" + "193581934212361123331930619348" +
      "193581934212361123331930619348" + "193581934212361123331930619348" +
      "193581934212361123331930619348" + "193581934212361123331930619348" +
      "193581934212361123331930619348" + "193581934212361123331930619348"
    numberPointer = big_integer_init_from_string(longString, 10)!
    stringPointer = big_integer_to_string(numberPointer, 10, false)!
    string = String(cString: stringPointer)
    #expect(string == longString)
    stringPointer.deallocate()
    numberPointer.deallocate()

    longString = ""
    for _ in 1 ... 2430 {
      longString += "\(1)"
    }
    numberPointer = big_integer_init_from_string(longString, 10)!
    stringPointer = big_integer_to_string(numberPointer, 10, false)!
    string = String(cString: stringPointer)
    #expect(string == longString)
    #expect(string.count == longString.count)
    stringPointer.deallocate()
    numberPointer.deallocate()

    longString = "1" + String(repeating: "0", count: 2500)
    numberPointer = big_integer_init_from_string(longString, 10)!
    stringPointer = big_integer_to_string(numberPointer, 10, false)!
    string = String(cString: stringPointer)
    #expect(string == longString)
    #expect(string.count == longString.count)
    stringPointer.deallocate()
    numberPointer.deallocate()
  }

  @Test func testBigIntegerAdd() async throws {
    var a = "18863046225568582542016021945328306014125955818525918809"
    var b = "49558923010544057053463173587344941434565966176383118780" +
            "0740923395817893020463093092080"
    var c = "49558923010544057053463173587346827739188523034637320382" +
            "2686251701832018976281619010889"
    var aPointer = big_integer_init_from_string(a, 10)!
    var bPointer = big_integer_init_from_string(b, 10)!
    var cPointer = big_integer_add(aPointer, bPointer)!
    var stringPointer = big_integer_to_string(cPointer, 10, false)!
    #expect(c == String(cString: stringPointer))
    aPointer.deallocate()
    bPointer.deallocate()
    cPointer.deallocate()
    stringPointer.deallocate()

    a = "9999999999999999999999999999999999999999999999999999999999999999" +
        "9999999999999999999999"
    b = "1"
    c = "1000000000000000000000000000000000000000000000000000000000000000" +
        "00000000000000000000000"
    aPointer = big_integer_init_from_string(a, 10)!
    bPointer = big_integer_init_from_string(b, 10)!
    cPointer = big_integer_add(aPointer, bPointer)!
    stringPointer = big_integer_to_string(cPointer, 10, false)!
    #expect(c == String(cString: stringPointer))
    aPointer.deallocate()
    bPointer.deallocate()
    cPointer.deallocate()
    stringPointer.deallocate()

    a = String(repeating: "9", count: 19358)
    b = String(repeating: "1", count: 1)
    c = "1" + String(repeating: "0", count: 19358)
    aPointer = big_integer_init_from_string(a, 10)!
    bPointer = big_integer_init_from_string(b, 10)!
    cPointer = big_integer_add(aPointer, bPointer)!
    stringPointer = big_integer_to_string(cPointer, 10, false)!
    #expect(c == String(cString: stringPointer))
    aPointer.deallocate()
    bPointer.deallocate()
    cPointer.deallocate()
    stringPointer.deallocate()

    a = "19358"
    b = "-12361"
    c = "6997"
    aPointer = big_integer_init_from_string(a, 10)!
    bPointer = big_integer_init_from_string(b, 10)!
    cPointer = big_integer_add(aPointer, bPointer)!
    stringPointer = big_integer_to_string(cPointer, 10, false)!
    #expect(c == String(cString: stringPointer))
    aPointer.deallocate()
    bPointer.deallocate()
    cPointer.deallocate()
    stringPointer.deallocate()

    a = "19358"
    b = "-19358"
    c = "0"
    aPointer = big_integer_init_from_string(a, 10)!
    bPointer = big_integer_init_from_string(b, 10)!
    cPointer = big_integer_add(aPointer, bPointer)!
    stringPointer = big_integer_to_string(cPointer, 10, false)!
    #expect(c == String(cString: stringPointer))
    aPointer.deallocate()
    bPointer.deallocate()
    cPointer.deallocate()
    stringPointer.deallocate()

    a = "12361"
    b = "-19358"
    c = "-6997"
    aPointer = big_integer_init_from_string(a, 10)!
    bPointer = big_integer_init_from_string(b, 10)!
    cPointer = big_integer_add(aPointer, bPointer)!
    stringPointer = big_integer_to_string(cPointer, 10, false)!
    #expect(c == String(cString: stringPointer))
    aPointer.deallocate()
    bPointer.deallocate()
    cPointer.deallocate()
    stringPointer.deallocate()
  }

  @Test func testBigIntegerSubtract() async throws {
    var a = "2"
    var b = "1"
    var c = "1"
    var aPointer = big_integer_init_from_string(a, 10)!
    var bPointer = big_integer_init_from_string(b, 10)!
    var cPointer = big_integer_subtract(aPointer, bPointer)!
    var stringPointer = big_integer_to_string(cPointer, 10, false)!
    #expect(c == String(cString: stringPointer))
    aPointer.deallocate()
    bPointer.deallocate()
    cPointer.deallocate()
    stringPointer.deallocate()

    a = "12361"
    b = "-19358"
    c = "31719"
    aPointer = big_integer_init_from_string(a, 10)!
    bPointer = big_integer_init_from_string(b, 10)!
    cPointer = big_integer_subtract(aPointer, bPointer)!
    stringPointer = big_integer_to_string(cPointer, 10, false)!
    #expect(c == String(cString: stringPointer))
    aPointer.deallocate()
    bPointer.deallocate()
    cPointer.deallocate()
    stringPointer.deallocate()
  }

//  @Test func testMutableBigIntegerDivide() async throws {
//    let dividend = big_integer_init_from_string(
//      "1" + String(String(repeating: "0", count: 2500)),
//      10
//    )!
//    let divisor = big_integer_init_from_string("de0b6b3a7640000", 16)!
//
//
//    for i in 0 ..< dividend.pointee._magnitude_count {
//      print("\(i): \(dividend.pointee._magnitude[Int(i)])")
//    }
//    print()
//    for i in 0 ..< divisor.pointee._magnitude_count {
//      print(divisor.pointee._magnitude[Int(i)], terminator: ", ")
//    }
//    print()
//
//    let lhs = mutable_big_integer_init_from_words(
//      dividend.pointee._magnitude,
//      dividend.pointee._magnitude_count
//    )!
//    let rhs = mutable_big_integer_init_from_words(
//      divisor.pointee._magnitude,
//      divisor.pointee._magnitude_count
//    )
//    let quotientAndRemainder = mutable_big_integer_divide(lhs, rhs)!
//    let quotient = quotientAndRemainder[0]!
//    let remainder = quotientAndRemainder[1]!
//
////    for i in quotient.pointee._offset ..< quotient.pointee._magnitude_count
//    var j = 0
//    for i in (quotient.pointee._offset ..< quotient.pointee._offset + quotient.pointee._magnitude_count).reversed() {
//      print("\(UInt32(bitPattern: quotient.pointee._magnitude[Int(i)])) * 2 ** (\(32 * j))", terminator: " + ")
//      j += 1;
//    }
//    j = 0;
////    print(quotient.pointee._magnitude[3])
//    print("\n#######")
//    for i in (remainder.pointee._offset ..< remainder.pointee._offset + remainder.pointee._magnitude_count).reversed() {
//      print("\(UInt32(bitPattern: remainder.pointee._magnitude[Int(i)])) * 2 ** (\(32 * j))", terminator: " + ")
//      j += 1
//    }
////    print(remainder.pointee._magnitude[0])
////    print(remainder.pointee._magnitude[1])
////    print(remainder.pointee._magnitude[2])
////    print(remainder.pointee._magnitude[3])
//  }

//  @Test func testBigIntBitCount() async throws {
//    var numberPointer = big_int_init("123611935819342123331934819306", 10)
//    #expect(big_int_bit_count(numberPointer) == 97)
//    big_int_deinit(numberPointer)
//
//    numberPointer = big_int_init("-123611935819342123331934819306", 10)
//    #expect(big_int_bit_count(numberPointer) == 97)
//    big_int_deinit(numberPointer)
//
//    numberPointer = big_int_init("0", 10)
//    #expect(big_int_bit_count(numberPointer) == 0)
//    big_int_deinit(numberPointer)
//  }
//
//  @Test func testDivideOneWord() async throws {
//    let numberPointer = big_int_init("193581934212361123331930619348", 10)!
//    let divisorPointer = big_int_init("19358", 10)!
//    let results = big_int_divide(numberPointer, divisorPointer)!;
//
//    #expect(
//      results[0]!.pointee._magnitude[0] == 542106 &&
//      results[0]!.pointee._magnitude[1] == UInt64(9275162996903914717)
//    )
//    #expect(results[1]!.pointee._magnitude[0] == 3694)
//  }

//  @Test func testDivide() async throws {
//    let a = big_int_init("193581934212361123331930619348", 10)!
//    let b = big_int_init("193581934212361123331930619324", 10)!
//
//    let dividendPointer = mutable_big_integer_init()!
//    dividendPointer.pointee._magnitude = a.pointee._magnitude
//    dividendPointer.pointee._magnitude_capacity = a.pointee._magnitude_capacity
//    dividendPointer.pointee._magnitude_count = a.pointee._magnitude_count
//
//    let divisorPointer = mutable_big_integer_init()!
//    divisorPointer.pointee._magnitude = b.pointee._magnitude
//    divisorPointer.pointee._magnitude_capacity = b.pointee._magnitude_capacity
//    divisorPointer.pointee._magnitude_count = a.pointee._magnitude_count
//
//    var result = mutable_big_integer_divide(dividendPointer, divisorPointer)!
//
//    print(result[0]!.pointee._magnitude[0])
//    print(result[1]!.pointee._magnitude[0])
//  }
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
