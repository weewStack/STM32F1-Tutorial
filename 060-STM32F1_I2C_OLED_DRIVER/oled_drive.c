#include "oled_drive.h"




//oled_cmd_1byte() 
void oled_cmd_1byte(char i2c,char data)
{
	
	i2c_start(i2c);
	
	i2c_add(i2c, 0x78,0); //0x78 is the primary address
	
	i2c_data(i2c,0x00); // Control function for a command
	i2c_data(i2c,data);
	
	i2c_stop(i2c);
}


//oled_cmd_2byte()
void oled_cmd_2byte(char i2c,char data[])
{
	int i = 0;
	
	i2c_start(i2c);
	
	i2c_add(i2c, 0x78,0); //0x78 is the primary address
	
	i2c_data(i2c,0x00); // Control function for a command
	for (i=0;i<2;i++)
	{
		i2c_data(i2c,data[i]);
	}
	
	
	i2c_stop(i2c);
}


//oled_init()
void oled_init(char i2c, char screen_size)
{
	i2c_init(i2c,i2c_FM);
	char cmd[] = {0xA8,0x3F};
	oled_cmd_2byte(i2c,cmd);
	char cmd1[] = {0xD3,0x00};
	oled_cmd_2byte(i2c,cmd1);
	
	oled_cmd_1byte(i2c,0x40);
	oled_cmd_1byte(i2c,0xA1);
	
	oled_cmd_1byte(i2c,0xC8);
	
	char cmd2[] = {0xDA,screen_size};
	oled_cmd_2byte(i2c,cmd2);
	
	char cmd3[] = {0x81,0x7F};
	oled_cmd_2byte(i2c,cmd3);
	
	oled_cmd_1byte(i2c,0xA4);
	oled_cmd_1byte(i2c,0xA6);
	
	char cmd4[] = {0xD5,0x80};
	oled_cmd_2byte(i2c,cmd4);
	
	char cmd5[] = {0x8D,0x14};
	oled_cmd_2byte(i2c,cmd5);
	
	oled_cmd_1byte(i2c,0xAF);
	
	char cmd6[] = {0x20,0x10};
	oled_cmd_2byte(i2c,cmd6);
	
}
void oled_init_64(char i2c)
{
	oled_init(i2c, 0x12);
}

void oled_init_32(char i2c)
{
	oled_init(i2c, 0x22);
}

//oled_data()
void oled_data(char i2c,char data)
{
	
	i2c_start(i2c);
	
	i2c_add(i2c, 0x78,0); //0x78 is the primary address
	
	i2c_data(i2c,0x40); // Control function for a data
	i2c_data(i2c,data);
	
	i2c_stop(i2c);
}
// oled_pos()

void oled_pos(char i2c,char Ypos, char Xpos)
{
	oled_cmd_1byte(i2c,0x00 + (0x0F & Xpos));
	oled_cmd_1byte(i2c,0x10 + (0x0F & (Xpos>>4)));
	oled_cmd_1byte(i2c,0xB0 + Ypos);
}

// oled_blank()
void oled_blank(char i2c)
{
	int i,j;
	oled_pos(i2c,0, 0);
	for(i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{
			oled_data(i2c,0x00);
		}
	}
	oled_pos(i2c,0, 0);
}

//oled_print
void oled_print(char i2c,char str[])
{
	int i,j;
	i=0;
	while(str[i])
	{
		for(j=0;j<5;j++)
		{
			oled_data(i2c,ASCII[(str[i]-32)][j]);
		}
		i++;
	}
}

//oled_msg
void oled_msg(char i2c,char Ypos, char Xpos,char str[])
{
	oled_pos(i2c,Ypos,Xpos);
	oled_print(i2c,str);
}
