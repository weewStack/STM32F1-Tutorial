#include "stm32f10x.h"                  // Device header


void delay(int rep);

int main(void)
{
	RCC->APB2ENR |= 0x10; /// Or  0b10000 --> Anabling Preiph GPIOC
	GPIOC->CRH &= 0xFF0FFFFF;  /// Reset the PORT C PIN 13
	GPIOC->CRH |= 0x00300000;  /// Set Port C PIN 13 as Output 
	GPIOC->ODR  |= 0x2000;     /// Set Port C Pin 13 
	while(1)
	{
		/// Blinking the Port C pin 13 
		GPIOC->ODR  |= 0x2000;
		delay(10);
		GPIOC->ODR  &= ~0x2000;
		delay(10);
		
	}

}


/// Random time delay Function
void delay(int rep)
{
	for(;rep>0;rep--)
	{
	int i;
	for(i=0; i< 100000;i++)
	{}
	}
}
