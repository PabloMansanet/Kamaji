include_directories(mocks)

add_executable(tests timer_task.tests.c)
target_link_libraries(tests timer_task timer_interrupt)
