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
