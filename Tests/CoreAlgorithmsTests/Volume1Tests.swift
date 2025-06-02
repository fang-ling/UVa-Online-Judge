/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Volume1Tests.swift                                   /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: February 7, 2025                               \ \ \_/__ \_\ \_  __  */
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

extension UVaOnlineJudgeTests {
  struct Volume1Tests {
    @Test func testP100() throws {
      try run(main: p100_main, for: 100, caseCount: 7).forEach { result in
        #expect(result.0 == result.1)
      }
    }

    @Test func testP102() throws {
      try run(main: p102_main, for: 102, caseCount: 4).forEach { result in
        #expect(result.0 == result.1)
      }
    }

    @Test func testP108() throws {
      try run(main: p108_main, for: 108, caseCount: 3).forEach { result in
        #expect(result.0 == result.1)
      }
    }

    @Test func testP113() throws {
      try run(main: p113_main, for: 113, caseCount: 4).forEach { result in
        #expect(result.0 == result.1)
      }
    }

    @Test func testP136() throws {
      try run(main: p136_main, for: 136, caseCount: 1).forEach { result in
        #expect(result.0 == result.1)
      }
    }
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
