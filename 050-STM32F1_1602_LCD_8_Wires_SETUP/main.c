#include "gp_drive.h"
#include "systick_time.h"
#include "lcd_1602_drive.h"
/*
Pin setup

PA8 -> RS
PA9 -> RW
PA10-> E
PA0 -> DB0
PA1 -> DB1
PA2 -> DB2
PA3 -> DB4
PA4 -> DB4
PA5 -> DB5
PA6 -> DB6
PA7 -> DB7
*/

// msg function

int main(void)
{
		systick_init();// initialize the delay function (Must initialize)
		lcd_init();
		lcd_msg(1, 1,"Welcome to the");
		lcd_msg(2, 6,"WeeW");
	while(1)
	{


	}
	
}

