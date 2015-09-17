#ifndef MOCK_TASK_H
#define MOCK_TASK_H

#include <assert.h>

typedef struct
{
   unsigned int timesTaskMainCalled;
} MockTask;

static inline void MockTask_Initialize(MockTask* mockTask)
{
   mockTask->timesTaskMainCalled = 0;
}

static inline void MockTask_TaskMain(void* mockTaskRaw)
{
   assert (mockTaskRaw);
   MockTask* mockTask = (MockTask*) mockTaskRaw;

   mockTask->timesTaskMainCalled++;
}

#endif
