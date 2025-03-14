/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* CoreAlgorithm.swift                                  /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: September 15, 2024                             \ \ \_/__ \_\ \_  __  */
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
import Testing

@Suite(.serialized)
struct UVaOnlineJudgeTests { }

func run(
  main: () -> Void,
  for problem: Int,
  caseCount: Int,
  skipping: [Int] = []
) throws -> [(Swift.String, Swift.String)] {
  var results: [(Swift.String, Swift.String)] = []
  for i in 0 ..< caseCount {
    if (skipping.contains(i)) {
      continue;
    }
    
    let `case` = "\(problem).\(i)"
    let inputPath = Bundle.module.path(forResource: `case`, ofType: "in")!
    let outputPath = Bundle.module.path(forResource: `case`, ofType: "out")!
    let solutionPath = "/tmp/CoreAlgorithm_\(`case`).out"
    
    freopen(inputPath, "r", stdin)
    freopen(solutionPath, "w", stdout)
    main()
    fclose(stdin)
    fclose(stdout)
    
    let output = try Swift.String(contentsOfFile: outputPath, encoding: .utf8)
    let solution = try Swift.String(contentsOfFile: solutionPath, encoding: .utf8)
    results.append((output, solution))
  }
  return results
}

/*import XCTest
@testable import CoreAlgorithm

final class CoreAlgorithm: XCTestCase {
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
      let solutionPath = "/tmp/CoreAlgorithm_\(`case`).out"
      
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
  
  func testVolume11() throws {
    try CoreAlgorithm.judge(solution: p1124_main, for: 1124, caseCount: 5)
  }
  
  func testVolume111() throws {
    try CoreAlgorithm.judge(solution: p11172_main, for: 11172, caseCount: 8)
  }
  
  func testVolume127() throws {
    try CoreAlgorithm.judge(solution: p12720_main, for: 12720, caseCount: 2)
  }
  
  func testVolume130() throws {
    try CoreAlgorithm.judge(solution: p13025_main, for: 13025, caseCount: 1)
  }
}*/

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
