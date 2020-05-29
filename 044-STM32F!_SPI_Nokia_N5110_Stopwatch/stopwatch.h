#include "stm32f10x.h" 
#include "systick_time.h"
#include "gp_drive.h" 
#include "SPI_drive.h"
#include "n5110_drive.h"
#include "help_func.h"


void sw_init(void);
void sw_reset(unsigned short * sw_rst, unsigned long * millis);
void sw_stop(unsigned int * counter);
void digit_check(unsigned int time_cst, char number[], char time[]);
void sw_start_func(unsigned long * millis, unsigned int * counter, char number[], char time[]);
