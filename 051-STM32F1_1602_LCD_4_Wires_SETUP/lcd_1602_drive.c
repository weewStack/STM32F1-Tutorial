#include "lcd_1602_drive.h"



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
