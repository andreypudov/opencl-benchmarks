cmake_minimum_required(VERSION 3.14)

project(benchmarks VERSION 0.0.1 LANGUAGES C)

find_package(OpenCL REQUIRED)

include_directories("${CMAKE_SOURCE_DIR}/include"
                    "${CMAKE_SOURCE_DIR}/lib/opencl/include"
                    "${PROJECT_SOURCE_DIR}/include")

add_library(benchmarks STATIC "src/vecmul/cpu_vecmul.c"
                              "src/vecmul/opencl/kernel.c"
                              "src/vecmul/opencl/preparation.c"
                              "src/vecmul/opencl/release.c")
target_link_libraries(benchmarks PRIVATE OpenCL::OpenCL opencl)