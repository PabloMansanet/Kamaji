#ifndef CLOCK_H
#define CLOCK_H

typedef struct
{
   unsigned int hours;
   unsigned int minutes;
   unsigned int seconds;
} Clock;

void ElapseSecondCallback(void* raw);

void ElapseSecond(Clock* clock);
void ElapseMinute(Clock* clock);
void ElapseHour(Clock* clock);

void ResetToMidnight(Clock* clock);

#endif //CLOCK_H
