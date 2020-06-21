#include "stm32f10x.h" 
#include "gp_drive.h" 
#include "SPI_drive.h"

void spi_init(unsigned short spi){
RCC->APB2ENR |= 1; //Enable AFIO function

if(spi ==1)
{
	// Activate SPI-1 peripheral / AFIO function
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
}else if(spi == 2){
	RCC->APB1ENR |= 0x4000; // Enabling the SPI-2 periph
		// Set up the pin 
	init_GP(PB,12,OUT50,O_GP_PP);
	init_GP(PB,13,OUT50,O_AF_PP);
	init_GP(PB,14,IN,I_PP);
	init_GP(PB,15,OUT50,O_AF_PP);

	//*******Setup SPI peripherals*****
	SPI2->CR1 |= 0x4; // Master Mode
	SPI2->CR1 |= 0x31; // fclk / 265
	SPI2->CR2 |= 0x4;
	SPI2->CR1 |= 0x40; // Enabling SPI SPI periph
	W_GP(PB,12,HIGH);
}
	
	

}


void spi_tx(unsigned short spi, char tx_char)
{
	if (spi ==1 )
	{
		W_GP(PA,4,LOW);
		SPI1->DR = tx_char;
		while(SPI1->SR & 0x80){}
		W_GP(PA,4,HIGH);
	}else if (spi ==2 )
	{
		W_GP(PB,12,LOW);
		SPI2->DR = tx_char;
		while(SPI2->SR & 0x80){}
		W_GP(PB,12,HIGH);
	}
}


void spi_msg(unsigned short spi, char str[])
{
int i =0;
	if (spi==1)
	{
	W_GP(PA,4,LOW);
	while(str[i])
	{
		SPI1->DR = str[i];
		while(SPI1->SR & 0x80){}
		i++;
	}
	W_GP(PA,4,HIGH);
	}
	else if (spi==2)
	{
	W_GP(PB,12,LOW);
	while(str[i])
	{
		SPI2->DR = str[i];
		while(SPI2->SR & 0x80){}
		i++;
	}
	W_GP(PB,12,HIGH);
	}
}


//spi_rx
char spi_rx(unsigned short spi, char value)
{
	char rx_val;
	if(spi==1)
	{
		SPI1->DR = value;while(SPI1->SR & 0x80){}
		while(SPI1->SR & 0x1){rx_val = SPI1->DR;}
	}
	else if(spi==2)
	{
		SPI2->DR = value;while(SPI2->SR & 0x80){}
		while(SPI2->SR & 0x1){rx_val = SPI2->DR;}
	}

	return rx_val;
}

//spi_cs
void spi_cs(unsigned short spi, unsigned short LOW_HIGH)
{
	if(spi==1)
	{
		W_GP(PA,4,LOW_HIGH);
	}
	else if(spi==2)
	{
		W_GP(PB,12,LOW_HIGH);
	}
}

