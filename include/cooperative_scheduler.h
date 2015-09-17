#ifndef COOPERATIVE_SCHEDULER_H
#define COOPERATIVE_SCHEDULER_H

#include "typedefs.h"
#include <stdbool.h>

enum { NumberOfTasks = 10 };

typedef struct 
{
} CooperativeScheduler;

void CooperativeScheduler_Initialize(CooperativeScheduler* scheduler);
bool CooperativeScheduler_RegisterTask(CooperativeScheduler* scheduler,
                                       FatCallbackFunction taskMain,
                                       void* taskRaw,
                                       unsigned int priority);
void CooperativeScheduler_Run(CooperativeScheduler* scheduler);

#endif //COOPERATIVE_SCHEDULER_H
