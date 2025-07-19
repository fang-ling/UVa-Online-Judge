// swift-tools-version: 6.1
/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Package.swift                                        /'___\ /\_ \          */
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

import PackageDescription

fileprivate func process(_ problems: [(Int, Int)]) -> [Resource] {
  let allProblems = problems.flatMap { problem in
    (0 ..< problem.1).map({ "\(problem.0).\($0)" })
  }
  
  var resources = allProblems.map({
    let volume = (Int($0.components(separatedBy: ".").first ?? "0") ?? 0) / 100
    return Resource.process("Resources/Volume\(volume)/\($0).in")
  })
  resources += allProblems.map({
    let volume = (Int($0.components(separatedBy: ".").first ?? "0") ?? 0) / 100
    return Resource.process("Resources/Volume\(volume)/\($0).out")
  })
  
  return resources
}

let package = Package(
  name: "core-algorithms",
  products: [
    .library(name: "CoreAlgorithms", targets: ["CoreAlgorithms"])
  ],
  targets: [
    .target(name: "CoreAlgorithms"),
    .target(
      name: "UVaOnlineJudge",
      dependencies: ["CoreAlgorithms"]
    ),
    .testTarget(
      name: "UVaOnlineJudgeTests",
      dependencies: ["UVaOnlineJudge"],
      resources: process([
        (100, 7)
      ]),
      swiftSettings: [.interoperabilityMode(.Cxx)]
    )
  ],
  cxxLanguageStandard: .cxx11
)

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


//let volumes =
//  process(
//    volume: 1,
//    problems: [
//      , (102, 4), (108, 3), (113, 4), (136, 1)
//    ]
//  ) +
//  process(volume: 2, problems: [(272, 4), (299, 6)]) +
//  process(volume: 3, problems: [(374, 5)]) +
//  process(volume: 4, problems: [(424, 5), (458, 2), (465, 5), (494, 8)]) +
//  process(volume: 5, problems: [(591, 7), (594, 3)]) +
//  process(volume: 6, problems: [(621, 3), (673, 6)]) +
//  process(volume: 7, problems: [(713, 5), (748, 3)]) +
//  process(volume: 11, problems: [(1124, 5)]) +
//  process(volume: 12, problems: [(1203, 8)]) +
//  process(volume: 15, problems: [(1585, 4)]) +
//  process(volume: 17, problems: [(1709, 3)]) +
//  process(
//    volume: 100,
//    problems: [
//      (10018, 4), (10035, 7), (10038, 6), (10041, 4), (10055, 7), (10071, 3),
//      (10082, 5)
//    ]
//  ) +
//  process(
//    volume: 101,
//    problems: [(10106, 4), (10110, 4), (10114, 2), (10189, 3)]
//  ) +
//  process(volume: 103, problems: [(10300, 4), (10324, 5), (10370, 3)]) +
//  process(volume: 104, problems: [(10424, 7)]) +
//  process(volume: 105, problems: [(10550, 3)]) +
//  process(volume: 106, problems: [(10696, 7)]) +
//  process(volume: 107, problems: [(10783, 5)]) +
//  process(volume: 108, problems: [(10812, 5)]) +
//  process(volume: 109, problems: [(10963, 4)]) +
//  process(volume: 110, problems: [(11044, 3), (11078, 4)]) +
//  process(volume: 111, problems: [(11172, 8)]) +
//  process(volume: 113, problems: [(11332, 6), (11364, 3)]) +
//  process(volume: 114, problems: [(11498, 6)]) +
//  process(volume: 115, problems: [(11547, 3), (11559, 3)]) +
//  process(volume: 116, problems: [(11614, 3), (11679, 3), (11687, 3)]) +
//  process(
//    volume: 117,
//    problems: [(11764, 2), (11799, 4), (11723, 5), (11727, 7)]
//  ) +
//  process(volume: 118, problems: [(11809, 4), (11805, 3), (11879, 5)]) +
//  process(volume: 119, problems: [(11942, 5)]) +
//  process(volume: 120, problems: [(12015, 3)]) +
//  process(volume: 122, problems: [(12250, 4), (12279, 4), (12289, 3)]) +
//  process(volume: 123, problems: [(12372, 4)]) +
//  process(volume: 124, problems: [(12403, 2), (12478, 1), (12468, 3)]) +
//  process(volume: 125, problems: [(12503, 4), (12577, 4)]) +
//  process(volume: 126, problems: [(12658, 2), (12696, 2), (12646, 3)]) +
//  process(volume: 127, problems: [(12720, 2)]) +
//  process(volume: 129, problems: [(12917, 3)]) +
//  process(volume: 130, problems: [(13012, 2), (13025, 1), (13034, 2)]) +
//  process(volume: 131, problems: [(13130, 3)])
