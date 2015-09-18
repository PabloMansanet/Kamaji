#include "mock.task.h"
#include "cooperative_scheduler.h"
#include "cooperative_scheduler.tests.h"

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

enum 
{ 
   LowPriority = 1,
   HighPriority = 2
};

/////////////////////////
// Mini test framework //
/////////////////////////
typedef struct 
{
   CooperativeScheduler scheduler; 
   MockTask alpha_mockTaskLowPriority;
   MockTask beta_mockTaskLowPriority;
   MockTask mockTaskHighPriority;
} TestFixture;

static TestFixture* testFixture = 0;

static void FixtureSetUp(void) 
{
   testFixture = (TestFixture*) malloc (sizeof(TestFixture));
   MockTask_Initialize(&testFixture->alpha_mockTaskLowPriority);
   MockTask_Initialize(&testFixture->beta_mockTaskLowPriority);
   MockTask_Initialize(&testFixture->mockTaskHighPriority);
   CooperativeScheduler_Initialize(&testFixture->scheduler);
}

static void FixtureTearDown(void)
{
   free(testFixture);
   testFixture = 0;
}

//////////////////////////
//        Tests         //
//////////////////////////

static void HELPER_register_two_low_priority_tasks(void)
{
   CooperativeScheduler_RegisterTask(&testFixture->scheduler,
                                     MockTask_TaskMain,
                                     &testFixture->alpha_mockTaskLowPriority,
                                     LowPriority);
   CooperativeScheduler_RegisterTask(&testFixture->scheduler,
                                     MockTask_TaskMain,
                                     &testFixture->beta_mockTaskLowPriority,
                                     LowPriority);
}

static void HELPER_register_one_high_priority_task(void)
{

   CooperativeScheduler_RegisterTask(&testFixture->scheduler,
                                     MockTask_TaskMain,
                                     &testFixture->mockTaskHighPriority,
                                     HighPriority);
}

void TEST_running_scheduler_with_a_single_task(void)
{
   FixtureSetUp();

   // Given
   HELPER_register_one_high_priority_task();
   assert(testFixture->mockTaskHighPriority.timesTaskMainCalled == 0);

   // When
   CooperativeScheduler_Run(&testFixture->scheduler);

   // Then 
   assert(testFixture->mockTaskHighPriority.timesTaskMainCalled == 1);

   FixtureTearDown();
}

void TEST_running_scheduler_with_two_same_priority_tasks_cycles_calls(void)
{
   FixtureSetUp();
   
   // Given
   HELPER_register_two_low_priority_tasks();

   // When
   CooperativeScheduler_Run(&testFixture->scheduler);

   // Then
   assert(testFixture->alpha_mockTaskLowPriority.timesTaskMainCalled == 1);
   assert(testFixture->beta_mockTaskLowPriority.timesTaskMainCalled == 0);
   
   // When
   CooperativeScheduler_Run(&testFixture->scheduler);

   // Then
   assert(testFixture->alpha_mockTaskLowPriority.timesTaskMainCalled == 1);
   assert(testFixture->beta_mockTaskLowPriority.timesTaskMainCalled == 1);

   // When
   CooperativeScheduler_Run(&testFixture->scheduler);

   // Then
   assert(testFixture->alpha_mockTaskLowPriority.timesTaskMainCalled == 2);
   assert(testFixture->beta_mockTaskLowPriority.timesTaskMainCalled == 1);

   FixtureTearDown();
}

void TEST_putting_task_to_sleep_stops_it_from_being_scheduled(void)
{
   FixtureSetUp();

   // Given
   HELPER_register_two_low_priority_tasks();

   // When
   CooperativeScheduler_TaskSleep(&testFixture->scheduler,
                                  &testFixture->alpha_mockTaskLowPriority);

   // Then
   CooperativeScheduler_Run(&testFixture->scheduler);
   assert(testFixture->alpha_mockTaskLowPriority.timesTaskMainCalled == 0);
   assert(testFixture->beta_mockTaskLowPriority.timesTaskMainCalled == 1);

   CooperativeScheduler_Run(&testFixture->scheduler);
   assert(testFixture->alpha_mockTaskLowPriority.timesTaskMainCalled == 0);
   assert(testFixture->beta_mockTaskLowPriority.timesTaskMainCalled == 2);

   FixtureTearDown();
}

void TEST_waking_task_up_after_sleep_puts_it_back_on_schedule(void)
{
   FixtureSetUp();

   // Given
   HELPER_register_one_high_priority_task();
   CooperativeScheduler_TaskSleep(&testFixture->scheduler,
                                  &testFixture->mockTaskHighPriority);
   CooperativeScheduler_Run(&testFixture->scheduler);
   assert(testFixture->mockTaskHighPriority.timesTaskMainCalled == 0);

   // When
   CooperativeScheduler_TaskWakeUp(&testFixture->scheduler,
                                   &testFixture->mockTaskHighPriority);
   CooperativeScheduler_Run(&testFixture->scheduler);

   // Then
   assert(testFixture->mockTaskHighPriority.timesTaskMainCalled == 1);

   FixtureTearDown();
}
