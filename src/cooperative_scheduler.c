#include "cooperative_scheduler.h"
#include <assert.h>

void CooperativeScheduler_Initialize(CooperativeScheduler* scheduler)
{
   assert(scheduler);
   scheduler->numberOfRegisteredTasks = 0;
}

bool CooperativeScheduler_RegisterTask(CooperativeScheduler* scheduler,
                                       FatCallbackFunction taskMain,
                                       void* taskRaw,
                                       unsigned int priority)
{
   assert(scheduler); 
   unsigned int taskIndex = scheduler->numberOfRegisteredTasks;
   
   if (taskIndex >= NumberOfTasks)
      return false;

   scheduler->taskMain[taskIndex] = taskMain;
   scheduler->taskRaw[taskIndex] = taskRaw;
   scheduler->priority[taskIndex] = priority;
   scheduler->numberOfRegisteredTasks++;

   return true;
}

void CooperativeScheduler_Run(CooperativeScheduler* scheduler)
{
   for (unsigned int taskIndex = 0;
        taskIndex < scheduler->numberOfRegisteredTasks;
        taskIndex++)
   {
      scheduler->taskMain[taskIndex](scheduler->taskRaw[taskIndex]);
   }
}

