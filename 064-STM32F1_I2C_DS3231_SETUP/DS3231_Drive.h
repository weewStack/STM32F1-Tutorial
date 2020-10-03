#include "i2c_drive.h"
#include "help_func.h"

char DS3231_converter(char date);
void DS3231_update_sec(char i2c,char sec);
void DS3231_update_min(char i2c,char min);
void DS3231_update_hrs(char i2c,char hrs);
void DS3231_update_day(char i2c,char date);
void DS3231_update_month(char i2c,char month);
void DS3231_update_yr(char i2c,char yr);
void DS3231_update_time(char i2c,char hrs,char min,char sec);
void DS3231_update_date(char i2c,char yr,char month,char day);
void DS3231_update_date_time(char i2c,char yr,char month,char day,char hrs,char min,char sec);
char DS3231_reverter(char time);
void DS3231_get_time(char i2c,char * str);
void int2time(char time,char str[]);
void int2date(char time,char str[]);

