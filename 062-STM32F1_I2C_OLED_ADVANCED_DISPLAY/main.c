#include "systick_time.h"
#include "i2c_drive.h"
#include "oled_drive.h"

unsigned char oled_buffer[8][128];

int main(void)
{
	int i,j;
	systick_init();
	oled_init_64(2);
	
		
	oled_blank(2);
	oled_msg(2,3,30,"Hello WeeW");
	DelayMs(2000);
	
	// Start of the Nokia 5110 Code (to be converted)

	ImgType weew_pic = {.h = weew_stack_rows, .w = weew_stack_cols, .x_pos = 25, .y_pos =2, .bit_y_pos = 0};
	weew_pic.image[0] = weew_stack;
	
	ImgType goku = {.h = Goku2_rows, .w = Goku2_cols, .x_pos = 0, .y_pos =0};
	goku.image[0] = Goku2;


	ImgType walkmen = {.h = walkmen_4_rows, .w = walkmen_4_cols, .x_pos = 0, .y_pos =0};
	walkmen.image[0] = walkmen_0;
	walkmen.image[1] = walkmen_1;
	walkmen.image[2] = walkmen_2;
	walkmen.image[3] = walkmen_3;
	walkmen.image[4] = walkmen_4;

	/*
	oled_blank(2);
	clear_buffer(oled_buffer);
	update_buffer(weew_pic, 0, oled_buffer);
	update_str_buffer(7, 35," Hello WeeW ",oled_buffer);
	print_buffer(2,oled_buffer);
	DelayMs(20000);
	*/
	

	clear_buffer(oled_buffer);
	update_buffer(goku, 0, oled_buffer);
	print_buffer(2,oled_buffer);
	DelayMs(1000);

		for(i=0;i<50;i++)
	{
	weew_pic.x_pos = 3*i;
	weew_pic.bit_y_pos = 2*i;
	clear_buffer(oled_buffer);
	update_buffer_bit(weew_pic, 0, oled_buffer);
	print_buffer(2,oled_buffer);
		DelayMs(50);
	}
	
	for(i=50;i>0;i--)
	{
	weew_pic.x_pos = 3*i;
	weew_pic.bit_y_pos = 2*i;
	clear_buffer(oled_buffer);
	update_buffer_bit(weew_pic, 0, oled_buffer);
	print_buffer(2,oled_buffer);
		DelayMs(50);
	}
	
	while(1)
	{
		for (i=0;i<83;i++)
		{
			walkmen.x_pos = i;
		if(i== 40)
		{
			clear_buffer(oled_buffer);
			update_buffer(walkmen, 4, oled_buffer);
			update_str_buffer(5, 15,"** Just WeeW **",oled_buffer);
			print_buffer(2,oled_buffer);
			DelayMs(1000);
		}else{
		for(j=0;j<4;j++)
		{
			clear_buffer(oled_buffer);
			update_buffer(walkmen, j, oled_buffer);
			print_buffer(2,oled_buffer);
			DelayMs(100);
		}
	}
		}
	}
	
}

