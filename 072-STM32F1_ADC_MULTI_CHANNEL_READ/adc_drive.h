#include "gp_drive.h"
#include "stm32f10x.h" 
#include "systick_time.h"

#define adc1          1 
#define adc2          2

enum channels
{
	PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PB0,PB1,PC0,PC1,PC2,PC3,PC4,PC5,temp_sensor
};


char adc_init(char adc, short port, short pin);
char adc_check(char adc);
int adc_rx(char adc, short port, short pin);
void adc_irq(char adc, char port, char pin);
void adc_wd(char adc, char port, char pin, short htr, short ltr);
void adc_multi_ch_init(char adc, char channels, char * adc_channels);
void adc_multi_ch_rx(char adc, char channels, char * adc_channels, int * analog_rx);
