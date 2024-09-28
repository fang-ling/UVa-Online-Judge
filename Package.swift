// swift-tools-version: 6.0

import PackageDescription

fileprivate func process(volume: Int, problems: [(Int, Int)]) -> [Resource] {
  let allProblems = problems.flatMap { problem in
    (0 ..< problem.1).map({ "\(problem.0).\($0)" })
  }
  
  var resources = allProblems.map({
    Resource.process("Resources/volume_\(volume)/\($0).in")
  })
  resources += allProblems.map({
    Resource.process("Resources/volume_\(volume)/\($0).out")
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
