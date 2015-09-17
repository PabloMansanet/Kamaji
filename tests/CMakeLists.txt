include_directories(mocks)

add_executable(timer_task_tests timer_task.tests.c)
add_executable(clock_tests clock.tests.c)
add_executable(full_system_tests full_system.tests.c)

target_link_libraries(timer_task_tests timer_task timer_interrupt)
target_link_libraries(clock_tests clock)
target_link_libraries(full_system_tests timer_task timer_interrupt clock)
