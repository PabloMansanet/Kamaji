#ifndef TIMER_TASK_H
#define TIMER_TASK_H

#include "typedefs.h"
#include <stdbool.h>

enum { NumberOfCallbacks = 10 };

typedef struct  
{
   FatCallbackFunction callbacks[NumberOfCallbacks];
   void* callbackRawData[NumberOfCallbacks];
   
   unsigned int callbackPeriodsInMs[NumberOfCallbacks];
   bool callbackReady[NumberOfCallbacks];

   unsigned int numberOfRegisteredCallbacks;
   unsigned int elapsedMicroSeconds;
} TimerTask;

void Initialize(TimerTask* timerTask);
bool RegisterCallback(TimerTask* timerTask,
                      FatCallbackFunction callback,
                      void* callbackRawData,
                      unsigned int periodInMs);
void TaskMain(TimerTask* timerTask);

#endif //TIMER_TASK_H
