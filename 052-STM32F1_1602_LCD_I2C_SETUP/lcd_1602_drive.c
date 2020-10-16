#include "lcd_1602_drive.h"

/*
PCF8574 Pin connection with LCD

P0-> RS (LCD cmd wire)
P1-> RW (LCD cmd wire)
P2-> E (LCD cmd wire)
P3-> Screen light --> Must always be 1
P4-> D4 (LCD Data wire)
P5-> D5 (LCD Data wire)
P6-> D6 (LCD Data wire)
P7-> D7 (LCD Data wire)


*/

void pin_output(unsigned char start, unsigned char end)
{
char i;
	for(i=start;i<end;i++)
	{
		Digital_Output(PA,i);
	}
}

void lcd_rs(unsigned char LOW_HIGH)
{
	W_GP(PA,8,LOW_HIGH);
}
void lcd_rw(unsigned char LOW_HIGH)
{
	W_GP(PA,9,LOW_HIGH);
}
void lcd_e(unsigned char LOW_HIGH)
{
	W_GP(PA,10,LOW_HIGH);
}

void lcd_data(unsigned char data)
{
	pin_output(4,7);
	lcd_rs(HIGH);
	lcd_rw(LOW);
	DelayUs(10);
	lcd_e(HIGH);
	DelayUs(5);
	GPIOA->ODR &= 0xff0f;
	GPIOA->ODR |= (data & 0x00f0);
	DelayUs(10);
	lcd_e(LOW);
	
	DelayUs(20);
	
	lcd_e(HIGH);
	DelayUs(5);
	GPIOA->ODR &= 0xff0f;
	GPIOA->ODR |= ((data << 4) & 0x00f0);
	DelayUs(10);
	lcd_e(LOW);
}
void lcd_cmd(unsigned char data)
{
	pin_output(0,11);
	lcd_rs(LOW);
	lcd_rw(LOW);
	DelayUs(10);
	lcd_e(HIGH);
	DelayUs(5);
	GPIOA->ODR &= 0xff0f;
	GPIOA->ODR |= (data & 0x00f0);
	DelayUs(10);
	lcd_e(LOW);
	
	DelayUs(20);
	
	lcd_e(HIGH);
	DelayUs(5);
	GPIOA->ODR &= 0xff0f;
	GPIOA->ODR |= ((data << 4) & 0x00f0);
	DelayUs(10);
	lcd_e(LOW);
}

void lcd_init(void)
{
	pin_output(4,11);
	DelayMs(20);
	lcd_rs(LOW);
	lcd_rw(LOW);
	DelayUs(10);
	lcd_e(HIGH);
	DelayUs(5);
	GPIOA->ODR &= 0xff0f;
	GPIOA->ODR |= 0x30; // 8 bit communication mode 
	DelayUs(10);
	lcd_e(LOW);
	
	DelayMs(10);
	
	lcd_rs(LOW);
	lcd_rw(LOW);
	DelayUs(10);
	lcd_e(HIGH);
	DelayUs(5);
	GPIOA->ODR &= 0xff0f;
	GPIOA->ODR |= 0x30; // 8 bit communication mode 
	DelayUs(10);
	lcd_e(LOW);
	
	DelayMs(1);
	
	lcd_rs(LOW);
	lcd_rw(LOW);
	DelayUs(10);
	lcd_e(HIGH);
	DelayUs(5);
	GPIOA->ODR &= 0xff0f;
	GPIOA->ODR |= 0x30; // 8 bit communication mode 
	DelayUs(10);
	lcd_e(LOW);
	
	DelayMs(1);
	
	lcd_rs(LOW);
	lcd_rw(LOW);
	DelayUs(10);
	lcd_e(HIGH);
	DelayUs(5);
	GPIOA->ODR &= 0xff0f;
	GPIOA->ODR |= 0x20; // 4 bit communication mode 
	DelayUs(10);
	lcd_e(LOW);
	
	
	lcd_cmd(0x2C); // 4 bit communication mode / 2 lines
	DelayMs(5);
	lcd_cmd(0x0C); // Display ON
	DelayMs(5);
	lcd_cmd(0x01); // Clear Display
	DelayMs(5);
	lcd_cmd(0x02); // Get back to initial address
	DelayMs(5);
}
void lcd_send( char str[])
{
	int i = 0;
		while(str[i])
		{
			lcd_data(str[i]);
			i++;
			DelayUs(100);
		}

}

void lcd_msg(unsigned char line_1_2, unsigned char pos_0_16, char msg[])
{
	short pos = 0;
	if(line_1_2==1)
	{
		pos = 0;
	}
	else if(line_1_2==2)
	{
		pos = 0x40;
	}
	lcd_cmd(0x80 +pos + pos_0_16);
	DelayUs(100);
	lcd_send(msg);
}
// I2c adjust 4 wire data tx
void lcd_i2c_data(char i2c,unsigned char data)
{
	
	//lcd_rs(HIGH);
	//lcd_rw(LOW);
	PCF8574_tx_byte(i2c,0x09);
	DelayUs(10);
	//lcd_e(HIGH);
	PCF8574_tx_byte(i2c,0x0D);
	DelayUs(5);
	//GPIOA->ODR &= 0xff0f;
	//GPIOA->ODR |= (data & 0x00f0);
	PCF8574_tx_byte(i2c, ((data & 0x00f0) | 0x0D));
	DelayUs(10);
	//lcd_e(LOW);
	PCF8574_tx_byte(i2c, ((data & 0x00f0) | 0x09));
	
	DelayUs(20);
	
	//lcd_e(HIGH);
	PCF8574_tx_byte(i2c,0x0D);
	DelayUs(5);
	//GPIOA->ODR &= 0xff0f;
	//GPIOA->ODR |= ((data << 4) & 0x00f0);
	PCF8574_tx_byte(i2c, (((data << 4) & 0x00f0) | 0x0D));
	DelayUs(10);
	//lcd_e(LOW);
	PCF8574_tx_byte(i2c, (((data << 4) & 0x00f0) | 0x09));
}


