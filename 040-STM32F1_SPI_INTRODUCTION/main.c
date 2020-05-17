#include "stm32f10x.h" 
#include "systick_time.h"
#include "gp_drive.h" 

/*
Actual setup

SPI - 1
--> 
PA4 --> SS
PA5 --> SCLK
PA6 --> MISO
PA7 --> MOSI

*/






int main(void)
{
systick_init();
// Activate SPI-1 peripheral / AFIO function
RCC->APB2ENR |= 1; //Enable AFIO function
RCC->APB2ENR |= 0x1000; // Enabling the SPI-1 periph
// Set up the pin 
init_GP(PA,4,OUT50,O_GP_PP);
init_GP(PA,5,OUT50,O_AF_PP);
init_GP(PA,6,IN,I_PP);
init_GP(PA,7,OUT50,O_AF_PP);

//*******Setup SPI peripherals*****
SPI1->CR1 |= 0x4; // Master Mode
SPI1->CR1 |= 0x31; // fclk / 265
SPI1->CR2 |= 0x4;
SPI1->CR1 |= 0x40; // Enabling SPI SPI periph
W_GP(PA,4,HIGH);

	while(1)
	{
		//Sending some data
		DelayMs(50);
		W_GP(PA,4,LOW);
		SPI1->DR = 'W';
		while(SPI1->SR & 0x80){}
		W_GP(PA,4,HIGH);
			W_GP(PA,4,LOW);
		SPI1->DR = 'e';
		while(SPI1->SR & 0x80){}
		W_GP(PA,4,HIGH);
			W_GP(PA,4,LOW);
		SPI1->DR = 'e';
		while(SPI1->SR & 0x80){}
		W_GP(PA,4,HIGH);
			W_GP(PA,4,LOW);
		SPI1->DR = 'W';
		while(SPI1->SR & 0x80){}
		W_GP(PA,4,HIGH);
		
	}
	
}
