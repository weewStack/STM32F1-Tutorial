/*
Welcome to the WeeW - Electronics
follow us on our Channel : https://www.youtube.com/channel/UCnTWd_4LwCEcAw19Jds0Vjg

The topic of this program is to:

- A general init function for the UART Transmit Tx
- A general init function for the UART Receive Rx


Related explanatory video : https://youtu.be/ZoSyhQNDyMI

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
		chat = UART_RX(2);
		UART_TX(2,chat);
	}
}


