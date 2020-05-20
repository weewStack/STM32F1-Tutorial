#include "systick_time.h"
#include "gp_drive.h" 
#include "SPI_drive.h"
#include "n5110_drive.h"

void n5110_init(unsigned short spi)
{
// Setup RST pin
init_GP(PA,0,OUT50,O_GP_PP);
// Set RST High & Wait 10 ms set low & Wait 10 ms and set high 
W_GP(PA,0,HIGH);
DelayMs(10);
W_GP(PA,0,LOW); //Reset of screen
DelayMs(10);
W_GP(PA,0,HIGH);

// Setup DC pin & set low
init_GP(PA,1,OUT50,O_GP_PP);
W_GP(PA,1,LOW);
//Setup screenlight pin & test ligh with 1 sec high
init_GP(PA,2,OUT50,O_GP_PP);
W_GP(PA,2,HIGH);
DelayMs(1000);
W_GP(PA,2,LOW);
	
	
spi_init(spi);
	
	
//extended instruction set & set voltage
spi_tx(1,0x21);
spi_tx(1,0xC0);
	
//function set & display control set normal mode
spi_tx(1,0x20);
spi_tx(1,0x0C);

}

void n5110_print(short Ypos, short Xpos, char str[])
{
	int i,j;
	i = 0;
	//Cleaning the String
	n5110_pos(0,0);
	W_GP(PA,1,HIGH);
	for(j=0;j<504;j++)
		{
			spi_tx(1,0x00);
			
		}
	
	W_GP(PA,1,LOW);
	
//Writre String into n5110
	n5110_pos(Ypos,Xpos);
	W_GP(PA,1,HIGH);
	while(str[i])
	{
		for(j=0;j<5;j++)
		{
			
			spi_tx(1,ASCII[str[i]-32][j]);
			
		}
	
	i++;
	}
	W_GP(PA,1,LOW);





	//sring position
}

void n5110_pos(short Ypos,short Xpos)
{
	W_GP(PA,1,LOW);
	spi_tx(1,0x20);
	spi_tx(1,((0x40 | Ypos)));
	spi_tx(1,(0x80 | Xpos));
	

}
