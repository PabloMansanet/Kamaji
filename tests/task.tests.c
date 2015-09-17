#include "scheduler.h"
#include "time_task.h"


/////////////////////////
// Mini test framework //
/////////////////////////
typedef struct 
{
   Scheduler scheduler; 
   ClockTime clockTime;
} TestFixture;

static TestFixture* testFixture = 0;

static void FixtureSetUp(void) 
{
   testFixture = (TestFixture*) malloc (sizeof(TestFixture));
   Initialize(&testFixture->scheduler);

   testFixture->clockTime.hours = 0;
   testFixture->clockTime.minutes = 0;
   testFixture->clockTime.seconds = 0;
}

static void FixtureTearDown(void)
{
   free(testFixture);
   testFixture = 0;
}

//////////////////////////
//        Tests         //
//////////////////////////


