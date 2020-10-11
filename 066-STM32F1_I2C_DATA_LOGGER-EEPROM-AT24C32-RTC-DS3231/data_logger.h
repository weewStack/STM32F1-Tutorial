#include "systick_time.h"
#include "AT24C_Drive.h"
#include "DS3231_Drive.h"

enum {
 Version = 0,
 Memory  = 1,
 Word_size = 3,
 Rec_size = 4,
 Rec_tot = 5,
 Rec_Add = 7
};



char Get_byte(char byte_pos,long num);
short Get_short(char i2c,short start_address);
void ATC24_memo_update_2byte(char i2c,short address,int val);
void logger_init(char i2c);
char logger_rec(char i2c,char * data);
char logger_read(char i2c,short record_number, char * data); 
