#include "stm32f10x.h" 

#include "stopwatch.h"
/*
Nokia Pin setup

SPI - 1
--> 
PA0 -->RST
PA1 --> DC
PA2 -->Screen Light
PA4 --> SS
PA5 --> SCLK
PA7 --> MOSI

3.3V --> Vcc
G --> Grd

PB0 -> reset 
PB1 -> start/stop

*/
unsigned short sw_start = 0;
unsigned short sw_rst = 1;
unsigned int counter = 0;
unsigned long millis = 0;


unsigned short digit = 0;

char time[7];
char number[3];

int main(void)
{
sw_init();

	while(1)
	{
		
		if(sw_rst)
		{
			//reset function
			sw_reset(&sw_rst, &millis);
		}
		// stop function
		else if ((sw_start == 0) && (counter != 0))
		{
			sw_stop(&counter);
		}
		// start function
		else if ((sw_start == 1) && (counter != 0))
		{
			sw_start_func(&millis,&counter,number,time);		
		}
	}
	
}
// PIN interrup function
void EXTI0_IRQHandler()
{
	EXTI->PR |= 1;
	sw_rst = 1;
}
void EXTI1_IRQHandler()
{
	EXTI->PR |= 2;
	//systick_int_start();
	if(sw_start)
	{
		sw_start=0;
	}
	else
	{
		sw_start=1;
		systick_int_start();
	}
}
// Systick interrup function
void SysTick_Handler(void)
{
	toggle_GP(PC,13);
	counter ++;
}

	

