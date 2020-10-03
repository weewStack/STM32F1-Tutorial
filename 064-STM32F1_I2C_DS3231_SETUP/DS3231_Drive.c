#include "DS3231_Drive.h"

// Setup the DS3231 address default (address is 0xD0)
void DS3231_add(char i2c, char R_W)
{
	i2c_add(i2c,0xD0,R_W);
}


//Setup the transmit function
void DS3231_tx(char i2c,char reg,char data)
{
	i2c_start(i2c);
	DS3231_add(i2c,0);
	i2c_data(i2c,reg);
	i2c_data(i2c,data);
	i2c_stop(i2c);
	
}

//Setup the rx function
void DS3231_rx(char i2c,char reg,char * str,char data_len)
{
	int i;
	i2c_start(i2c);
	DS3231_add(i2c,0);
	i2c_data(i2c,reg);
	
	i2c_start(i2c);
	DS3231_add(i2c,1);
	for(i=0;i<(data_len-1);i++)
	{
		str[i] = i2c_rx(i2c,ACK);
	}
	str[i] = i2c_rx(i2c,NACK);
	
	i2c_stop(i2c);
}

//Getting the right format
char DS3231_converter(char date)
{
	char date_format = 0;
	date_format = date/10;
	date_format = date_format << 4;
	date_format |= (date%10);
	return date_format;
}

void DS3231_update_sec(char i2c,char sec)
{
	DS3231_tx(i2c,0x00,DS3231_converter(sec));
}
void DS3231_update_min(char i2c,char min)
{
	DS3231_tx(i2c,0x01,DS3231_converter(min));
}

void DS3231_update_hrs(char i2c,char hrs)
{
	DS3231_tx(i2c,0x02,DS3231_converter(hrs));
}
void DS3231_update_day(char i2c,char date)
{
	DS3231_tx(i2c,0x04,DS3231_converter(date));
}
void DS3231_update_month(char i2c,char month)
{
	DS3231_tx(i2c,0x05,DS3231_converter(month));
}
void DS3231_update_yr(char i2c,char yr)
{
	DS3231_tx(i2c,0x06,DS3231_converter(yr));
}
void DS3231_update_time(char i2c,char hrs,char min,char sec)
{
	DS3231_update_sec(i2c,sec);
	DS3231_update_min(i2c,min);
	DS3231_update_hrs(i2c,hrs);
}
void DS3231_update_date(char i2c,char yr,char month,char day)
{
	DS3231_update_day(i2c,day);
	DS3231_update_month(i2c,month);
	DS3231_update_yr(i2c,yr);
}
void DS3231_update_date_time(char i2c,char yr,char month,char day,char hrs,char min,char sec)
{
	DS3231_update_time(i2c,hrs,min,sec);
	DS3231_update_date(i2c,yr,month,day);
}

//Data reverter
char DS3231_reverter(char time)
{
	char update = time >> 4;
	update *=10;
	update += (time & 0x0F);
	return update;
}

void DS3231_get_time(char i2c,char * str)
{
	DS3231_rx(i2c,0x00,str,7);
}

void int2time(char time,char str[])
{
	char num[3];
	if(len_str(str)>0)
	{
		Concatstr(str,":");
	}
	int2char(time,num);
	if(len_str(num)==0)
	{
		Concatstr(str,"0");
	}
	Concatstr(str,num);
	str_empty(num);
}

void int2date(char time,char str[])
{
	char num[3];
	if(len_str(str)>0)
	{
		Concatstr(str,"/");
	}
	int2char(time,num);
	if(len_str(num)==0)
	{
		Concatstr(str,"0");
	}
	Concatstr(str,num);
	str_empty(num);
}
