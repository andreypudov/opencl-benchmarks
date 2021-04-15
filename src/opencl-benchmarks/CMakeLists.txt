cmake_minimum_required(VERSION 3.14)

project(opencl-benchmarks-cli VERSION 0.0.1 LANGUAGES C)

include_directories("${CMAKE_SOURCE_DIR}/include"
                    "${PROJECT_SOURCE_DIR}/include")

add_executable(opencl-benchmarks "src/opencl-benchmarks.c")
target_link_libraries(opencl-benchmarks PRIVATE benchmarks)