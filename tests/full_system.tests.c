#include "timer_task.h"
#include "timer_interrupt.h"
#include "clock.h"
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
   Clock clock;
} TestFixture;

static TestFixture* testFixture = 0;

static void FixtureSetUp(void) 
{
   testFixture = (TestFixture*) malloc (sizeof(TestFixture));
   TimerTask_Initialize(&testFixture->timerTask);
   Clock_ResetToMidnight(&testFixture->clock);
}

static void FixtureTearDown(void)
{
   free(testFixture);
   testFixture = 0;
}

//////////////////////////
//        Tests         //
//////////////////////////

static void TEST_clock_is_updated_through_timer_interrupt(void)
{
   FixtureSetUp();

   // Given
   const unsigned int OneSecondInMS = 1000;
   const unsigned int OneSecondInMicroSeconds = 1000000;
   TimerTask_RegisterCallback(&testFixture->timerTask,
                    Clock_ElapseSecondCallback,
                    &testFixture->clock,
                    OneSecondInMS);
                    
   assert(testFixture->clock.seconds == 0);

   // When (simulated MAIN loop)
   for (unsigned int i = 0; i < OneSecondInMicroSeconds; i++)
   {
      TIMER_ISR();
      TimerTask_TaskMain(&testFixture->timerTask);
   }

   // Then
   assert(testFixture->clock.seconds == 1);

   FixtureTearDown();
}

int main(void)
{
   TEST_clock_is_updated_through_timer_interrupt();
   printf("All system tests passed!\n");
}
