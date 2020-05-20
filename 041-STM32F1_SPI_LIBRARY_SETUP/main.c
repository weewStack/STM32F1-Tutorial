#include "stm32f10x.h" 
#include "systick_time.h"
#include "gp_drive.h" 
#include "SPI_drive.h"



int main(void)
{
systick_init();

spi_init(1);

	while(1)
	{
		//Sending some data
		DelayMs(50);
		spi_tx(1,'W');
		spi_tx(1,'e');
		spi_tx(1,'e');
		spi_tx(1,'W');
		
		spi_msg(1, "WeeW");
	}
	
}
