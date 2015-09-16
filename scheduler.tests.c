#include "scheduler.h"
#include "timer_interrupt.h"
#include "assert.h"
#include "stdlib.h"
#include "stdio.h"

/////////////////////////
// Mini test framework //
/////////////////////////
typedef struct 
{
   Scheduler scheduler; 
   unsigned int testCallbackCounter;
} TestFixture;

static TestFixture* testFixture = 0;

static void FixtureSetUp() 
{
   testFixture = (TestFixture*) malloc (sizeof(TestFixture));
   Initialize(&testFixture->scheduler);
   testFixture->testCallbackCounter = 0;
}

static void FixtureTearDown()
{
   if (testFixture) 
   {
      free(testFixture);
      testFixture = 0;
   }
}

//////////////////////////
//        Tests         //
//////////////////////////

static void TestCallback(void) 
{
   assert(testFixture);
   testFixture->testCallbackCounter++;
}

static void TEST_registering_callback_on_the_scheduler_struct(void)
{
   FixtureSetUp();

   //Given

   const unsigned int TestCallbackPeriodInMs = 1000;
   RegisterCallback(&testFixture->scheduler,
                    &TestCallback,
                    TestCallbackPeriodInMs);
   
   //Then
   assert(testFixture->scheduler.callbacks[0] == &TestCallback);
   assert(testFixture->scheduler.callbackPeriodsInMs[0] == TestCallbackPeriodInMs);
   assert(testFixture->scheduler.numberOfRegisteredCallbacks == 1);

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
      RegisterCallback(&testFixture->scheduler,
                       &TestCallback,
                       TestCallbackPeriodInMs);
   }

   // When
   bool registerResult = RegisterCallback(&testFixture->scheduler,
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
   RegisterCallback(&testFixture->scheduler,
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
   TEST_registering_callback_on_the_scheduler_struct();
   TEST_registering_too_many_callbacks_returns_false();
   TEST_calling_TIMER_ISR_enough_times_triggers_callback();
   printf("All tests passed!\n");
}
