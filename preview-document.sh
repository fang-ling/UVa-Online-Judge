clang -extract-api \
      --product-name=CoreAlgorithm \
      -o .build/symbol-graphs/CoreAlgorithm.symbols.json \
      -x objective-c-header \
      Sources/CoreAlgorithm/include/Foundation/*.h \
      -I . \
      -isysroot $(xcrun --show-sdk-path) \
      -F $(xcrun --show-sdk-path)/System/Library/Frameworks

$(xcrun --find docc) preview \
                     Sources/CoreAlgorithm/Documentation.docc \
                     -o .build/.docc-build \
                     --additional-symbol-graph-dir .build/symbol-graphs
