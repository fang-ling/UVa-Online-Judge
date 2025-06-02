/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Volume117Tests.swift                                 /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 15, 2024                               \ \ \_/__ \_\ \_  __  */
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
  struct Volume117Tests {
    @Test func testP11723() throws {
      try run(main: p11723_main, for: 11723, caseCount: 5).forEach { result in
        #expect(result.0 == result.1)
      }
    }

    @Test func testP11727() throws {
      try run(main: p11727_main, for: 11727, caseCount: 7).forEach { result in
        #expect(result.0 == result.1)
      }
    }

    @Test func testP11764() throws {
      try run(main: p11764_main, for: 11764, caseCount: 2).forEach { result in
        #expect(result.0 == result.1)
      }
    }
    
    @Test func testP11799() throws {
      try run(main: p11799_main, for: 11799, caseCount: 4).forEach { result in
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
