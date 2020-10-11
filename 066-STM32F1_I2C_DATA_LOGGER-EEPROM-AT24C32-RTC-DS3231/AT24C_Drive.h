#include "i2c_drive.h"
#include "help_func.h"
#include "systick_time.h"

void AT24C_save_byte(char i2c,short reg,char data);
void AT24C_save_page(char i2c,short reg,char * str,char data_len);
char AT24C_load_byte(char i2c,short reg);
void AT24C_load_page(char i2c,short reg,char * str,char data_len);
