#include <stdint.h>
#include "stm32f4xx.h"                  // Device header
//#include "stm32f7xx.h"                  // Device header

#ifndef __delay__H__
#define __delay__H__

//TODO: Change Names 
//TODO: Remove unnecessary function declarations
void delayuS(const int numberOfMicroSeconds);
void delay(const int numberOfMilliseconds);
void setDelayTime(const uint32_t clockCyclesPerMillisecond);
void resetSysTickCounter();
void setClockSourceToProcessorClock();
void enableSysTickCounter();
void runSysTickDelay(const int delayDuration);
void resetSysTickCSRRegister();

#endif

