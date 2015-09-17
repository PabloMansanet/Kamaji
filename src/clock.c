#include "clock.h"
#include <assert.h>

void ElapseSecondCallback(void* raw)
{
   assert(raw);
   Clock* clock = (Clock*) raw;
   ElapseSecond(clock);
}

void ElapseHour(Clock* clock)
{
   assert(clock);
   if (clock->hours < 23)
   {
      clock->hours++;
   }
   else
   {
      clock->hours = 0;
   }
}

void ElapseMinute(Clock* clock)
{
   assert(clock);
   if (clock->minutes < 59)
   {
      clock->minutes++;
   }
   else
   {
      clock->minutes = 0;
      ElapseHour(clock);
   }
}

void ElapseSecond(Clock* clock)
{
   assert(clock);

   if (clock->seconds < 59)
   {
      clock->seconds++;
   }
   else
   {
      clock->seconds = 0;
      ElapseMinute(clock);
   }
}

void ResetToMidnight(Clock* clock)
{
   assert(clock);
   clock->seconds = 0;
   clock->minutes = 0;
   clock->hours = 0;
}
