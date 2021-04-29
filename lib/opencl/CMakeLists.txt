cmake_minimum_required(VERSION 3.14)

project(opencl VERSION 0.0.1 LANGUAGES C)

find_package(OpenCL REQUIRED)

include_directories("${OpenCL_INCLUDE_DIR}"
                    "${CMAKE_SOURCE_DIR}/include"
                    "${PROJECT_SOURCE_DIR}/include")

add_library(opencl STATIC "src/device.c"
                          "src/error.c"
                          "src/release.c")
target_link_libraries(opencl PRIVATE OpenCL::OpenCL ${OpenCL_LIBRARIES})