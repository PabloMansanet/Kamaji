add_library(scheduler_test SHARED tests.scheduler.cpp)
add_executable(run_unit_tests main.cpp)

add_test(NAME trivial_test COMMAND run_unit_tests) 
target_link_libraries(run_unit_tests gtest gtest_main scheduler_test)

