#include "nrf24_drive.h"

void nrf_init(unsigned short spi){
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
	SPI1->CR1 |= 0x10; // fclk / 8
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
	SPI2->CR1 |= 0x10; // fclk / 8
	SPI2->CR2 |= 0x4;
	SPI2->CR1 |= 0x40; // Enabling SPI SPI periph
	W_GP(PB,12,HIGH);
	
	
	// Init CE (PA0) PIN & set low
	
	// Init IRQ pin (PA1) & Interrupt for falling Trigger
	
	//Power down
	
	
	//Small power usage 
	
	
	//lower DR speed
	
	
	// Enable Dynamic Payload : Reg Feature bit EN_DPL
	
}
	
	

}
// nrf_cmd_rd
char nrf_cmd_rd(unsigned short spi, char register_add)
{
	char nrf_spi_rd;
	spi_cs(1,LOW);
	spi_rx(1,(register_add & nrf_read));
	nrf_spi_rd= spi_rx(1,(register_add & nrf_read));
	spi_cs(1,HIGH);
	return nrf_spi_rd;
}

// nrf_cmd_wr
char nrf_cmd_wr(unsigned short spi, char register_add, char new_value,char mask)
{
	char reg_value, new_reg_value, cmd;
	cmd = nrf_write | register_add;
	reg_value = nrf_cmd_rd(1, register_add);
	new_reg_value = (reg_value & mask) | new_value;
	
	spi_cs(1,LOW);
	spi_rx(1,cmd);
	spi_rx(1,new_reg_value );
	spi_cs(1,HIGH);
	
	reg_value = nrf_cmd_rd(1, register_add);
	if(reg_value == new_reg_value)
	{
		return 1;
	}
	else
		{
		return 0;
	}
	
}

//nrf_cmd
char nrf_cmd(unsigned short spi, char cmd)
{
	char nrf_spi_rd;
	spi_cs(1,LOW);
	spi_rx(1,cmd);
	nrf_spi_rd= spi_rx(1,(cmd));
	spi_cs(1,HIGH);
	return nrf_spi_rd;
}