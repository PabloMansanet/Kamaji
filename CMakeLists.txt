cmake_minimum_required(VERSION 3.3)
project(blue_rtos)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_C_FLAGS "-g -Wall -Wextra -Werror -std=c11 -Wstrict-prototypes -Wmissing-prototypes -Wshadow -Wfloat-equal -O")

add_subdirectory(src)
add_subdirectory(tests)

