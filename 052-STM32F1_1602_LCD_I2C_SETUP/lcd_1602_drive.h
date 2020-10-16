#include "gp_drive.h"
#include "systick_time.h"
#include "stm32f10x.h"
#include "PCF8574_drive.h"

void pin_output(unsigned char start, unsigned char end);
void lcd_rs(unsigned char LOW_HIGH);
void lcd_rw(unsigned char LOW_HIGH);
void lcd_e(unsigned char LOW_HIGH);
void lcd_data(unsigned char data);
void lcd_cmd(unsigned char data);
void lcd_init(void);
void lcd_send( char str[]);
void lcd_msg(unsigned char line_1_2, unsigned char pos_0_16, char msg[]);
void lcd_i2c_data(char i2c,unsigned char data);
void lcd_i2c_cmd(char i2c,unsigned char data);
void lcd_i2c_init(char i2c);
void lcd_i2c_send(char i2c, char str[]);
void lcd_i2c_msg(char i2c,unsigned char line_1_2, unsigned char pos_0_16, char msg[]);
void lcd_blank_1(char i2c);
void lcd_blank_2(char i2c);
void lcd_blank_12(char i2c);
