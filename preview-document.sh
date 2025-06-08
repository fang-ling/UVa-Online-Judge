clang -extract-api \
      --product-name=CoreAlgorithms \
      -o .build/symbol-graphs/CoreAlgorithms.symbols.json \
      -x objective-c-header \
      Sources/CoreAlgorithms/include/Foundation/*.h \
      -I . \
      -isysroot $(xcrun --show-sdk-path) \
      -F $(xcrun --show-sdk-path)/System/Library/Frameworks

$(xcrun --find docc) preview \
                     Sources/CoreAlgorithms/Documentation.docc \
                     -o .build/.docc-build \
                     --additional-symbol-graph-dir .build/symbol-graphs
