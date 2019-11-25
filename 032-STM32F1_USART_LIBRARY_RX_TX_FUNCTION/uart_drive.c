#include "uart_drive.h"

void UART_init(unsigned short usart, unsigned long BR)
{
 /// If using USART1 clock speed 72Mhz, else 36Mhz
	/// USART3 -> PB10 (Tx) and PB11(Rx)
	/// USART2 -> PA2 (Tx) and PA3(Rx)
	/// USART1 -> PA9 (Tx) and PA10(Rx)
	
	// Enable the Alternate Function for PINs
	unsigned long BRR_Cal;
	
	BRR_Cal = USART_BRR(usart,BR);
	
		RCC->APB2ENR |= 1;
	
	
	if(usart == 1)
	{
	RCC->APB2ENR |=0x4000;
	init_GP(PA,9,OUT50,O_AF_PP);
	init_GP(PA,10,IN,I_PP);
	// Setup the baude rate for 9600 bps
	USART1->BRR = BRR_Cal; 
	USART1->CR1 |= 8;
	USART1->CR1 |= 4;
	USART1->CR1 |= 0x2000;
	}
	else if (usart == 2)
	{		//-----------Init UART ------------///
	// Enable UART2
		RCC->APB1ENR |=0x20000;
	// Enable the related PINs
	init_GP(PA,2,OUT50,O_AF_PP);
	init_GP(PA,3,IN,I_PP);
	// Setup the baude rate for 9600 bps
	USART2->BRR = BRR_Cal; 
	// Enable Uart Transmit
	USART2->CR1 |= 8;
	// Enable Uart Recive
	USART2->CR1 |= 4;
	// Enable Uart
	USART2->CR1 |= 0x2000;}
	else if (usart == 3)
	{
	RCC->APB1ENR |=0x40000;
	init_GP(PB,10,OUT50,O_AF_PP);
	init_GP(PA,11,IN,I_PP);
	// Setup the baude rate for 9600 bps
	USART3->BRR = BRR_Cal; 
	USART3->CR1 |= 8;
	USART3->CR1 |= 4;
	USART3->CR1 |= 0x2000;
	}
}

unsigned long USART_BRR(unsigned short usart, unsigned long BR)
{
	unsigned long div = 36000000UL;
	unsigned long dec;
	unsigned long final;
	double frac = 36000000.00;
	double frac2 = 1.00;
	
	if(usart == 1)
	{
	div = 72000000UL;
	frac = 72000000.00;
	}
	div = div / (BR*16);
	frac = 16*((frac / (BR*16))-div);
	dec = frac;
	frac2 = 100*(frac-dec);
	if(frac2>50)
	{
		dec ++;
		if(dec == 16)
		{
			dec = 0;
			div ++;
		}
	}
	
	final = (div<<4);
	final += dec;
	
	return final;
	
}


char UART_RX(unsigned short uart)
{
	char c;
	if(uart == 1)
		{
		while((USART1->SR & 0x20) == 0x00)
		{};
		c = USART1->DR;
		}
	else if(uart == 2)
		{
		while((USART2->SR & 0x20) == 0x00)
		{};
		c = USART2->DR;
		}
		if(uart == 3)
		{
		while((USART3->SR & 0x20) == 0x00)
		{};
		c = USART3->DR;
		}
		return c;
}

void UART_TX(unsigned short uart,char c)
{
	if(uart == 1)
		{
			while((USART1->SR & (1<<6)) == 0x80)
			{};
			USART1->DR = c;
		}
	else if(uart == 2)
		{
			while((USART2->SR & (1<<6)) == 0x80)
			{};
			USART2->DR = c;
		}
		if(uart == 3)
		{
			while((USART3->SR & (1<<6)) == 0x80)
			{};
			USART3->DR = c;
		}
}
