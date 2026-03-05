#include "delay.h"
#include <stdint.h>

void setDelayTime(const uint32_t clockCyclesPerMillisecond){
	SysTick->LOAD = clockCyclesPerMillisecond - 1;
}

void resetSysTickCounter(){
	SysTick->VAL = 0;
}

void setClockSourceToProcessorClock(){
	SysTick->CTRL |= (1U << 2);
}

void enableSysTickCounter(){
	SysTick->CTRL |= (1U << 0);
}

void runSysTickDelay(const int delayDuration){
	const uint32_t sysTickTimerCountDownIsComplete = (1U << 16);

	for (int i = 0; i < delayDuration; ++i){
		//TODO: change hex value to bit shifted value
//		 while(!(SysTick->CTRL & 0x10000)){}
		while(!(SysTick->CTRL & sysTickTimerCountDownIsComplete)){}
	}
}

void resetSysTickCSRRegister(){
	SysTick->CTRL = 0;
}

//TODO: refactor both delays
void delayMicroSeconds(const int numberOfMicroSeconds){
	const uint32_t clockCyclesPerMillisecond = 16;

	setDelayTime(clockCyclesPerMillisecond);

	resetSysTickCounter();

	setClockSourceToProcessorClock();
	
	enableSysTickCounter();

	runSysTickDelay(numberOfMicroSeconds);
	
	resetSysTickCSRRegister();
}

void delayMilliSeconds(const int numberOfMilliSeconds){
	const uint32_t clockCyclesPerMillisecond = 16000;
	
	setDelayTime(clockCyclesPerMillisecond);

	resetSysTickCounter();

	setClockSourceToProcessorClock();

	enableSysTickCounter();

	runSysTickDelay(numberOfMilliSeconds);
	
	resetSysTickCSRRegister();
}
