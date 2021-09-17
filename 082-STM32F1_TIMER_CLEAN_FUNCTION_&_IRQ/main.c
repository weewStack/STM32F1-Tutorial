#include "gp_drive.h"
#include "timer_drive.h"

//###########################################
/*
void TIM1_UP_IRQHandler(){}
void TIM2_IRQHandler(){}
void TIM3_IRQHandler(){}
void TIM4_IRQHandler(){}


*/









int main(void)
{
	timer_irq_millis_start(T1,500);
	Digital_Output(PA,8);
	Digital_Output(PA,9);
		
while(1)
	{
		
		
		
		TDelay_Milli(500);
		toggle_GP(PA,8);
		
	}
}

void TIM1_UP_IRQHandler(){
	timer_irq_Rflag(T1);
	toggle_GP(PA,9);
}
