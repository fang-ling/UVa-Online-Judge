/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* ArrayTests.swift                                     /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: September 21, 2024                             \ \ \_/__ \_\ \_  __  */
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

import XCTest
@testable import hxy

final class ArrayTests: XCTestCase {
  func testCount() {
    let array = array_init(Int(MemoryLayout<Int>.size))!
    XCTAssertEqual(array.pointee.count, 0)
    
    var element = 20
    withUnsafeMutablePointer(to: &element) { element in
      array_append(array, element)
    }
    XCTAssertEqual(array.pointee.count, 1)
    
    element = 40
    withUnsafeMutablePointer(to: &element) { element in
      array_append(array, element)
    }
    XCTAssertEqual(array.pointee.count, 2)
    
    array_remove_last(array, nil)
    XCTAssertEqual(array.pointee.count, 1)
    
    array_deinit(array)
  }
  
  struct Person {
    let name: String
    let age: Int
  }
  
  func testAppend() {
    let array = array_init(Int(MemoryLayout<Person>.size))!
    XCTAssertEqual(array.pointee.count, 0)
    
    
    var person = Person(name: "Yüan-yüeh", age: 18)
    withUnsafeMutablePointer(to: &person) { person in
      array_append(array, person)
    }
    XCTAssertEqual(array.pointee.count, 1)
    
    array_deinit(array)
  }
  
  func testRemoveLast() {
    let array = array_init(Int(MemoryLayout<Int>.size))!
   
    var element = 58
    array_append(array, &element)
    var lastElement = -1
    array_remove_last(array, &lastElement)
    XCTAssertEqual(lastElement, 58)
    
    element = 48
    array_append(array, &element)
    
    element = 33
    array_append(array, &element)
    
    for i in 0 ..< 20 {
      var _i = i
      array_append(array, &_i)
    }
    var elements = [48, 33] + Swift.Array(0 ..< 20)
    elements.reverse()
    var i = 0
    while array.pointee.count > 0 {
      array_remove_last(array, &lastElement)
      XCTAssertEqual(lastElement, elements[i])
      i += 1
    }
    
    array_deinit(array)
  }
  
  func testSubscript() {
    let array = array_init(Int(MemoryLayout<Int>.size))!
    
    for i in 0 ..< 20 {
      var _i = i
      array_append(array, &_i)
    }
    
    var element = 58
    array_write(array, 16, &element)
    element = -1
    array_read(array, 16, &element)
    XCTAssertEqual(element, 58)
    
    array_deinit(array)
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
