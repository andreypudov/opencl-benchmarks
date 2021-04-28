cmake_minimum_required(VERSION 3.14)

project(benchmarks-test VERSION 0.0.1 LANGUAGES CXX)

include_directories("${CMAKE_SOURCE_DIR}/include"
                    "${CMAKE_SOURCE_DIR}/lib/benchmarks/include"
                    "${PROJECT_SOURCE_DIR}/include")

add_executable(benchmarks-test "src/benchmarks.cc" "src/vector_multiplication.cc")
target_link_libraries(benchmarks-test PRIVATE gtest gmock gtest_main benchmarks)

add_test(COMMAND benchmarks-test)