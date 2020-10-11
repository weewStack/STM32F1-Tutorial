#include "data_logger.h"
#include "uart_drive.h"

/*
I2C2
PB10 -> SCL
PB11 -> SDA

I2C1
PB6 -> SCL
PB7 -> SDA
*/

char time_table[10],time[12],date[12],save[10],num[12];
int i,tot_rec;
int main(void)
{
	systick_init();
	UART_init(2,115200);
	i2c_init(2,i2c_FM);
	logger_init(2);
	
	DS3231_get_time(2,time_table);
	logger_rec(2,time_table);
	/*
	for(i=0;i<10;i++)
	{
		UART_TX(2,AT24C_load_byte(2,i));
	}
	*/
	UART_SEND(2,"/n The number of records: ");
	tot_rec = Get_short(2,Rec_tot);
	int2char(tot_rec,num);
	UART_SEND(2,num);
	UART_SEND(2,"\n*********************************\n");
	for(i=0;i<tot_rec;i++)
	{
		logger_read(2,i,save);
		UART_SEND(2,"\n");
		DS3231_Time_Date(save,time,Time);
		DS3231_Time_Date(save,date,Date);
		UART_SEND(2,time);
		UART_SEND(2,"\n");
		UART_SEND(2,date);
		UART_SEND(2,"\n*********************************\n");
		str_empty(time);
		str_empty(date);
	}
	while(1)
	{
		
	}
	
}


