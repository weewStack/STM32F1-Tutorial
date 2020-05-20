/*
//// Library used to setup GPIOs for more details, visit:

https://youtu.be/e0JfbZEditA

*/



#include "stm32f10x.h"    
#include "gp_drive.h"


void init_GP(unsigned short PORT,unsigned short PIN,unsigned short DIR,unsigned short OPT)
{
	volatile unsigned long * CR;
	unsigned short tPin = PIN;
	unsigned short offset = 0x00;
	
		if(PIN > 7)
		{
			tPin -=8;
			offset = 0x01;
		}
		

	if(PORT == 1)
		{
			RCC_APBENR |= 0x4;

			CR = (volatile unsigned long *)(&GPIO_A + offset);
		}
	else if(PORT == 2)
		{
		RCC_APBENR |= 0x8;
		CR = (volatile unsigned long *)(&GPIO_B+ offset);
		}
	else if(PORT == 3)
		{
		RCC_APBENR |= 0x10;
		CR = (volatile unsigned long *)(&GPIO_C + offset);
		}

	*CR &= ~(0xf<<(tPin)*4);
	*CR |= ((DIR<<(tPin*4)) | (OPT<<(tPin*4+2)));
}

int R_GP(unsigned short PORT,unsigned short pin)
{
	volatile unsigned long * IDR;
	unsigned long offset = 0x02;
	int state;
	
	if(PORT == 1)
		{
			IDR = (volatile unsigned long *)(&GPIO_A + offset);
		}
	else if(PORT == 2)
		{
		IDR = (volatile unsigned long *)(&GPIO_B+ offset);
		}
	else if(PORT == 3)
		{
		IDR = (volatile unsigned long *)(&GPIO_C+ offset);
		}
		state =  ((*IDR & (1<<pin))>>pin)  ;
		
		return state;
}

void W_GP(unsigned short PORT,unsigned short pin, unsigned short STATUS)
{
	volatile unsigned long * ODR;
	unsigned long offset = 0x03;
	if(PORT == 1)
		{
			ODR = (volatile unsigned long *)(&GPIO_A + offset);
		}
	else if(PORT == 2)
		{
		ODR = (volatile unsigned long *)(&GPIO_B+ offset);
		}
	else if(PORT == 3)
		{
		ODR = (volatile unsigned long *)(&GPIO_C+ offset);
		}
	STATUS ? (*ODR |= (STATUS<<pin)) : (*ODR &= ~(1<<pin));
}

void toggle_GP(unsigned short Port,unsigned short pin)
{
	if(R_GP(Port,pin))
		{
			W_GP(Port,pin,0);
		}
	else
		{
			W_GP(Port,pin,1);
		}
}





void PINc(unsigned short pin, unsigned short STATUS)
{
	STATUS ? (GPIOC->ODR |= (STATUS<<pin)) : (GPIOC->ODR &= ~(1<<pin));
}

void B_init(void)
{
	init_GP(PC,13,OUT50,O_GP_PP);
}

void BLED(unsigned short state)
{
	W_GP(PC,13,state);
}
