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
   MockTask mockTaskLowPriority;
   MockTask mockTaskHighPriority;
} TestFixture;

static TestFixture* testFixture = 0;

static void FixtureSetUp(void) 
{
   testFixture = (TestFixture*) malloc (sizeof(TestFixture));
   MockTask_Initialize(&testFixture->mockTaskHighPriority);
   MockTask_Initialize(&testFixture->mockTaskLowPriority);
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
