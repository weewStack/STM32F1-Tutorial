#include "stm32f10x.h" 
#include "systick_time.h"
#include "gp_drive.h"
#include "uart_drive.h"
#include "nrf24_drive.h"
/*
NRF24 Pin setup

SPI - 1
--> 

PA4 --> SS
PA5 --> SCLK
PA7 --> MOSI
PA7 --> MOSI

SPI - 2

PB12 --> SS
PB13 --> SCLK
PB14 --> MOSI
PA15 --> MOSI


PA0 -->Channel 4-->CE
PA1 --> IRQ (Only in MODE1)
3.3V --> Vcc
G --> Grd

**UART2 -> PA2 (Tx) and PA3(Rx)

*/




char payload[32];

int main(void)
{
	systick_init();
	UART_init(2,115200);
	nrf_init(1,MODE0);
	
	
	// PTX Mode
	/*
	Digital_Input(PB,0); /// Push button for sending button for sending STM32
	*/
	
	// PRX Mode
	/*
	Digital_Output(PB,1); /// Connected to LED and toggle when recieve message
	W_GP(PB,1,HIGH);
	nrf_prx_init(1);
	*/
	while(1)
	{
		//Sending Code
		/*
		if(R_GP(PB,0))
		{
			 if(nrf_send(1,"Hey WeeW\n"))
			{
				UART_SEND(2,"Message sent succesfully\n");
			}
			else
			{
				UART_SEND(2,"Message sent failed\n");
			}
			DelayMs(10);
		}
		*/
	
		
		//Recieving Code
		/*
		if(nrf_msg_check(1))
		{
			nrf_rx(1,payload);
			UART_SEND(2,payload);
			toggle_GP(PB,1);
		}
		*/
		
			
	
	
	}
	
}

