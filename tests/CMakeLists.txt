include_directories(mocks)

add_library(timer_task_tests timer_task.tests.c)
add_library(clock_tests clock.tests.c)
add_library(full_system_tests full_system.tests.c)
add_library(cooperative_scheduler_tests cooperative_scheduler.tests.c)

target_link_libraries(timer_task_tests timer_task timer_interrupt)
target_link_libraries(clock_tests clock)
target_link_libraries(full_system_tests timer_task timer_interrupt clock)
target_link_libraries(cooperative_scheduler_tests cooperative_scheduler)

add_executable(tests main.c)
target_link_libraries(tests timer_task_tests 
                            clock_tests 
                            full_system_tests
                            cooperative_scheduler_tests)
