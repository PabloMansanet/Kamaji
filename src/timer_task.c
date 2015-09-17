#include "timer_task.h"
#include "timer_interrupt.h"
#include <assert.h>
#include <stddef.h>

static void TriggerCallbacks(TimerTask* timerTask)
{
   for (size_t i = 0; i < timerTask->numberOfRegisteredCallbacks; i++)
   {
      if (timerTask->callbackReady[i])
      {
         timerTask->callbacks[i](timerTask->callbackRawData[i]);
         timerTask->callbackReady[i] = false;
      }
   }
}

void TimerTask_TaskMain(void* timerTaskRaw)
{
   assert(timerTaskRaw);
   TimerTask* timerTask = (TimerTask*)timerTaskRaw;
   TriggerCallbacks(timerTask);
}

static void QueueCallbacks(TimerTask* timerTask)
{
   const unsigned int elapsedMilliSeconds = timerTask->elapsedMicroSeconds / 1000;
   for (size_t i = 0; i < timerTask->numberOfRegisteredCallbacks; i++)
   {
      if (elapsedMilliSeconds % timerTask->callbackPeriodsInMs[i] == 0)
      {
         timerTask->callbackReady[i] = true;
      }
   }
}

static void TimerTaskCallback(void* raw)
{
   assert(raw);

   TimerTask* timerTask = (TimerTask*)raw;
   const unsigned int before = timerTask->elapsedMicroSeconds / 1000;
   timerTask->elapsedMicroSeconds += timerPeriodMicroSeconds;
   const unsigned int after = timerTask->elapsedMicroSeconds / 1000;
   
   if (before != after)
      QueueCallbacks(timerTask);
}

void TimerTask_Initialize(TimerTask* timerTask)
{
   assert(timerTask);

   timerTask->numberOfRegisteredCallbacks = 0; 
   timerTask->elapsedMicroSeconds = 0;

   TIMER_ISR_SET_CALLBACK(TimerTaskCallback, timerTask);
}

bool TimerTask_RegisterCallback(TimerTask* timerTask,
                                FatCallbackFunction callback,
                                void* callbackRawData,
                                unsigned int periodInMs)
{
   assert(timerTask);

   const unsigned int callbackIndex = timerTask->numberOfRegisteredCallbacks;

   if (callbackIndex >= NumberOfCallbacks)
      return false;

   if (periodInMs == 0)
      return false;

   timerTask->callbacks[callbackIndex] = callback;
   timerTask->callbackPeriodsInMs[callbackIndex] = periodInMs;
   timerTask->callbackReady[callbackIndex] = false;
   timerTask->callbackRawData[callbackIndex] = callbackRawData;
   timerTask->numberOfRegisteredCallbacks++;
   return true;
}

