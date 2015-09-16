#include "scheduler.h"
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

static void TestCallback() 
{
   assert(testFixture);
   testFixture->testCallbackCounter++;
}

static void TEST_registering_callback_on_the_scheduler_struct()
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

int main(void) 
{
   TEST_registering_callback_on_the_scheduler_struct();
   printf("All tests passed!\n");
}
