#include "systick_time.h"
#include "DS3231_Drive.h"
#include "uart_drive.h"


/*
I2C2
PB10 -> SCL
PB11 -> SDA

I2C1
PB6 -> SCL
PB7 -> SDA


*/

char yr = 20;
char month = 10;
char day = 3;
char hrs = 0;
char min = 44;
char sec = 30;
char time_table[7];
char time[12],date[12];
int main(void)
{
	systick_init();
	i2c_init(2,i2c_FM);
	UART_init(2,115200);
	//DS3231_update_date_time(2,yr,month,day,hrs,min,sec);
	UART_SEND(2,"Hello WeeW\n");
	DelayMs(500);
	

	
	while(1)
	{
		
		DS3231_get_time(2,time_table);
		int2time(DS3231_reverter(time_table[2]),time);
		int2time(DS3231_reverter(time_table[1]),time);
		int2time(DS3231_reverter(time_table[0]),time);
		
		// SEND time using UART
		UART_SEND(2,time);
		UART_SEND(2,"\n");
		int2date(DS3231_reverter(time_table[6]),date);
		int2date(DS3231_reverter(time_table[5]),date);
		int2date(DS3231_reverter(time_table[4]),date);
		UART_SEND(2,date);
		UART_SEND(2,"\n");
		
		str_empty(time);
		str_empty(date);
		UART_SEND(2,"-----------------------------------------------------\n");
		DelayMs(1000);
	}
	
}


