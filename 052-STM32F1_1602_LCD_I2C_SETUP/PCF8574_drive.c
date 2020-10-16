#include "PCF8574_drive.h"


void PCF8574_add(char i2c, char R_W)
{
	i2c_add(i2c,0x4E,R_W);
}

// Tx byte function
void PCF8574_tx_byte(char i2c, char data)
{
	i2c_start(i2c);
	PCF8574_add(i2c,0);
	i2c_data(i2c,data);
	i2c_stop(i2c);
}
