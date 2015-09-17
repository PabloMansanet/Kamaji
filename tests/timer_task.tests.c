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

static void TestCallback(void) 
{
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
                       TestCallbackPeriodInMs);
   }

   // When
   bool registerResult = RegisterCallback(&testFixture->timerTask,
                                          &TestCallback,
                                          TestCallbackPeriodInMs);
   // Then
   assert(!registerResult); 

   FixtureTearDown();
}

static void TEST_calling_TIMER_ISR_enough_times_triggers_callback(void)
{
   FixtureSetUp();
   
   const unsigned int TestCallbackPeriodInMs = 1;
  
   // Given
   RegisterCallback(&testFixture->timerTask,
                    &TestCallback,
                    TestCallbackPeriodInMs);
   
   for (unsigned int i = 0; i < 999; i++) 
   {
      TIMER_ISR();      
   }
   assert(testFixture->testCallbackCounter == 0);

   // When
   TIMER_ISR();

   // Then
   assert(testFixture->testCallbackCounter == 1);

   FixtureTearDown();
}

int main(void) 
{
   TEST_registering_callback_on_the_timerTask_struct();
   TEST_registering_too_many_callbacks_returns_false();
   TEST_calling_TIMER_ISR_enough_times_triggers_callback();
   printf("All tests passed!\n");
}
