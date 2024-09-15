// swift-tools-version: 5.10

import PackageDescription

let volume5 = [
  "594.0", "594.1", "594.2"
]

let package = Package(
  name: "hxy",
  targets: [
    .target(name: "CUVaOnlineJudge"),
    .testTarget(
      name: "hxy",
      dependencies: ["CUVaOnlineJudge"],
      path: "Tests/hxy",
      resources:
        volume5.map({ .process("Resources/volume_5/\($0).in") }) +
        volume5.map({ .process("Resources/volume_5/\($0).out") })
    )
  ],
  cLanguageStandard: .c89
)
