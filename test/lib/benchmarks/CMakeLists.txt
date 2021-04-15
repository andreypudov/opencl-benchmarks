cmake_minimum_required(VERSION 3.14)

project(benchmarks-test VERSION 0.0.1 LANGUAGES CXX)

include_directories(SYSTEM "${gtest_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/include"
                    "${PROJECT_SOURCE_DIR}/include")

add_library(benchmarks-test STATIC "src/vector_multiplication.cc")