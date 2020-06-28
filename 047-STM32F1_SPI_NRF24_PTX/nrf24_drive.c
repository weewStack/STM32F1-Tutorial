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
}

	// Init CE (PA0) PIN & set low
init_GP(PA,0,OUT50,O_GP_PP);
W_GP(PA,0,LOW);
	
	// Init IRQ pin (PA1) & Interrupt for falling Trigger
init_GP(PA,1,IN,I_PP);

__disable_irq();
EXTI->IMR |= 2;
EXTI->FTSR |=2;
NVIC_EnableIRQ(EXTI1_IRQn);
__enable_irq();
	
	//Power down
	nrf_cmd_wr(1,NRF_CONFIG,POWER_DOWN,POWER_MASK);
	DelayMs(10);

	
	//Small power usage 
	nrf_cmd_wr(1,NRF_SETUP ,RF_PWR_18db,RF_PWR_MASK);
	
	//lower DR speed
	nrf_cmd_wr(1,NRF_SETUP ,RF_DR_LOW,RF_DR_MASK);
	
	nrf_cmd_wr(1,NRF_SETUP_RETR,ARD_750us,ARD_MASK);
	
	// Enable Dynamic Payload : Reg Feature bit EN_DPL
	nrf_cmd_wr(1,NRF_FEATURE ,EN_DPL,EN_DPL_MASK);
	nrf_cmd_wr(1,NRF_DYNPD ,EN_DPL_P0,EN_DPL_P0_MASK);

}
// nrf_cmd_rd : Reading NRF24 registers
char nrf_cmd_rd(unsigned short spi, char register_add)
{
	char nrf_spi_rd;
	spi_cs(1,LOW);
	spi_rx(1,(register_add & nrf_read));
	nrf_spi_rd= spi_rx(1,(register_add & nrf_read));
	spi_cs(1,HIGH);
	return nrf_spi_rd;
}

// nrf_cmd_wr : Writing NRF24 registers
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

//nrf_cmd : Simple command for NRF24
char nrf_cmd(unsigned short spi, char cmd)
{
	char nrf_spi_rd;
	spi_cs(1,LOW);
	spi_rx(1,cmd);
	nrf_spi_rd= spi_rx(1,(cmd));
	spi_cs(1,HIGH);
	return nrf_spi_rd;
}


// nrf_prx_init() : initializing the NRF to start the Primary Reciever mode
void nrf_prx_init(unsigned short spi)
{
	nrf_cmd_wr(spi,NRF_STATUS ,RX_DR_SET,RX_DR_MASK);
	nrf_cmd_wr(spi,NRF_STATUS ,TX_DS_SET,TX_DS_MSAK);
	nrf_cmd_wr(spi,NRF_STATUS ,MAX_RT_SET,MAX_RT_MASK);
	nrf_cmd(spi,FLUSH_RX);
	nrf_cmd(spi,FLUSH_TX);
	nrf_cmd_wr(spi,NRF_CONFIG,PRIM_RX,PRIM_RX_MASK);
	nrf_cmd_wr(spi,NRF_CONFIG ,POWER_UP,POWER_MASK);
	DelayMs(10);
	W_GP(PA,0,HIGH);

}


// nrf_rf_rx(payload)
void nrf_rf_rx(unsigned short spi,char payload[])
{
	int payload_w = 0;
	int i;
	
	payload_w = nrf_cmd(spi,R_RX_PL_WID);
	spi_cs(spi,LOW);
	spi_rx(spi,R_RX_PAYLOAD);
	for(i=0;i<payload_w;i++)
	{
		payload[i] = spi_rx(spi,R_RX_PAYLOAD);
	}	
	spi_cs(spi,HIGH);
	nrf_cmd_wr(spi,NRF_STATUS ,RX_DR_SET,RX_DR_MASK);
	nrf_cmd(spi,FLUSH_RX);
	}

// nrf_ptx_init

void nrf_ptx_init(unsigned short spi)
{
	nrf_cmd_wr(spi,NRF_STATUS ,RX_DR_SET,RX_DR_MASK);
	nrf_cmd_wr(spi,NRF_STATUS ,TX_DS_SET,TX_DS_MSAK);
	nrf_cmd_wr(spi,NRF_STATUS ,MAX_RT_SET,MAX_RT_MASK);
	nrf_cmd(spi,FLUSH_RX);
	nrf_cmd(spi,FLUSH_TX);
	nrf_cmd_wr(spi,NRF_CONFIG,PRIM_TX,PRIM_RX_MASK);
	nrf_cmd_wr(spi,NRF_CONFIG ,POWER_UP,POWER_MASK);
	DelayMs(10);
	W_GP(PA,0,HIGH);
}


// nrf_rf_tx(payload)

void nrf_rf_tx(unsigned short spi,char payload[])
{
	int i = 0;
	if(nrf_cmd_rd(spi,NRF_CONFIG) & 1)
	{
		nrf_ptx_init(spi);
	}
	spi_cs(spi,LOW);
	spi_rx(spi,W_TX_PAYLOAD);
	while(payload[i])
	{
		spi_rx(spi,payload[i]);
		i++;
	}
	spi_cs(spi,HIGH);
	
}
