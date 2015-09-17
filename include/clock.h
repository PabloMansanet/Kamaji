#ifndef CLOCK_H
#define CLOCK_H

typedef struct
{
   unsigned int hours;
   unsigned int minutes;
   unsigned int seconds;
} Clock;

void Clock_ElapseSecondCallback(void* raw);

void Clock_ElapseSecond(Clock* clock);
void Clock_ElapseMinute(Clock* clock);
void Clock_ElapseHour(Clock* clock);

void Clock_ResetToMidnight(Clock* clock);

#endif //CLOCK_H
