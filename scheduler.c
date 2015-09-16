#include "scheduler.h"
#include "assert.h"

void Initialize(Scheduler* scheduler)
{
   assert(scheduler);

   for (int callbackIndex = 0;
        callbackIndex != NUMBER_OF_CALLBACKS;
        callbackIndex++)
   {
      scheduler->callbacks[callbackIndex] = 0;
   }
   scheduler->numberOfRegisteredCallbacks = 0; 
}

bool RegisterCallback(Scheduler* scheduler,
                      const CallbackFunction callback,
                      unsigned int periodInMs)
{
   const unsigned int callbackIndex = scheduler->numberOfRegisteredCallbacks;
   if (callbackIndex >= NUMBER_OF_CALLBACKS)
      return false;

   scheduler->callbacks[callbackIndex] = callback;
   scheduler->callbackPeriodsInMs[callbackIndex] = periodInMs;
   scheduler->numberOfRegisteredCallbacks++;
   return true;
}


