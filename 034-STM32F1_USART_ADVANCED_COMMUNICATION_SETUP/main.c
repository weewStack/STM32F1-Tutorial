/*
Welcome to the WeeW - Stack

Welcome to this new video for the STM32F1 microcontroller, where the code is from scratch.

Download the video code on Github: https://github.com/weewStack/STM32F1-Tutorial

This video has the following topic:

1- Understand the USART-UART advanced communication strategy

2- Update the UART / Systick interrupt library

3- Make the input function (Equivalent of the input for Python) 

*/

#include "stm32f10x.h"    
#include "gp_drive.h" 
#include "systick_time.h"
#include "uart_drive.h"



/*
UART Manager
0- count
1- signal
2- Bridge
3- Terminator should 1: Terminator / 0: Interrupt
4- terminator char 
5- time cst
6- time counter 

*/
/*
char USART_1_msg[250];
unsigned short USART_1_cnt = 0;
unsigned short USART_1_sig = 0;
unsigned short USART_1_bdg = 0;
*/
unsigned short uart_1_mgr[7]={0,0,0,0,0,0,0};

char USART_2_msg[250];
unsigned short USART_2_cnt = 0;
unsigned short USART_2_sig = 0;
unsigned short USART_2_bdg = 0;
unsigned short uart_2_mgr[7]={0,0,0,0,'0',500,0};

char USART_3_msg[250];
unsigned short USART_3_cnt = 0;
unsigned short USART_3_sig = 0;
unsigned short USART_3_bdg = 0;
unsigned short uart_3_mgr[7]={0,0,0,0,'0',500,0};




char chat = 'C';

char msg[30] = "Welcome to the WeeW\n";

int main(void)
{
systick_init();
UART_init(2,115200);
UART_init(3,115200);

DelayMs(100);

UART_SEND(2,"This is UART 2");
UART_SEND(3,"This is UART 3");
	

while(1)
	{
		if(uart_2_mgr[1] == 1)
		{
			UART_SEND(3,USART_2_msg);
			uart_2_mgr[1] = 0;
			str_empty(USART_2_msg);
		}
		if(uart_3_mgr[1] == 1)
		{
			UART_SEND(2,USART_3_msg);
			uart_3_mgr[1] = 0;
			str_empty(USART_3_msg);
		}
		
		
	}
}



void USART2_IRQHandler()
{
	UART_ISR(2,uart_2_mgr, USART_2_msg);
}

void USART3_IRQHandler()
{
	UART_ISR(3,uart_3_mgr, USART_3_msg);
}

void SysTick_Handler(void)
{
	systick_int(uart_1_mgr,uart_2_mgr,uart_3_mgr);
}

