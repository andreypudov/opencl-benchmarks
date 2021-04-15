cmake_minimum_required(VERSION 3.14)

project(opencl-benchmarks VERSION 0.0.1 LANGUAGES CXX)

unset(CMAKE_CXX_CPPCHECK)
unset(CMAKE_CXX_CLANG_TIDY)
unset(CMAKE_CXX_CPPLINT)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories(SYSTEM "${gtest_SOURCE_DIR}/include")
endif()

add_subdirectory("lib/benchmarks")

find_program(VALGRIND "valgrind")
if(VALGRIND)
  add_custom_target(valgrind
    COMMAND "${VALGRIND}" --tool=memcheck
                          --leak-check=yes
                          --show-reachable=yes
                          --num-callers=20
                          --track-origins=yes
                          --track-fds=yes
                          --error-limit=no
                          --suppressions="${CMAKE_SOURCE_DIR}/.valgrind"
                          $<TARGET_FILE:opencl-benchmarks-test>)
endif()