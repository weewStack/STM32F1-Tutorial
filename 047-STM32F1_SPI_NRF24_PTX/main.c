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
unsigned short trigger = 0;
unsigned short msg_status = 0;
char payload[32] = "Hello WeeW\n";

int main(void)
{
	systick_init();
	UART_init(2,115200);
	UART_SEND(2,"Starting Transmit NRF24 communication\n");
	nrf_init(1);
	
	
	//initialize PB0 & inrterrupt
	init_GP(PB,0,IN,I_PP);

__disable_irq();
AFIO->EXTICR[0] |= 0x1;
EXTI->IMR |= 1;
EXTI->FTSR |=1;
NVIC_EnableIRQ(EXTI0_IRQn);
__enable_irq();
	
	
	init_GP(PC,13,OUT50,O_GP_PP); // for quick Debugging purposes
	W_GP(PC,13,HIGH); // for quick Debugging purposes
	
	nrf_ptx_init(1);
	
	UART_TX(2,nrf_cmd_rd(2,NRF_CONFIG));
	
	while(1)
	{
		
		if(trigger)
		{
			nrf_rf_tx(1,payload);
			
			msg_status = 1;
			while(msg_status)
			{
				if(nrf_irq)
				{
					nrf_irq= 0;
					if(nrf_cmd_rd(1,NRF_STATUS) & 0x20)
					{
						msg_status = 0;
						trigger = 0;
						nrf_cmd_wr(1,NRF_STATUS,TX_DS_SET,TX_DS_MSAK);
						UART_SEND(2,"Message succefuly sent\n");		
					}
					else if(nrf_cmd_rd(1,NRF_STATUS) & 0x10)
					{
						nrf_cmd_wr(1,NRF_STATUS,MAX_RT_SET,MAX_RT_MASK);
						UART_SEND(2,"Max number of re-transmission reached\n");	
						DelayMs(500);
					}
					else if(nrf_cmd_rd(1,NRF_STATUS) & 0x1) 
					{
						msg_status = 0;
						trigger = 0;
						UART_SEND(2,"The payload is bigger than NRF buffer\n");	
						nrf_cmd(1,FLUSH_TX);
						DelayMs(100);
					}
				
				}
			
			}
		
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

void EXTI0_IRQHandler()
{
	EXTI->PR |= 1;
	trigger = 1;
	toggle_GP(PC,13);
}
