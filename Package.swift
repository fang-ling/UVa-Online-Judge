// swift-tools-version: 6.0

import PackageDescription

let volume5 = [
  (594, 2)
].flatMap { problem in
  (0 ... problem.1).map({ "\(problem.0).\($0)" })
}

let volume127 = [
  (12720, 1)
].flatMap { problem in
  (0 ... problem.1).map({ "\(problem.0).\($0)" })
}

let package = Package(
  name: "hxy",
  targets: [
    .target(name: "hxy"),
    .testTarget(
      name: "hxyTests",
      dependencies: ["hxy"],
      path: "Tests/hxy",
      resources:
        volume5.map({ .process("Resources/volume_5/\($0).in") }) +
        volume5.map({ .process("Resources/volume_5/\($0).out") }) +
        volume127.map({ .process("Resources/volume_127/\($0).in") }) +
        volume127.map({ .process("Resources/volume_127/\($0).out") })
    )
  ],
  cLanguageStandard: .c89
)
