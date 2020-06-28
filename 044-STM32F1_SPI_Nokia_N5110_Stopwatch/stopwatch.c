#include "stopwatch.h"

void sw_init(void)
{
	systick_init();
n5110_init(1);
n5110_clear();
	


	//initialize PIN
init_GP(PB,0,OUT50,O_GP_PP);
init_GP(PB,1,OUT50,O_GP_PP);

	//initialize PIN Interrup routine
	__disable_irq();
	AFIO->EXTICR[0] |= 0x11;
	EXTI->IMR |= 0x3;
	EXTI->RTSR |= 0x3;
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	__enable_irq();

	
	// initialize Systick interrup
	systick_int_start();

	
	// Initialize PC13 for test 
	init_GP(PC,13,OUT50,O_GP_PP);
}


// Reset sw

void sw_reset(unsigned short * sw_rst, unsigned long * millis)
{
			*sw_rst = 0;
			systick_init();
			*millis = 0;
			n5110_clear();
			n5110_add_print(2,25,"00:00:0");
			n5110_add_print(5,0,"START");
}

void sw_stop(unsigned int * counter)
{
	systick_init();
			*counter = 0;
			n5110_add_print(5,0,"START");
}

void sw_start_func(unsigned long * millis, unsigned int * counter, char number[], char time[])
{
unsigned int milli = 0;
unsigned int seconds  = 0;
unsigned int second  = 0;
unsigned int minute  = 0;
	
	n5110_add_print(5,0,"STOP ");
			n5110_add_print(5,55,"RESET");
			
			*millis += *counter;
			*counter =0;
			
			seconds = *millis/10;
			milli = *millis % 10;
			second = seconds % 60;
			minute = seconds / 60;
			
			digit_check(minute,number,time);
			digit_check(second,number,time);
			int2char(milli,number);
			Concatstr(time,number);
			str_empty(number);
			
			if(minute>59)
			{
				n5110_add_print(2,25,"00:00:0");
				*millis = 0;
			}
			else
			{
				n5110_add_print(2,25,time);
			}
			str_empty(time);
}


void digit_check(unsigned int time_cst, char number[], char time[])
{
	int digit;
			int2char(time_cst,number);
			digit = len_str(number)+1;
			if(digit==1)
			{
				Concatstr(time,"0");
				Concatstr(time,number);
			}
			else
			{
				Concatstr(time,number);
			}
			str_empty(number);
			Concatstr(time,":");
}



