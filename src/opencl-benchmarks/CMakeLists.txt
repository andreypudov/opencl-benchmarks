cmake_minimum_required(VERSION 3.14)

project(opencl-benchmarks-cli VERSION 0.0.1 LANGUAGES CXX)

find_package(OpenCL REQUIRED)

include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG master)
FetchContent_Declare(googlebenchmark GIT_REPOSITORY https://github.com/google/benchmark.git GIT_TAG master)
FetchContent_MakeAvailable(googletest googlebenchmark)

include_directories("${OpenCL_INCLUDE_DIR}"
                    "${CMAKE_SOURCE_DIR}/include"
                    "${CMAKE_SOURCE_DIR}/lib/benchmarks/include"
                    "${CMAKE_SOURCE_DIR}/lib/opencl/include"
                    "${PROJECT_SOURCE_DIR}/include")

add_executable(opencl-benchmarks "src/opencl-benchmarks.cc"
                                 "src/vecmul/cpu_vecmul.cc"
                                 "src/vecmul/ocl_vecmul.cc")
target_link_libraries(opencl-benchmarks PRIVATE OpenCL::OpenCL benchmark::benchmark opencl benchmarks)