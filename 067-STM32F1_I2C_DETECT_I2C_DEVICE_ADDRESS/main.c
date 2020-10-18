#include "systick_time.h"
#include "i2c_drive.h"
#include "uart_drive.h"

/*
I2C2
PB10 -> SCL
PB11 -> SDA

I2C1
PB6 -> SCL
PB7 -> SDA
*/
int add;
char check = 0;
int main(void)
{
	systick_init();
	Digital_Output(PC,13);
	i2c_init(2,i2c_FM);
	UART_init(2,115200);
	for(add =0;add < 0xFE;add++)
	{
		if(i2c_check(2))
		{
			i2c_start(2);
			check = i2c_add(2,add,0);
			i2c_stop(2);
		}
		if(check)
		{
			UART_TX(2,add);
			UART_TX(2,'\n');
			check =0;
		}
	}
	
	while(1)
	{
		toggle_GP(PC,13);
		DelayMs(500);
		toggle_GP(PC,13);
		DelayMs(500);
	}
	
}

