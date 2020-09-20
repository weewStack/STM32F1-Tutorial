#include "bno055_drive.h"


// Setup the BNO address default (address is 0x29)
void bno055_add(char i2c, char R_W)
{
	i2c_add(i2c,0x52,R_W);
}


//Setup the transmit function
void bno055_tx(char i2c,char reg,char data)
{
	i2c_start(i2c);
	bno055_add(i2c,0);
	i2c_data(i2c,reg);
	i2c_data(i2c,data);
	i2c_stop(i2c);
}


//Setup the recieve function
void bno055_rx(char i2c,char reg,char * str,char data_len)
{
	int i;
	i2c_start(i2c);
	bno055_add(i2c,0);
	i2c_data(i2c,reg);
	
	i2c_start(i2c);
	bno055_add(i2c,1);
	
	for(i=0;i<(data_len-1);i++)
	{
		str[i] = i2c_rx(i2c,ACK);
	}
	str[i] = i2c_rx(i2c,NACK);
	
	i2c_stop(i2c);

}

//Initialization function for the bno
void bno55_init(char i2c)
{
	systick_init();
	i2c_init(i2c,i2c_FM);
	bno055_tx(i2c,0x3D,0x0C);
	DelayMs(50);
}

// Getting Euler's angle
void bno055_eul(char i2c,short * angle)
{
short val = 0;
int i = 0;
char eul[8];
	
	bno055_rx(i2c,0x1A,eul,6);
	for(i=0;i<3;i++)
	{
		val = eul[i*2+1];
		val = val << 8;
		val |= eul[i*2];
		angle[i] = (val/16);
	}
}

