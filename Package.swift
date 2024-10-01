// swift-tools-version: 6.0
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
 * This source file is part of the hxy open source project.
 *
 * Copyright (c) 2024 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */

import PackageDescription

fileprivate func process(volume: Int, problems: [(Int, Int)]) -> [Resource] {
  let allProblems = problems.flatMap { problem in
    (0 ..< problem.1).map({ "\(problem.0).\($0)" })
  }
  
  var resources = allProblems.map({
    Resource.process("Resources/Volume\(volume)/\($0).in")
  })
  resources += allProblems.map({
    Resource.process("Resources/Volume\(volume)/\($0).out")
  })
  
  return resources
}

let volume5 = process(volume: 5, problems: [(594, 3)])
let volume118 = process(volume: 118, problems: [(11809, 4)])
let volume127 = process(volume: 127, problems: [(12720, 2)])

let package = Package(
  name: "hxy",
  targets: [
    .target(name: "hxy"),
    .testTarget(
      name: "hxyTests",
      dependencies: ["hxy"],
      path: "Tests/hxy",
      resources:
        volume5 + volume118 + volume127
    )
  ],
  cLanguageStandard: .c89
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
