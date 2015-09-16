#include "scheduler.h"
#include "timer_interrupt.h"
#include <assert.h>
#include <stddef.h>

static void TriggerCallbacks(Scheduler* scheduler)
{
   const unsigned int elapsedMilliSeconds = scheduler->elapsedMicroSeconds / 1000;
   for (size_t i = 0; i < scheduler->numberOfRegisteredCallbacks; i++)
   {
      if (elapsedMilliSeconds % scheduler->callbackPeriodsInMs[i] == 0)
      {
         scheduler->callbacks[i]();
      }
   }
}

static void SchedulerCallback(void* raw)
{
   assert(raw);

   Scheduler* scheduler = (Scheduler*)raw;
   const unsigned int before = scheduler->elapsedMicroSeconds / 1000;
   scheduler->elapsedMicroSeconds += timerPeriodMicroSeconds;
   const unsigned int after = scheduler->elapsedMicroSeconds / 1000;
   
   if (before != after)
      TriggerCallbacks(scheduler);
}


void Initialize(Scheduler* scheduler)
{
   assert(scheduler);

   scheduler->numberOfRegisteredCallbacks = 0; 
   scheduler->elapsedMicroSeconds = 0;

   TIMER_ISR_SET_CALLBACK(SchedulerCallback, scheduler);
}

bool RegisterCallback(Scheduler* scheduler,
                      CallbackFunction callback,
                      unsigned int periodInMs)
{
   assert(scheduler);

   const unsigned int callbackIndex = scheduler->numberOfRegisteredCallbacks;

   if (callbackIndex >= NumberOfCallbacks)
      return false;

   if (periodInMs == 0)
      return false;

   scheduler->callbacks[callbackIndex] = callback;
   scheduler->callbackPeriodsInMs[callbackIndex] = periodInMs;
   scheduler->numberOfRegisteredCallbacks++;
   return true;
}

