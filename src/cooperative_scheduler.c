#include "cooperative_scheduler.h"


void CooperativeScheduler_Initialize(CooperativeScheduler* scheduler)
{
   (void) scheduler;
}

bool CooperativeScheduler_RegisterTask(CooperativeScheduler* scheduler,
                                       FatCallbackFunction taskMain,
                                       void* taskRaw,
                                       unsigned int priority)
{
   (void) scheduler;
   (void) taskMain;
   (void) taskRaw;
   (void) priority;
   return false;
}

void CooperativeScheduler_Run(CooperativeScheduler* scheduler)
{
   (void) scheduler;
}

