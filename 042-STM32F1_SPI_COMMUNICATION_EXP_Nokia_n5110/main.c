#include "stm32f10x.h" 
#include "systick_time.h"
#include "gp_drive.h" 
#include "SPI_drive.h"
#include "n5110_drive.h"

/*
Pin setup

SPI - 1
--> 
PA0 -->RST
PA1 --> DC
PA2 -->Screen Light
PA4 --> SS
PA5 --> SCLK
PA7 --> MOSI

3.3V --> Vcc
G --> Grd
*/




int main(void)
{
systick_init();
n5110_init(1);


	while(1)
	{
		n5110_print(3,10," Hello WeeW ");
		DelayMs(500);
		toggle_GP(PA,2);
	}
	
}
