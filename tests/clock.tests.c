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
   Clock clock; 
} TestFixture;

static TestFixture* testFixture = 0;

static void FixtureSetUp(void) 
{
   testFixture = (TestFixture*) malloc (sizeof(TestFixture));
   ResetToMidnight(&testFixture->clock);
}

static void FixtureTearDown(void)
{
   free(testFixture);
   testFixture = 0;
}

//////////////////////////
//        Tests         //
//////////////////////////

static void TEST_elapsing_a_second_on_a_freshy_reset_clock(void) 
{
   FixtureSetUp();
  
   // Given
   assert(testFixture->clock.hours == 0);
   assert(testFixture->clock.minutes == 0);
   assert(testFixture->clock.seconds == 0);

   // When
   ElapseSecond(&testFixture->clock);
  
   // Then
   assert(testFixture->clock.seconds == 1);

   FixtureTearDown();
}

static void TEST_elapsing_a_minute_via_seconds(void)
{
   FixtureSetUp();

   // Given
   for (int i = 0; i < 59; i++) 
   {
      ElapseSecond(&testFixture->clock);
   }
   assert(testFixture->clock.seconds == 59);
   assert(testFixture->clock.minutes == 0);

   // When
   ElapseSecond(&testFixture->clock);

   // Then
   assert(testFixture->clock.seconds == 0);
   assert(testFixture->clock.minutes == 1);

   FixtureTearDown();
}

static void TEST_elapsing_an_hour_via_minutes(void)
{
   FixtureSetUp();
  
   // Given
   for (int i = 0; i < 59; i++) 
   {
      ElapseMinute(&testFixture->clock);
   }
   assert(testFixture->clock.minutes == 59);
   assert(testFixture->clock.hours == 0);

   // When
   ElapseMinute(&testFixture->clock);

   // Then
   assert(testFixture->clock.minutes == 0);
   assert(testFixture->clock.hours == 1);

   FixtureTearDown();
}


int main(void) 
{
   TEST_elapsing_a_second_on_a_freshy_reset_clock();
   TEST_elapsing_a_minute_via_seconds();
   TEST_elapsing_an_hour_via_minutes();
   printf("All tests passed!\n");
}
