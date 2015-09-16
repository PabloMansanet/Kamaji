#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>

typedef void (*CallbackFunction)(void);

enum { NumberOfCallbacks = 10 };

typedef struct  
{
   CallbackFunction callbacks[NumberOfCallbacks];
   unsigned int callbackPeriodsInMs[NumberOfCallbacks];
   unsigned int numberOfRegisteredCallbacks;
   unsigned int elapsedMicroSeconds;
} Scheduler;

void Initialize(Scheduler* scheduler);
bool RegisterCallback(Scheduler* scheduler,
                      CallbackFunction callback,
                      unsigned int periodInMs);


#endif //SCHEDULER_H
