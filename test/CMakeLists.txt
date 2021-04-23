cmake_minimum_required(VERSION 3.14)

project(opencl-benchmarks-test VERSION 0.0.1 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG master)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory("lib/benchmarks")