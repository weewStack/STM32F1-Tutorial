#include "adc_drive.h"
#include "help_func.h"
#include "uart_drive.h"

char num[10];
int analog_rx = 0;
int main(void)
{
// Initialize the ADC
	systick_init();
	UART_init(2,115200);
	adc_init(adc1, PA, 0);
	adc_init(adc2, PA, 1);
while(1)
{
	if(adc_check(adc1, PA, 0))
	{
		analog_rx = adc_rx(adc1, PA, 0) * 330;
		analog_rx = analog_rx / 100;
		UART_SEND(2,"ADC1: ");
		int2char(analog_rx,num);
		UART_SEND(2,num);
		str_empty(num);
		
		UART_SEND(2," ADC2: ");
		analog_rx = adc_rx(adc2, PA, 1) * 330;
		analog_rx = analog_rx / 100;
		int2char(analog_rx,num);
		UART_SEND(2,num);
		str_empty(num);
		UART_TX(2,'\n');
	}
}
}
