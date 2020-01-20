/*
Welcome to the WeeW - Stack

Welcome to this new video for the STM32F1 microcontroller, where the code is from scratch.

Download the video code on Github: https://github.com/weewStack/STM32F1-Tutorial

This video has the following topic: 

1- Introduction to ESP01 / ESP8266 Hard & soft with Proof of working using UART Bridge communication (Part 1)

2- Creating the ESP-01 setup library / menu (Part 2)

3- Creating the ESP-01 wifi communication library (Part 3)

*/
/*
Part2: Details:

Creating a menu as bellow function by function

"\nSelect the next step: \nD: Detect the ESP01\n"

	
	***********************************

"\nSelect the next step: \n\
	M: Manual input ESP\n\
	R: Reset\n\
	L: List Networks\n\
	P: Get IP address\n\
	A: Automatic connection using saved Network and password\n\
	I: Input Network & Pass\n\
	C: Check Network Connection\n"
*/

/*
Part3: Details:

0- Setup the GPIOs // PA0(RED) , PA1 (BLUE)
1- Review the communication key parameters
2- Build the library for the LED control
3- Add the data streaming Push botton PA4
4- wrap-up the library and project

*/


#include "stm32f10x.h"    
#include "gp_drive.h" 
#include "systick_time.h"
#include "uart_drive.h"
#include "help_func.h"
#include "esp01_drive.h"



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

char USART_2_msg[2000];
unsigned short USART_2_cnt = 0;
unsigned short USART_2_sig = 0;
unsigned short USART_2_bdg = 0;
unsigned short uart_2_mgr[7]={0,0,0,0,0,0,0};

char USART_3_msg[2000];
unsigned short USART_3_cnt = 0;
unsigned short USART_3_sig = 0;
unsigned short USART_3_bdg = 0;
unsigned short uart_3_mgr[7]={0,0,0,0,0,0,0};



int main(void)
{
	init_GP(PA,0,OUT50,O_GP_PP);
	init_GP(PA,1,OUT50,O_GP_PP);
	init_GP(PC,13,OUT50,O_GP_PP);
	init_GP(PA,4,IN,I_PP);
	
	W_GP(PA,0,HIGH);
	W_GP(PA,1,HIGH);
	
esp_init(USART_3_msg,USART_2_msg,uart_3_mgr,uart_2_mgr);
	
while(1)
	{
		esp_mgr(USART_3_msg,USART_2_msg,uart_3_mgr,uart_2_mgr);
		W_GP(PC,13,R_GP(PA,4));
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

