#include "gp_drive.h"
#include "systick_time.h"
#include "lcd_1602_drive.h"
/*
Pin setup : 4 bits data communication

PA8 -> RS
PA9 -> RW
PA10-> E

PA4 -> DB4
PA5 -> DB5
PA6 -> DB6
PA7 -> DB7
*/

// update init for 4 bit data transfer 

int main(void)
{
		systick_init();// initialize the delay function (Must initialize)
		lcd_init();
		lcd_msg(1, 0,"Welcome to the");
		lcd_msg(2, 6,"WeeW");
	while(1)
	{


	}
	
}

