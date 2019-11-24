/*
Welcome to the WeeW - Electronics
follow us on our Channel : https://www.youtube.com/channel/UCnTWd_4LwCEcAw19Jds0Vjg

The topic of this program is to:

- A general init function for the USART1, USART2, USART3
- A function that generate the right USART BAUD Rate
- test Recieve & send Char using different USART and baud rates

Related explanatory video : https://youtu.be/w1wBcrSlydQ

*/

#include "stm32f10x.h"    
#include "gp_drive.h" 
#include "systick_time.h"
#include "uart_drive.h"


char chat = 'C';

int main(void)
{
systick_init();
UART_init(2,256000);


while(1)
	{
		// Recieve Char
		while((USART2->SR & 0x20) == 0x00)
		{};
		chat = USART2->DR;
		// Transmit Char
		//DelayMs(100);
		while((USART2->SR & (1<<6)) == 0x80)
		{};
		USART2->DR = chat;
	}
}



