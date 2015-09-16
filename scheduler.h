#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>

static const unsigned int NUMBER_OF_CALLBACKS = 10;
typedef void (*CallbackFunction)();

typedef struct  
{
   CallbackFunction callbacks[NUMBER_OF_CALLBACKS];
   unsigned int callbackPeriodsInMs[NUMBER_OF_CALLBACKS];
   unsigned int numberOfRegisteredCallbacks;
} Scheduler;

void Initialize(Scheduler* scheduler);
bool RegisterCallback(Scheduler* scheduler,
                      const CallbackFunction callback,
                      unsigned int periodInMs);

// to be called periodically by the hardware timer interrupt.
void TickScheduler(Scheduler*, unsigned int microseconds); 


#endif //SCHEDULER_H
