/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* RedBlackTreeTests.swift                              /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: March 5, 2025                                  \ \ \_/__ \_\ \_  __  */
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

import Foundation
@testable import CoreAlgorithms
import Testing

@Suite
struct RedBlackTreeTests {
  @Test func testInit() {
    let tree = red_black_tree_init(
      Int64(MemoryLayout<Int>.size),
      Int64(MemoryLayout<Int>.size),
      { (lhs: UnsafeRawPointer?, rhs: UnsafeRawPointer?) -> Int32 in
        let a = lhs!.load(as: Int.self)
        let b = rhs!.load(as: Int.self)

        if a < b {
          return -1
        } else if a > b {
          return 1
        } else {
          return 0
        }
      }
    )

    red_black_tree_deinit(tree)
  }

  @Test func testInsert() {
    let tree = red_black_tree_init(
      Int64(MemoryLayout<Int>.size),
      Int64(MemoryLayout<Int>.size),
      { (lhs: UnsafeRawPointer?, rhs: UnsafeRawPointer?) -> Int32 in
        let a = lhs!.load(as: Int.self)
        let b = rhs!.load(as: Int.self)

        if a < b {
          return -1
        } else if a > b {
          return 1
        } else {
          return 0
        }
      }
    )

    var key = 19358
    var value = 19342
    red_black_tree_insert(tree, &key, &value)
    #expect(tree?.pointee.count == 1)

    red_black_tree_deinit(tree)
  }

  @Test func testMin() {
    let tree = red_black_tree_init(
      Int64(MemoryLayout<Int>.size),
      Int64(MemoryLayout<Int>.size),
      { (lhs: UnsafeRawPointer?, rhs: UnsafeRawPointer?) -> Int32 in
        let a = lhs!.load(as: Int.self)
        let b = rhs!.load(as: Int.self)

        if a < b {
          return -1
        } else if a > b {
          return 1
        } else {
          return 0
        }
      }
    )

    var key = 19358
    var value = 19342
    red_black_tree_insert(tree, &key, &value)

    key = 19306
    value = 19348
    red_black_tree_insert(tree, &key, &value)

    var minKey = 0
    var minValue = 0
    red_black_tree_min(tree, &minKey, &minValue)
    #expect(minKey == key)
    #expect(minValue == value)


    red_black_tree_deinit(tree)
  }

  @Test func testMax() {
    let tree = red_black_tree_init(
      Int64(MemoryLayout<Int>.size),
      Int64(MemoryLayout<Int>.size),
      { (lhs: UnsafeRawPointer?, rhs: UnsafeRawPointer?) -> Int32 in
        let a = lhs!.load(as: Int.self)
        let b = rhs!.load(as: Int.self)

        if a < b {
          return -1
        } else if a > b {
          return 1
        } else {
          return 0
        }
      }
    )

    var key = 19306
    var value = 19348
    red_black_tree_insert(tree, &key, &value)

    key = 19358
    value = 19342
    red_black_tree_insert(tree, &key, &value)

    var maxKey = 0
    var maxValue = 0
    red_black_tree_max(tree, &maxKey, &maxValue)
    #expect(maxKey == key)
    #expect(maxValue == value)


    red_black_tree_deinit(tree)
  }

  @Test func testRemove() {
    let tree = red_black_tree_init(
      Int64(MemoryLayout<Int>.size),
      Int64(MemoryLayout<Int>.size),
      { (lhs: UnsafeRawPointer?, rhs: UnsafeRawPointer?) -> Int32 in
        let a = lhs!.load(as: Int.self)
        let b = rhs!.load(as: Int.self)

        if a < b {
          return -1
        } else if a > b {
          return 1
        } else {
          return 0
        }
      }
    )

    var key = 19358
    var value = 19342
    red_black_tree_insert(tree, &key, &value)
    #expect(tree?.pointee.count == 1)

    var removedValue = 0
    red_black_tree_remove(tree, &key, &removedValue)
    #expect(value == removedValue)
    #expect(tree?.pointee.count == 0)

    red_black_tree_deinit(tree)
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
