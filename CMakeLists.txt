cmake_minimum_required(VERSION 3.3)
project(Kamaji)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-g -Wall")

#TESTING FRAMEWORK
option(test "Build all tests." OFF)

if (test)
   add_subdirectory(lib/gtest-1.7.0)
   enable_testing()
   include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
   add_subdirectory(test)
endif()
