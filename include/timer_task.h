#ifndef TIMER_TASK_H
#define TIMER_TASK_H

#include <stdbool.h>

typedef void (*CallbackFunction)(void);

enum { NumberOfCallbacks = 10 };

typedef struct  
{
   CallbackFunction callbacks[NumberOfCallbacks];
   unsigned int callbackPeriodsInMs[NumberOfCallbacks];
   unsigned int numberOfRegisteredCallbacks;
   unsigned int elapsedMicroSeconds;
} TimerTask;

void Initialize(TimerTask* timerTask);
bool RegisterCallback(TimerTask* timerTask,
                      CallbackFunction callback,
                      unsigned int periodInMs);


#endif //TIMER_TASK_H
