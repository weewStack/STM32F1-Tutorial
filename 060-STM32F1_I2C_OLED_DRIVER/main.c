#include "systick_time.h"
#include "i2c_drive.h"
#include "oled_drive.h"



int main(void)
{
	
	systick_init();
	oled_init_32(2);
	oled_init_64(1);
	//DelayMs(2000);
	oled_blank(2);
	oled_msg(2,2,30,"Hello WeeW");
	oled_blank(1);
	oled_msg(1,3,30,"Hello WeeW");
	
	while(1)
	{

	}
	
}

