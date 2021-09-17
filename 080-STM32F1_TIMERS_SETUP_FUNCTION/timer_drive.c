#include "timer_drive.h"

void TDelay_Micros(char timer, int microS){
	int prescaler = 72-1;
	TIM_TypeDef * tim;

	if(timer==1)
	{
		//Setup the Counter at the bus level
		RCC->APB2ENR |= 0x0800;
	}
	else
	{
		RCC->APB1ENR |= 1 <<(timer-2);
	}
	switch(timer)
	{
		case 1 : tim = TIM1;break;
		case 2 : tim = TIM2;break;
		case 3 : tim = TIM3;break;
		case 4 : tim = TIM4;break;
	}
	
		// Setup the counter to 0
	tim->CNT = 0;
	
	// Setup the prescaler to 72 -> 1 div equal to 1 Micro Sec
	tim->PSC = prescaler;	
	
	// initialize the Auto reload register value
	tim->ARR = (microS-3);	
	
	//Enable the counter
	tim->CR1 |= 0x9;
	
	while(tim->CR1 & 1)
	{}
	
}

void TDelay_Millis(char timer, int milliS)
{
	int i = 0;
	for(i=0;i<milliS;i++)
	{
		TDelay_Micros(timer,1000);
	}
}

void TDelay_Micro(int microS){
	TDelay_Micros(T4, microS);
}

void TDelay_Milli(int milliS)
{
	TDelay_Millis(T4, milliS);
	
}
