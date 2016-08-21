#ifndef __sys-tick__h
#define __sys-tick__h

#include "MKL46Z4.h"

void Init_Sys_Tick();
void SysTick_Handler();
//void delay_systick_us(unsigned int TicksIn_us);
//void delay_systick_ms(unsigned int TickIn_ms);
void delay_us(uint32_t TICK);

#endif


