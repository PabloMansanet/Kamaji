#ifndef TIMER_INTERRUPT_H
#define TIMER_INTERRUPT_H

static void(*staticTimerCallback)() = 0;

void TIMER_ISR_SET_CALLBACK(void(*callback)())
{
   staticTimerCallback = callback;
}

void TIMER_ISR(void)
{
   if (staticTimerCallback) staticTimerCallback();
}

#endif //TIMER_INTERRUPT_H
