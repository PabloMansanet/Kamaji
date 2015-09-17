#include "clock.tests.h"
#include "full_system.tests.h"
#include "timer_task.tests.h"
#include <stdio.h>

int main(void)
{
   // Clock tests
   TEST_elapsing_a_second_on_a_freshy_reset_clock();
   TEST_elapsing_a_minute_via_seconds();
   TEST_elapsing_an_hour_via_minutes();

   // Timer task tests
   TEST_registering_callback_on_the_timerTask_struct();
   TEST_registering_too_many_callbacks_returns_false();
   TEST_calling_TIMER_ISR_enough_times_queues_callback();
   TEST_calling_task_main_triggers_queued_callback_once();

   // System tests
   TEST_clock_is_updated_through_timer_interrupt();

   printf("All tests passed!\n");
}
