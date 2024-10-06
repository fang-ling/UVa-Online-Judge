/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* hxy.swift                                            /'___\ /\_ \          */
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

import XCTest
@testable import hxy

final class hxy: XCTestCase {
  static func judge(
    solution: () -> Void,
    for problem: Int,
    caseCount: Int,
    skipping: [Int] = []
  ) throws {
    for i in 0 ..< caseCount {
      if (skipping.contains(i)) {
        continue;
      }
      
      let `case` = "\(problem).\(i)"
      let inputPath = Bundle.module.path(forResource: `case`, ofType: "in")!
      let outputPath = Bundle.module.path(forResource: `case`, ofType: "out")!
      let solutionPath = "/tmp/hxy_\(`case`).out"
      
      freopen(inputPath, "r", stdin)
      freopen(solutionPath, "w", stdout)
      solution()
      fclose(stdin)
      fclose(stdout)
      
      let output = try String(contentsOfFile: outputPath, encoding: .utf8)
      let solution = try String(contentsOfFile: solutionPath, encoding: .utf8)
      
      XCTAssertEqual(output, solution)
    }
  }
  
  func testVolume4() throws {
    try hxy.judge(solution: p465_main, for: 465, caseCount: 5)
  }
  
  func testVolume5() throws {
    try hxy.judge(solution: p594_main, for: 594, caseCount: 3)
  }
  
  func testVolume100() throws {
    try hxy.judge(solution: p10071_main, for: 10071, caseCount: 3)
  }
  
  func testVolume101() throws {
    try hxy.judge(solution: p10114_main, for: 10114, caseCount: 2)
  }
  
  func testVolume118() throws {
    try hxy.judge(solution: p11809_main, for: 11809, caseCount: 4)
  }
  
  func testVolume127() throws {
    try hxy.judge(solution: p12720_main, for: 12720, caseCount: 2)
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