// I2c adjust 4 wire cmd tx
void lcd_i2c_cmd(char i2c,unsigned char data)
{
	
	//lcd_rs(LOW);
	//lcd_rw(LOW);
	PCF8574_tx_byte(i2c,0x08);
	DelayUs(10);
	//lcd_e(HIGH);
	PCF8574_tx_byte(i2c,0x0C);
	DelayUs(5);
	//GPIOA->ODR &= 0xff0f;
	//GPIOA->ODR |= (data & 0x00f0);
	PCF8574_tx_byte(i2c, ((data & 0x00f0) | 0x0C));
	DelayUs(10);
	//lcd_e(LOW);
	PCF8574_tx_byte(i2c, ((data & 0x00f0) | 0x08));
	DelayUs(20);
	
	//lcd_e(HIGH);
	PCF8574_tx_byte(i2c,0x0C);
	DelayUs(5);
	//GPIOA->ODR &= 0xff0f;
	//GPIOA->ODR |= ((data << 4) & 0x00f0);
	PCF8574_tx_byte(i2c, (((data << 4) & 0x00f0) | 0x0C));
	DelayUs(10);
	//lcd_e(LOW);
	PCF8574_tx_byte(i2c, (((data << 4) & 0x00f0) | 0x08));
}

// // I2c adjust 4 wire init
void lcd_i2c_init(char i2c)
{
  i2c_init(i2c, i2c_FM);
	DelayMs(20);
	//lcd_rs(LOW);
	//lcd_rw(LOW);
	PCF8574_tx_byte(i2c,0x08);
	DelayUs(10);
	//lcd_e(HIGH);
	PCF8574_tx_byte(i2c,0x0C);
	DelayUs(5);
	//GPIOA->ODR &= 0xff0f;
	//GPIOA->ODR |= 0x30; // 8 bit communication mode 
	PCF8574_tx_byte(i2c,0x3C);
	DelayUs(10);
	//lcd_e(LOW);
	PCF8574_tx_byte(i2c,0x38);
	
	DelayMs(10);
	
	//lcd_rs(LOW);
	//lcd_rw(LOW);
	PCF8574_tx_byte(i2c,0x08);
	DelayUs(10);
	//lcd_e(HIGH);
	PCF8574_tx_byte(i2c,0x0C);
	DelayUs(5);
	//GPIOA->ODR &= 0xff0f;
	//GPIOA->ODR |= 0x30; // 8 bit communication mode 
	PCF8574_tx_byte(i2c,0x3C);
	DelayUs(10);
	//lcd_e(LOW);
	PCF8574_tx_byte(i2c,0x38);
	
	DelayMs(1);
	
	//lcd_rs(LOW);
	//lcd_rw(LOW);
	PCF8574_tx_byte(i2c,0x08);
	DelayUs(10);
	//lcd_e(HIGH);
	PCF8574_tx_byte(i2c,0x0C);
	DelayUs(5);
	//GPIOA->ODR &= 0xff0f;
	//GPIOA->ODR |= 0x30; // 8 bit communication mode 
	PCF8574_tx_byte(i2c,0x3C);
	DelayUs(10);
	//lcd_e(LOW);
	PCF8574_tx_byte(i2c,0x38);
	
	DelayMs(1);
	
	//lcd_rs(LOW);
	//lcd_rw(LOW);
	PCF8574_tx_byte(i2c,0x08);
	DelayUs(10);
	//lcd_e(HIGH);
	PCF8574_tx_byte(i2c,0x0C);
	DelayUs(5);
	//GPIOA->ODR &= 0xff0f;
	//GPIOA->ODR |= 0x20; // 4 bit communication mode 
	PCF8574_tx_byte(i2c,0x2C);
	DelayUs(10);
	//lcd_e(LOW);
	PCF8574_tx_byte(i2c,0x28);
	
	
	lcd_i2c_cmd(i2c,0x2C); // 4 bit communication mode / 2 lines
	DelayMs(5);
	lcd_i2c_cmd(i2c,0x0C); // Display ON
	DelayMs(5);
	lcd_i2c_cmd(i2c,0x01); // Clear Display
	DelayMs(5);
	lcd_i2c_cmd(i2c,0x02); // Get back to initial address
	DelayMs(5);
}
void lcd_i2c_send(char i2c, char str[])
{
	int i = 0;
		while(str[i])
		{
			lcd_i2c_data(i2c,str[i]);
			i++;
			DelayUs(100);
		}
}
void lcd_i2c_msg(char i2c,unsigned char line_1_2, unsigned char pos_0_16, char msg[])
{
	short pos = 0;
	if(line_1_2==1)
	{
		pos = 0;
	}
	else if(line_1_2==2)
	{
		pos = 0x40;
	}
	lcd_i2c_cmd(i2c,0x80 +pos + pos_0_16);
	DelayUs(100);
	lcd_i2c_send(i2c,msg);
}
void lcd_blank_1(char i2c)
{
	lcd_i2c_msg(i2c,1, 0, "                ");
}
void lcd_blank_2(char i2c)
{
	lcd_i2c_msg(i2c,2, 0, "                ");
}
void lcd_blank_12(char i2c)
{
	lcd_blank_1(i2c);
	lcd_blank_2(i2c);
}
