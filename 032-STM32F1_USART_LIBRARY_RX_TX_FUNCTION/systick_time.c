#include "stm32f10x.h" 
#include "systick_time.h"

void systick_init(void)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL |= 5;
}

void DelayMillis(void)
{
	SysTick->LOAD = 0x11940;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
}

void DelayMs(unsigned long t)
{
	for(;t>0;t--)
		{
			DelayMillis();
		}
}
