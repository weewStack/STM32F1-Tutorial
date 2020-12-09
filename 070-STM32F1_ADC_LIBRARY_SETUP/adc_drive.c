#include "adc_drive.h"

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


// Initializing the ADC for the STM32F1
char adc_init(char adc, short port, short pin)
{
	char channel;
	char result = 0;
	if(port == PA)
	{
		if(pin < 8)
		{
			result = 1;
			channel = pin;
		}
	}
	else if (port == PB)
	{
		if(pin<2)
		{
		result = 1;
		channel = 8 + pin;
		}
	}
	else if (port == PC)
	{
		if(pin<6)
		{
		result = 1;
		channel = 10 + pin;
		}
	}
	if(result)
	{
		init_GP(port,pin,IN,I_AN);
		if(adc == adc1)
		{
			RCC->APB2ENR |= 0x201;
			ADC1->CR2 = 0;
			ADC1->SQR3 = channel;
			ADC1->CR2 |= 1;
			DelayMs(100);
			ADC1->CR2 |= 1;
			ADC1->CR2 |= 2;
		}
		else if(adc == adc2)
		{
			RCC->APB2ENR |= 0x401;
			ADC2->CR2 = 0;
			ADC2->SQR3 = channel;
			ADC2->CR2 |= 1;
			DelayMs(100);
			ADC2->CR2 |= 1;
			ADC2->CR2 |= 2;
		}
	}
	return result ;
}

// Reading the flag that says the data is ready
char adc_check(char adc, short port, short pin)
{
	char check = 0;
	if(adc == adc1)
		{
			if(ADC1->SR & 2)
			{
				check  = 1;
			}
		}
		else if(adc == adc2)
		{
			if(ADC2->SR & 2)
			{
				check  = 1;
			}
		}
	
	
	return check;
}

// Reading the ADC value 
int adc_rx(char adc, short port, short pin)
{
	int result = 0;
	int data = 0;
	if(adc == adc1)
	{
		data = ADC1->DR;
	} 
	else if(adc == adc2)
	{
		data = ADC2->DR;
	}
	
	result = (data*1000)/0xfff;
	
	
	return result;
}


