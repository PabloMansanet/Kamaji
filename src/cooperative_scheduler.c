#include "cooperative_scheduler.h"
#include <assert.h>

void CooperativeScheduler_Initialize(CooperativeScheduler* scheduler)
{
   assert(scheduler);
   scheduler->numberOfRegisteredTasks = 0;
   scheduler->taskToRunNextIndex = 0;
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
   const unsigned int taskIndex = scheduler->taskToRunNextIndex;
   scheduler->taskMain[taskIndex](scheduler->taskRaw[taskIndex]);

   const unsigned int taskToRunNextIndex = taskIndex + 1 < scheduler->numberOfRegisteredTasks ?
                                           taskIndex + 1 :
                                           0;
   scheduler->taskToRunNextIndex = taskToRunNextIndex;
}

