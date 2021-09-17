
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




int analog_rx[2];
int avg_analog_rx[2];
int i=0;


int deg =0;
int speed =0;


int main(void)
{
	
	systick_init(); // Initialize the delay function
	adc_init(adc1, PA, 1);
	adc_init(adc2, PA, 2);

while(1)
	{	
		analog_rx[0] = 0;
		analog_rx[1] = 0;
		for(i=0;i<50;i++)
		{
			analog_rx[0] = analog_rx[0] + adc_rx(adc1, PA, 1);
			analog_rx[1] = analog_rx[1] + adc_rx(adc2, PA, 2);
		}
		
		
		avg_analog_rx[0]  = ((analog_rx[0]/50)*180)/4000;
		
		servo_180_deg(PA,8, avg_analog_rx[0]);
		
		
		avg_analog_rx[1]  = ((analog_rx[1]/50)*100)/4000;
		if(avg_analog_rx[0]>90)
		{
			servo_speed_CCD(PA, 9, avg_analog_rx[1]);
		}
		else
		{
			servo_speed_CD(PA, 9, avg_analog_rx[1]);
		}
		

	}
}


