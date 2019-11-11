#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"
void Delays(int time);

int main(void)
{
	init_GP(PA,0,IN,I_PP);
	init_GP(PC,13,OUT50, O_GP_PP);
	
	while(1)
	{
		if(R_GP(PA,0)==1) /// Checking status of PIN ! portA 
		{
			Delays(10);
			toggle_GP(PC,13); /// Toggle the PIN state
			Delays(10);
		}
		else
		{
			W_GP(PC,13,1); /// Set the PIN 13 port C high
		}
	}
	
}


void Delays(int time) /// Random delay function
{
	int t;
	for(;time>0;time--)
	{
	 for(t=0;t<100000;t++)
		{}
	}
}
