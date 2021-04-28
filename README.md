# OpenCL Benchmarks

## Build
```
mkdir build && cd build/
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=. ..
cmake --build . --target install --config Release

GTEST_OUTPUT=xml:sample.xml ctest --verbose
```