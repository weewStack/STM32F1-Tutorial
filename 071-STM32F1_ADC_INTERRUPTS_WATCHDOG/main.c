#include "adc_drive.h"
#include "msg_drive.h"

/*
PA0 -> ADC12_IN0
PA1 -> ADC12_IN1
PA2 -> ADC12_IN2
PA3 -> ADC12_IN3
PA4 -> ADC12_IN4
PA5 -> ADC12_IN5
PA6 -> ADC12_IN6
PA7 -> ADC12_IN7
PB0 -> ADC12_IN8
PB1 -> ADC12_IN9

PC0 -> ADC12_IN10
PC1 -> ADC12_IN11
PC2 -> ADC12_IN12
PC3 -> ADC12_IN13
PC4 -> ADC12_IN14
PC5 -> ADC12_IN15

ADC12_IN16 input channel which is used to convert the sensor output voltage into a digital value.


*/
int analog_rx = 0;
int adc1_int = 0;
int adc2_int = 0;
int adc1_wd = 1;
int adc2_wd = 0;
char adc1_flag = 0;
char adc2_flag = 0;
int main(void)
{
	Digital_Output(PC,13);
	systick_init(); // Initialize the delay function
	UART_init(2,115200); // Initialize the Uart communication : 
	adc_init(adc1, PA, 0);// Initialize the ADC: adc_init(ADC1 or ADC2, Port, Pin)
	//ADC1->CR1 |= 0x20; // Setting the Interrupt
	ADC1->CR1 |= 0x800000; // Enable the watchdog
	ADC1->HTR = 0xD00;
	ADC1->LTR = 0x200;
	ADC1->CR1 |= 0x40;
	
	__disable_irq();
	NVIC_EnableIRQ(ADC1_2_IRQn);
	__enable_irq();

while(1)
	{
		if(adc1_flag)
		{
			W_GP(PC,13,LOW);
			adc1_flag = 0;
			ADC1->CR1 |= 0x40;
			analog_rx = (analog_rx *1000)/ 0xfff;
			basic_msg(2,analog_rx);
		}
		W_GP(PC,13,HIGH);
	}
}
void ADC1_2_IRQHandler()
{
	if(adc1_int)
	{
		ADC1->CR1 &= ~0x20;
		analog_rx = ADC1->DR;
		adc1_flag = 1;
	}
	if(adc2_int)
	{
		ADC2->CR1 &= ~0x20;
		analog_rx = ADC2->DR;
		adc2_flag = 1;
	}
	if(adc1_wd)
	{
		ADC1->CR1 &= ~0x40;
		ADC1->SR &= ~0x01;
		analog_rx = ADC1->DR;
		adc1_flag = 1;
	}
	if(adc2_wd)
	{
		ADC2->CR1 &= ~0x40;
		ADC2->SR &= ~0x01;
		analog_rx = ADC2->DR;
		adc2_flag = 1;
	}
}

