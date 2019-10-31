#include "stm32f10x.h"                  // Device header

void Delays(int time);

int main(void)
{
	RCC->APB2ENR |= 4; //// Enabling PORT A
	RCC->APB2ENR |= 0x10; /// Enabling PORT C
	GPIOA->CRL &= 0xFFFFFFF0; /// Reset the Port A PIN 0
	GPIOA->CRL |= 0x8; /// Set port A pin 0 as in Input push pull
	
	GPIOC->CRH &= 0xFF0FFFFF;
	GPIOC->CRH |= 0x00300000;
	
	while(1)
	{
		if(GPIOA->IDR & 0x00000001)
		{
			Delays(10);
			GPIOC->ODR ^= 0x2000;
			Delays(10);
		}
		else
		{
			GPIOC->ODR = 0x2000;
		}
	}
	
}


void Delays(int time)
{
	int t;
	for(;time>0;time--)
	{
	 for(t=0;t<100000;t++)
		{}
	}
}
