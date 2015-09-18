#ifndef COOPERATIVE_SCHEDULER_H
#define COOPERATIVE_SCHEDULER_H

#include "typedefs.h"
#include <stdbool.h>

enum { NumberOfTasks = 10 };

typedef enum
{
   Awake,
   Asleep
} TaskState;

typedef struct 
{
   FatCallbackFunction taskMain[NumberOfTasks];
   void* taskRaw[NumberOfTasks];
   unsigned int priority[NumberOfTasks];
   TaskState taskState[NumberOfTasks];

   unsigned int numberOfRegisteredTasks;
   unsigned int taskToRunNextIndex;
} CooperativeScheduler;

void CooperativeScheduler_Initialize(CooperativeScheduler* scheduler);
bool CooperativeScheduler_RegisterTask(CooperativeScheduler* scheduler,
                                       FatCallbackFunction taskMain,
                                       void* taskRaw,
                                       unsigned int priority);
void CooperativeScheduler_Run(CooperativeScheduler* scheduler);
bool CooperativeScheduler_TaskSleep(CooperativeScheduler* scheduler,
                                    void* taskRaw);
bool CooperativeScheduler_TaskWakeUp(CooperativeScheduler* scheduler,
                                     void* taskRaw);

#endif //COOPERATIVE_SCHEDULER_H
