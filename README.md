# OpenCL Benchmarks

## Build
```
mkdir build && cd build/
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_INSTALL_PREFIX=. ..
cmake --build . --target install --config Release
cmake --build . --target valgrind --config Release

GTEST_OUTPUT=xml:sample.xml ctest --verbose
```