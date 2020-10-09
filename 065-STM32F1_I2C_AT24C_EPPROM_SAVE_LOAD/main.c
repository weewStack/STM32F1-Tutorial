#include "systick_time.h"
#include "AT24C_Drive.h"
#include "uart_drive.h"

/*
I2C2
PB10 -> SCL
PB11 -> SDA

I2C1
PB6 -> SCL
PB7 -> SDA


*/
char save[12] = "Hellow WeeW\n";
char load[12];
int main(void)
{
	systick_init();
	UART_init(2,115200);
	i2c_init(2,i2c_FM);
	AT24C_save_page(2,0,save,12);

	AT24C_load_page(2,0,load,12);
	UART_SEND(2,load);
	
	
	while(1)
	{
		
	}
	
}


