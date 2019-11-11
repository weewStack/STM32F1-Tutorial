#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"
void Delays(int time);
int signal = 0;
int main(void)
{
	init_GP(PA,0,IN,I_PP);
	init_GP(PC,13,OUT50, O_GP_PP);
	init_GP(PA,12,OUT50,O_GP_PP);
	
	__disable_irq();
	AFIO->EXTICR[0] = 0x00; /// Activating the interrupts for the Port A PIN 0
	EXTI->IMR |= 1; /// Enable the interrupt for EXTI0
	EXTI->RTSR |= 1; /// Generate a system interrupt at the rising edge
	NVIC_EnableIRQ(EXTI0_IRQn); // Enable the global interrupt function
	__enable_irq();
	
	
	while(1)
	{
		W_GP(PA,12,signal);
		if(signal) /// Checking status of PIN ! portA 
		{
			Delays(10);
			toggle_GP(PC,13); /// Toggle the PIN state
			Delays(10);
		}
		else
		{
			W_GP(PC,13,1); /// Set the PIN 13 port C high
		}

	}
	
}


void Delays(int time) /// Random delay function
{
	int t;
	for(;time>0;time--)
	{
	 for(t=0;t<100000;t++)
		{}
	}
}

void EXTI0_IRQHandler()
{
	EXTI->PR |=1;
	if(signal)
	{signal = 0;}
	else
	{signal = 1;}
}

