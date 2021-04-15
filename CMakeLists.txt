cmake_minimum_required(VERSION 3.14)

project(opencl-benchmarks VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_CPPCHECK "cppcheck; --std=c11; --enable=all;")
# set(CMAKE_C_CLANG_TIDY "clang-tidy")
set(CMAKE_C_CPPLINT clang-format; --dry-run; --Werror)

add_subdirectory("src/opencl-benchmarks")
add_subdirectory("lib/benchmarks")

enable_testing()
add_subdirectory("test")

install(TARGETS opencl-benchmarks DESTINATION bin/)
