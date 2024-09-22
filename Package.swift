// swift-tools-version: 6.0

import PackageDescription

let volume5 = [
  "594.0", "594.1", "594.2"
]
let volume127 = [
  "12720.0", "12720.1"
]

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
