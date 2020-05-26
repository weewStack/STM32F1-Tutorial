#include "stm32f10x.h" 
#include "systick_time.h"
#include "gp_drive.h" 
#include "SPI_drive.h"
#include "n5110_drive.h"

/*
Pin setup

SPI - 1
--> 
PA0 -->RST
PA1 --> DC
PA2 -->Screen Light
PA4 --> SS
PA5 --> SCLK
PA7 --> MOSI

3.3V --> Vcc
G --> Grd
*/

unsigned char n5110_buffer[6][84];


int main(void)
{
	int i,j;
systick_init();
n5110_init(1);

ImgType weew_pic = {.h = weew_stack_rows, .w = weew_stack_cols, .x_pos = 0, .y_pos =0};

weew_pic.image[0] = weew_stack;


ImgType walkmen = {.h = walkmen_4_rows, .w = walkmen_4_cols, .x_pos = 0, .y_pos =0};

walkmen.image[0] = walkmen_0;
walkmen.image[1] = walkmen_1;
walkmen.image[2] = walkmen_2;
walkmen.image[3] = walkmen_3;
walkmen.image[4] = walkmen_4;

n5110_clear();
clear_buffer(n5110_buffer);
update_buffer(weew_pic, 0, n5110_buffer);
update_str_buffer(5, 15," Hello WeeW ",n5110_buffer);
print_buffer(n5110_buffer);
DelayMs(3000);

	while(1)
	{
		for (i=0;i<83;i++)
		{
			walkmen.x_pos = i;
		if(i== 40)
		{
			clear_buffer(n5110_buffer);
			update_buffer(walkmen, 4, n5110_buffer);
			update_str_buffer(5, 15,"** Just WeeW **",n5110_buffer);
			print_buffer(n5110_buffer);
			DelayMs(1000);
		}else{
		for(j=0;j<4;j++)
		{
			clear_buffer(n5110_buffer);
			update_buffer(walkmen, j, n5110_buffer);
			print_buffer(n5110_buffer);
			DelayMs(100);
		}
	}
		//toggle_GP(PA,2);
		}
	}
	
}
