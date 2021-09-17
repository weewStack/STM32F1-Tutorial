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
char adc_check(char adc)
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

void adc_irq(char adc, char port, char pin)
{
	adc_init(adc, port, pin);// Initialize the ADC: adc_init(ADC1 or ADC2, Port, Pin)
	if(adc == 1)
	{
		ADC1->CR1 |= 0x20; // Setting the Interrupt
		ADC1->CR1 |= 0x40;
	}
	else if(adc == 2)
	{
		ADC2->CR1 |= 0x20; // Setting the Interrupt
		ADC2->CR1 |= 0x40;
	}
	
	__disable_irq();
	NVIC_EnableIRQ(ADC1_2_IRQn);
	__enable_irq();
}

void adc_wd(char adc, char port, char pin, short htr, short ltr)
{
		adc_init(adc, port, pin);// Initialize the ADC: adc_init(ADC1 or ADC2, Port, Pin)

		if(adc == 1)
	{
		ADC1->CR1 |= 0x800000; // Enable the watchdog
		ADC1->HTR = htr;
		ADC1->LTR = ltr;
		ADC1->CR1 |= 0x40;
	}
	else if(adc == 2)
	{
		ADC2->CR1 |= 0x800000; // Enable the watchdog
		ADC2->HTR = htr;
		ADC2->LTR = ltr;
		ADC2->CR1 |= 0x40;
	}
	
	__disable_irq();
	NVIC_EnableIRQ(ADC1_2_IRQn);
	__enable_irq();
}

void adc_multi_ch_init(char adc, char channels, char * adc_channels)
{
	char i = 0;
	//Initiate the pins
	for(i=0;i< channels;i++)
	{
		if(adc_channels[i]<8)
		{
			init_GP(PA,adc_channels[i],IN,I_AN);
		}
		else if(adc_channels[i]<10)
		{
			init_GP(PB,adc_channels[i]-8,IN,I_AN);
		}
		else if(adc_channels[i]<16)
		{
			init_GP(PC,adc_channels[i]-10,IN,I_AN);
		}
	}
	if(adc == 1)
	{
	//Setup the control registers
	RCC->APB2ENR |= 0x201;
	ADC1->CR2 = 0;
	ADC1->CR2 |= 1;
	DelayMs(100);
	ADC1->SQR3 = adc_channels[1];
	ADC1->CR2 |= 2; //Continous readings
	ADC1->CR2 |= 1; //starting the conversion
	}
	else if(adc == 2) {
	//Setup the control registers
	RCC->APB2ENR |= 0x401;
	ADC2->CR2 = 0;
	ADC2->CR2 |= 1;
	DelayMs(100);
	ADC2->SQR3 = adc_channels[1];
	ADC2->CR2 |= 2; //Continous readings
	ADC2->CR2 |= 1; //starting the conversion
	
	}
}

void adc_multi_ch_rx(char adc, char channels, char * adc_channels, int * analog_rx)
{
	char i = 0;
	int temp_rx = 0;
	if(adc==1)
	{
	while(1)
		{
			if(adc_check(adc1))
			{
				temp_rx = ADC1->DR;
				//analog_rx[i] = (temp_rx  *1000) / 0xFFF;
				analog_rx[i] = temp_rx ;
				i++;
				if(i == channels)
				{
					i = 0;
					ADC1->SQR3 = adc_channels[i];
					break;
				}
				else
				{
					ADC1->SQR3 = adc_channels[i];
				}
			}
			
	}
}
	else if(adc==2)
	{
	while(1)
		{
			if(adc_check(adc1))
			{
				temp_rx = ADC2->DR;
				//analog_rx[i] = (temp_rx  *1000) / 0xFFF;
				analog_rx[i] = temp_rx ;
				i++;
				if(i == channels)
			{
				i = 0;
				ADC2->SQR3 = adc_channels[i];
				break;
			}
			else
			{
				ADC2->SQR3 = adc_channels[i];
			}
			}
			
	}
}
}
