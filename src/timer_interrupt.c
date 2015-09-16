#include "timer_interrupt.h"
#include <assert.h>

static void NullFunction( void* data ) { (void)data; }

static FatCallbackFunction timerIsrCallback = NullFunction;

static void* timerIsrCallbackData = 0;

void TIMER_ISR_SET_CALLBACK(FatCallbackFunction callback,
                            void* callbackData)
{
   assert(callback);

   timerIsrCallback = callback;
   timerIsrCallbackData = callbackData;
}

void TIMER_ISR(void)
{
   timerIsrCallback(timerIsrCallbackData);
}
