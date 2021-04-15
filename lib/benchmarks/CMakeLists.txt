cmake_minimum_required(VERSION 3.14)

project(benchmarks VERSION 0.0.1 LANGUAGES C)

include_directories("${CMAKE_SOURCE_DIR}/include"
                    "${PROJECT_SOURCE_DIR}/include")

add_library(benchmarks STATIC "src/vector_multiplication.c")