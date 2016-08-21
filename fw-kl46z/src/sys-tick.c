#include "sys-tick.h"

int DelayTimerTick; //variable delaytimertick

void Init_Sys_Tick()
{
	//SysTick->LOAD = SystemCoreClock * 5 / 1000;	
	SysTick->LOAD = SystemCoreClock/1000000;	
	SysTick->VAL = 0;	//reset the current value.
  //Select Core Clock & Enable SysTick & Disable Interrupt 
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
}

void delay_us(uint32_t TICK)
{
uint32_t tmp = TICK;
    while (tmp)
    {
        tmp = tmp - 1;
        /* Wait until SysTick counts down to 0 */
        while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
        {
            /* Dump read to clear SysTick Flag */
            //(uint32_t)SysTick->CTRL;
        }
				    /* Dump read to clear SysTick Flag */
           (uint32_t)SysTick->CTRL;
    }	
}

//void SysTick_Handler()
//{
//	if (DelayTimerTick < 0xFFFFFFFF)
//		DelayTimerTick++;
//}

//void delay_systick_us(unsigned int TicksIn_us)
//{
//	DelayTimerTick=0;
//	while(DelayTimerTick < TicksIn_us);
//}

//void delay_systick_ms(unsigned int TickIn_ms)
//{	
//	delay_systick_us(1000*TickIn_ms);
//}

