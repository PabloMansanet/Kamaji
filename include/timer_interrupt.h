#ifndef TIMER_INTERRUPT_H
#define TIMER_INTERRUPT_H

#include "typedefs.h"

enum { timerPeriodMicroSeconds = 1 };

void TIMER_ISR(void);
void TIMER_ISR_SET_CALLBACK(FatCallbackFunction callback,
                                   void* callbackData);


#endif //TIMER_INTERRUPT_H
