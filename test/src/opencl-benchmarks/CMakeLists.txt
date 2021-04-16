cmake_minimum_required(VERSION 3.14)

project(opencl-benchmarks-test VERSION 0.0.1 LANGUAGES CXX)

include_directories("${CMAKE_SOURCE_DIR}/include"
                    "${CMAKE_SOURCE_DIR}/lib/benchmarks/include"
                    "${CMAKE_SOURCE_DIR}/src/opencl-benchmarks/include"
                    "${PROJECT_SOURCE_DIR}/include")

add_executable(opencl-benchmarks-test "src/opencl-benchmarks.cc")
target_link_libraries(opencl-benchmarks-test gtest_main benchmarks benchmarks-test)

add_test(COMMAND opencl-benchmarks-test)