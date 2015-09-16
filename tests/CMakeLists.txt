add_executable(tests scheduler.tests.c)

target_link_libraries(tests scheduler timer_interrupt)
