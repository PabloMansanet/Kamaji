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
   MockTask mockTaskLowPriorityA;
   MockTask mockTaskLowPriorityB;
   MockTask mockTaskHighPriority;
} TestFixture;

static TestFixture* testFixture = 0;

static void FixtureSetUp(void) 
{
   testFixture = (TestFixture*) malloc (sizeof(TestFixture));
   MockTask_Initialize(&testFixture->mockTaskLowPriorityA);
   MockTask_Initialize(&testFixture->mockTaskLowPriorityB);
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

void TEST_running_scheduler_with_a_single_task(void)
{
   FixtureSetUp();

   // Given
   CooperativeScheduler_RegisterTask(&testFixture->scheduler,
                                     MockTask_TaskMain,
                                     &testFixture->mockTaskHighPriority,
                                     HighPriority);
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
   CooperativeScheduler_RegisterTask(&testFixture->scheduler,
                                     MockTask_TaskMain,
                                     &testFixture->mockTaskLowPriorityA,
                                     LowPriority);
   CooperativeScheduler_RegisterTask(&testFixture->scheduler,
                                     MockTask_TaskMain,
                                     &testFixture->mockTaskLowPriorityB,
                                     LowPriority);

   // When
   CooperativeScheduler_Run(&testFixture->scheduler);

   // Then
   assert(testFixture->mockTaskLowPriorityA.timesTaskMainCalled == 1);
   assert(testFixture->mockTaskLowPriorityB.timesTaskMainCalled == 0);
   
   // When
   CooperativeScheduler_Run(&testFixture->scheduler);

   // Then
   assert(testFixture->mockTaskLowPriorityA.timesTaskMainCalled == 1);
   assert(testFixture->mockTaskLowPriorityB.timesTaskMainCalled == 1);

   // When
   CooperativeScheduler_Run(&testFixture->scheduler);

   // Then
   assert(testFixture->mockTaskLowPriorityA.timesTaskMainCalled == 2);
   assert(testFixture->mockTaskLowPriorityB.timesTaskMainCalled == 1);


   FixtureTearDown();
}
