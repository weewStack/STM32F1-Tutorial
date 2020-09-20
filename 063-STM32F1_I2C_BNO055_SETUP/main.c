#include "systick_time.h"
#include "bno055_drive.h"
#include "oled_drive.h"
#include "help_func.h"

/*
I2C2
PB10 -> SCL
PB11 -> SDA

I2C1
PB6 -> SCL
PB7 -> SDA
*/

short angles[3];
short yaw,roll, pitch;
char num[10];

int main(void)
{
	bno55_init(2);
	oled_init_64(2);
	oled_blank(2);
	
	oled_msg(2,2,10,"Yaw: ");
	oled_msg(2,4,10,"Roll: ");
	oled_msg(2,6,10,"Pitch: ");
	
	while(1)
	{
		bno055_eul(2,angles);
		yaw = angles[Yaw];
		roll = angles[Roll];
		pitch = angles[Pitch];
		
		oled_msg(2,2,50,"          ");
		int2char(yaw,num);
		oled_msg(2,2,50,num);
		str_empty(num);
		
		oled_msg(2,4,50,"          ");
		int2char(roll,num);
		oled_msg(2,4,50,num);
		str_empty(num);
		
		oled_msg(2,6,50,"          ");
		int2char(pitch,num);
		oled_msg(2,6,50,num);
		str_empty(num);
	}
	
}

