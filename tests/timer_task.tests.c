#include "timer_task.h"
#include "timer_interrupt.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/////////////////////////
// Mini test framework //
/////////////////////////
typedef struct 
{
   TimerTask timerTask; 
   unsigned int testCallbackCounter;
} TestFixture;

static TestFixture* testFixture = 0;

static void FixtureSetUp(void) 
{
   testFixture = (TestFixture*) malloc (sizeof(TestFixture));
   Initialize(&testFixture->timerTask);
   testFixture->testCallbackCounter = 0;
}

static void FixtureTearDown(void)
{
   free(testFixture);
   testFixture = 0;
}

//////////////////////////
//        Tests         //
//////////////////////////

static void TestCallback(void* raw) 
{
   (void)raw;
   assert(testFixture);
   testFixture->testCallbackCounter++;
}

static void TEST_registering_callback_on_the_timerTask_struct(void)
{
   FixtureSetUp();

   //Given
   const unsigned int TestCallbackPeriodInMs = 1000;
   RegisterCallback(&testFixture->timerTask,
                    &TestCallback,
                    NULL,
                    TestCallbackPeriodInMs);
   
   //Then
   assert(testFixture->timerTask.callbacks[0] == &TestCallback);
   assert(testFixture->timerTask.callbackPeriodsInMs[0] == TestCallbackPeriodInMs);
   assert(testFixture->timerTask.numberOfRegisteredCallbacks == 1);

   FixtureTearDown();
}

static void TEST_registering_too_many_callbacks_returns_false(void)
{
   FixtureSetUp();

   // Given 
   const unsigned int TestCallbackPeriodInMs = 1000;

   for (int callbackIndex = 0;
        callbackIndex != NumberOfCallbacks;
        callbackIndex++)
   {
      RegisterCallback(&testFixture->timerTask,
                       &TestCallback,
                       NULL,
                       TestCallbackPeriodInMs);
   }

   // When
   bool registerResult = RegisterCallback(&testFixture->timerTask,
                                          &TestCallback,
                                          NULL,
                                          TestCallbackPeriodInMs);
   // Then
   assert(!registerResult); 

   FixtureTearDown();
}

static void TEST_calling_TIMER_ISR_enough_times_queues_callback(void)
{
   FixtureSetUp();
   
   const unsigned int TestCallbackPeriodInMs = 1;
  
   // Given
   RegisterCallback(&testFixture->timerTask,
                    &TestCallback,
                    NULL,
                    TestCallbackPeriodInMs);
   
   for (unsigned int i = 0; i < 999; i++) 
   {
      TIMER_ISR();      
   }
   assert(testFixture->timerTask.callbackReady[0] == false);

   // When
   TIMER_ISR();

   // Then
   assert(testFixture->timerTask.callbackReady[0] == true);

   FixtureTearDown();
}

static void TEST_calling_task_main_triggers_queued_callback_once(void)
{
   FixtureSetUp();
   
   const unsigned int TestCallbackPeriodInMs = 1;

   // Given
   RegisterCallback(&testFixture->timerTask,
                    &TestCallback,
                    NULL,
                    TestCallbackPeriodInMs);
   testFixture->timerTask.callbackReady[0] = true;
   assert(testFixture->testCallbackCounter == 0);

   // When
   TaskMain(&testFixture->timerTask);

   // Then
   assert(testFixture->testCallbackCounter == 1);
   assert(testFixture->timerTask.callbackReady[0] == false);

   FixtureTearDown();
}

int main(void) 
{
   TEST_registering_callback_on_the_timerTask_struct();
   TEST_registering_too_many_callbacks_returns_false();
   TEST_calling_TIMER_ISR_enough_times_queues_callback();
   TEST_calling_task_main_triggers_queued_callback_once();
   printf("All tests passed!\n");
}
