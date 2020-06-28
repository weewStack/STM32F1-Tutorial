#include "stm32f10x.h" 
#include "systick_time.h"
#include "gp_drive.h"
#include "uart_drive.h"
#include "nrf24_drive.h"
/*
NRF24 Pin setup

SPI - 1
--> 
PA0 -->Channel 4-->CE
PA1 --> IRQ
PA4 -->Channel 0--> SS
PA5 -->Channel 1--> SCLK
PA7 -->Channel 2--> MOSI
PA7 -->Channel 3--> MOSI

3.3V --> Vcc
G --> Grd

**UART2 -> PA2 (Tx) and PA3(Rx)

*/
int i;


int main(void)
{
	systick_init();
	UART_init(2,115200);
	UART_SEND(2,"Starting NRF24 communication\n");
	nrf_init(1);
	
	
	init_GP(PC,13,OUT50,O_GP_PP); // for quick Debugging purposes
	W_GP(PC,13,HIGH); // for quick Debugging purposes
	
	nrf_cmd_wr(1, NRF_CONFIG, PRIM_TX,PRIM_RX_MASK);
	
	for(i=0;i<10;i++)
	{
		UART_TX(2,i);
		UART_TX(2,'-');
		UART_TX(2,nrf_cmd_rd(1, i));
		UART_TX(2,'\n');
	
	}
	
	
	while(1)
	{

	
	}
	
}

