
#include "timer_drive.h"
#include "adc_drive.h"

//###########################################
/*

PA0 -> TIM2_CH1
PA1 -> TIM2_CH2
PA2 -> TIM2_CH3
PA3 -> TIM2_CH4

PA6 -> TIM3_CH1
PA7 -> TIM3_CH2
PB0 -> TIM3_CH3
PB1 -> TIM3_CH4

PA8 -> TIM1_CH1
PA9 -> TIM1_CH2
PA10 -> TIM1_CH3
PA11 -> TIM1_CH4


void TIM1_UP_IRQHandler(){}
void TIM2_IRQHandler(){}
void TIM3_IRQHandler(){}
void TIM4_IRQHandler(){}


*/




int analog_rx = 0;
int avg_analog_rx = 0;
int i=0;



int main(void)
{
	/*
	RCC->APB2ENR |= 0x0800;
	
	init_GP(PA,8,OUT50,O_AF_PP);
	init_GP(PA,9,OUT50,O_AF_PP);
	init_GP(PA,10,OUT50,O_AF_PP);
	init_GP(PA,11,OUT50,O_AF_PP);
	
	TIM1->PSC = (72-1);
	TIM1->ARR = 60000;
	TIM1->CNT = 0;
	
	TIM1->CCMR1 |= 0x60;
	TIM1->CCMR1 |= 0x6000;
	TIM1->CCMR2 |= 0x60;
	TIM1->CCMR2 |= 0x6000;
	
	TIM1->CCER |= 1;
	TIM1->CCER |= 0x10;
	TIM1->CCER |= 0x100;
	TIM1->CCER |= 0x1000;
	
	TIM1->BDTR |= 0x8000;
	
	TIM1->CCR1 = 15000;
	TIM1->CCR2 = 30000;
	TIM1->CCR3 = 45000;
	TIM1->CCR4 = 60000;
	
	TIM1->CR1 |= 1;
	*/
	
	systick_init(); // Initialize the delay function
	adc_init(adc1, PA, 1);
	
	timer_pwm_milli(PA, 8, 1000, 0);
	timer_pwm_milli(PA, 9, 1000, 250);
	timer_pwm_milli(PA, 10, 1000, 500);
	timer_pwm_milli(PA, 11, 1000, 750);
while(1)
	{	
		analog_rx = 0;
		for(i=0;i<50;i++)
		{
			analog_rx = analog_rx + adc_rx(adc1, PA, 1);
		}
		avg_analog_rx = (analog_rx/50);
		
		
		timer_pwm_milli(PA, 8, 1000, avg_analog_rx);
		
	}
}


