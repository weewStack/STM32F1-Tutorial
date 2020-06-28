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

unsigned short nrf_irq = 0;

char payload[32];
int i;
int main(void)
{
	systick_init();
	UART_init(2,115200);
	UART_SEND(2,"Starting Recieve NRF24 communication\n");
	nrf_init(1);
	//PB1 as LED
	init_GP(PB,1,OUT50,O_GP_PP);
	W_GP(PB,1,HIGH);
	
	init_GP(PC,13,OUT50,O_GP_PP); // for quick Debugging purposes
	W_GP(PC,13,HIGH); // for quick Debugging purposes
	
	nrf_prx_init(1);
	
	
	
	
	
	while(1)
	{
		
		// if nrf irq
				// -> Check status reg
				
				//--> Else flux RX 
		if(nrf_irq)
		{
			DelayMs(10);
			nrf_irq = 0;
			if(nrf_cmd_rd(1,NRF_STATUS) & 0x40)
			{
				// --> if RX then nrf_rf_rx(payload)
				nrf_rf_rx(1,payload);
				UART_SEND(2,payload);
				toggle_GP(PB,1);
			}
			else
			{
				nrf_prx_init(1);
			}
			W_GP(PC,13,HIGH);
			
		}
	
	}
	
}

// irq handler
void EXTI1_IRQHandler()
{
	EXTI->PR |= 2;
	nrf_irq = 1;
	W_GP(PC,13,LOW);
}
