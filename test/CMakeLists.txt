cmake_minimum_required(VERSION 3.14)

project(opencl-benchmarks-test VERSION 0.0.1 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG master)
FetchContent_MakeAvailable(googletest)

add_subdirectory("src/opencl-benchmarks")
add_subdirectory("lib/benchmarks")