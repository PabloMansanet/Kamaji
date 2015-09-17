#include "clock.h"
#include <assert.h>

void Clock_ElapseSecondCallback(void* raw)
{
   assert(raw);
   Clock* clock = (Clock*) raw;
   Clock_ElapseSecond(clock);
}

void Clock_ElapseHour(Clock* clock)
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

void Clock_ElapseMinute(Clock* clock)
{
   assert(clock);
   if (clock->minutes < 59)
   {
      clock->minutes++;
   }
   else
   {
      clock->minutes = 0;
      Clock_ElapseHour(clock);
   }
}

void Clock_ElapseSecond(Clock* clock)
{
   assert(clock);

   if (clock->seconds < 59)
   {
      clock->seconds++;
   }
   else
   {
      clock->seconds = 0;
      Clock_ElapseMinute(clock);
   }
}

void Clock_ResetToMidnight(Clock* clock)
{
   assert(clock);
   clock->seconds = 0;
   clock->minutes = 0;
   clock->hours = 0;
}
