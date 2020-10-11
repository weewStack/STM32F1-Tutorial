#include "AT24C_Drive.h"


// Setup the AT24C address default (address is 0xAE)
void AT24C_add(char i2c, char R_W)
{
	i2c_add(i2c,0xAE,R_W);
}

//Setup the transmit / save byte function
void AT24C_save_byte(char i2c,short reg,char data)
{
	char reg_1 = ((reg>>8) & 0x00FF);
	char reg_2 = (reg & 0x00FF);
	i2c_start(i2c);
	AT24C_add(i2c,0);
	i2c_data(i2c,reg_1);
	i2c_data(i2c,reg_2);
	i2c_data(i2c,data);
	i2c_stop(i2c);
	DelayMs(20);
}

//Setup the transmit / save byte function
void AT24C_save_page(char i2c,short reg,char * str,char data_len)
{
	char reg_1 = ((reg>>8) & 0x00FF);
	char reg_2 = (reg & 0x00FF);
	int i;
	i2c_start(i2c);
	AT24C_add(i2c,0);
	i2c_data(i2c,reg_1);
	i2c_data(i2c,reg_2);

	for(i=0;i<data_len;i++)
	{
		i2c_data(i2c,str[i]);
	}
	i2c_stop(i2c);
	DelayMs(20);
}

//Setup the rx/load byte function
char AT24C_load_byte(char i2c,short reg)
{
	char result;
	char reg_1 = ((reg>>8) & 0x00FF);
	char reg_2 = (reg & 0x00FF);
	i2c_start(i2c);
	AT24C_add(i2c,0);
	i2c_data(i2c,reg_1);
	i2c_data(i2c,reg_2);
	i2c_start(i2c);
	AT24C_add(i2c,1);
	result = i2c_rx(i2c,NACK);
	i2c_stop(i2c);
	DelayMs(20);
	return result;
}


//Setup the rx/load page function
void AT24C_load_page(char i2c,short reg,char * str,char data_len)
{
	int i;
	char reg_1 = ((reg>>8) & 0x00FF);
	char reg_2 = (reg & 0x00FF);
	i2c_start(i2c);
	AT24C_add(i2c,0);
	i2c_data(i2c,reg_1);
	i2c_data(i2c,reg_2);
	i2c_start(i2c);
	AT24C_add(i2c,1);
	for(i=0;i<(data_len-1);i++)
	{
		str[i] = i2c_rx(i2c,ACK);
	}
	str[i] = i2c_rx(i2c,NACK);
	i2c_stop(i2c);
	DelayMs(20);
}
