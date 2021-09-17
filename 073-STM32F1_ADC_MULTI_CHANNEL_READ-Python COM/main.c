#include "adc_drive.h"
#include "uart_drive.h"
#include "msg_drive.h"


//###########################################
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
char adc_channels[17] = {PB1,PA7,PA4,PA0};
int analog_rx[17];
char channels = 4;
//###########################################

//###########################################
/*
UART Manager
0- count
1- signal
2- Bridge
3- Terminator data load 1: Terminator / 0: Interrupt
4- terminator char 
5- time cst
6- time counter 

*/

unsigned short uart_2_mgr[7]={0,0,0,1,'\n',0,0};
char USART_2_msg[100];
//###########################################


//###########################################
char stream = 0;

//###########################################

int main(void)
{
	systick_init(); // Initialize the delay function
	//UART_init(2,256000);
	UART_init(2,115200);
	//UART_init(2,128000);
	//UART_init(2,57600);
	adc_multi_ch_init(adc1, channels, adc_channels);
	
	
while(1)
	{
		// Check if we get the data
		if(uart_2_mgr[1])
		{
			uart_2_mgr[1]=0;
			if (len_str(USART_2_msg) == 4)
			{
				if(USART_2_msg[1] == '?')
				{
					sync(2,channels);
					stream = 0;
				}
				if(USART_2_msg[1] == 'A')
				{
					stream = 1;
				}
				if(USART_2_msg[1] == 'S')
				{
					stream = 0;
				}
			}
			else
			{
				UART_SEND(2,"#E#\n");
			}
			str_empty(USART_2_msg);
		}
		
	if(stream)
	{
		//Read the Analog data
		adc_multi_ch_rx(adc1, channels, adc_channels, analog_rx);
		//Make the message and send the data
		make_msg_check(2,channels, analog_rx);
		

	}
	}
}


//UART interrupt to handle the reception incoming messages
void USART2_IRQHandler()
{
	UART_ISR(2,uart_2_mgr, USART_2_msg);
}
/*
void USART3_IRQHandler()
{
	UART_ISR(3,uart_3_mgr, USART_3_msg);
}
*/
