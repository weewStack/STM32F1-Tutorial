#include "adc_drive.h"
#include "uart_drive.h"
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



char adc_channels[17] = {PB1,PA4,PA0,PA1};
int analog_rx[17];
char channels = 4;

int main(void)
{
	systick_init(); // Initialize the delay function
	UART_init(2,115200);
	adc_multi_ch_init(adc1, channels, adc_channels);
	
	
while(1)
	{
		adc_multi_ch_rx(adc1, channels, adc_channels, analog_rx);
		//UART_TX(2,'R');
	}
}


