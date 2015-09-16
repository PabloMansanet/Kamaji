cmake_minimum_required(VERSION 3.3)
project(blue_rtos)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_C_FLAGS "-g -Wall -Wextra -Werror -std=c11 -Wstrict-prototypes -Wmissing-prototypes -Wshadow -Wfloat-equal -O")

add_executable(tests scheduler.tests.c)
add_library(scheduler scheduler.c) 
add_library(timer_interrupt timer_interrupt.c)

target_link_libraries(tests scheduler timer_interrupt)
