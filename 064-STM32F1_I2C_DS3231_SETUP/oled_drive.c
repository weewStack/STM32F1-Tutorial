#include "oled_drive.h"




//oled_cmd_1byte() 
void oled_cmd_1byte(char i2c,char data)
{
	
	i2c_start(i2c);
	
	i2c_add(i2c, 0x78,0); //0x78 is the primary address
	
	i2c_data(i2c,0x00); // Control function for a command
	i2c_data(i2c,data);
	
	i2c_stop(i2c);
}


//oled_cmd_2byte()
void oled_cmd_2byte(char i2c,char data[])
{
	int i = 0;
	
	i2c_start(i2c);
	
	i2c_add(i2c, 0x78,0); //0x78 is the primary address
	
	i2c_data(i2c,0x00); // Control function for a command
	for (i=0;i<2;i++)
	{
		i2c_data(i2c,data[i]);
	}
	
	
	i2c_stop(i2c);
}


//oled_init()
void oled_init(char i2c, char screen_size)
{
	i2c_init(i2c,i2c_FM);
	char cmd[] = {0xA8,0x3F};
	oled_cmd_2byte(i2c,cmd);
	char cmd1[] = {0xD3,0x00};
	oled_cmd_2byte(i2c,cmd1);
	
	oled_cmd_1byte(i2c,0x40);
	oled_cmd_1byte(i2c,0xA1);
	
	oled_cmd_1byte(i2c,0xC8);
	
	char cmd2[] = {0xDA,screen_size};
	oled_cmd_2byte(i2c,cmd2);
	
	char cmd3[] = {0x81,0x7F};
	oled_cmd_2byte(i2c,cmd3);
	
	oled_cmd_1byte(i2c,0xA4);
	oled_cmd_1byte(i2c,0xA6);
	
	char cmd4[] = {0xD5,0x80};
	oled_cmd_2byte(i2c,cmd4);
	
	char cmd5[] = {0x8D,0x14};
	oled_cmd_2byte(i2c,cmd5);
	
	oled_cmd_1byte(i2c,0xAF);
	
	char cmd6[] = {0x20,0x10};
	oled_cmd_2byte(i2c,cmd6);
	
}
void oled_init_64(char i2c)
{
	oled_init(i2c, 0x12);
}

void oled_init_32(char i2c)
{
	oled_init(i2c, 0x22);
}

//oled_data()
void oled_data(char i2c,char data)
{
	
	i2c_start(i2c);
	
	i2c_add(i2c, 0x78,0); //0x78 is the primary address
	
	i2c_data(i2c,0x40); // Control function for a data
	i2c_data(i2c,data);
	
	i2c_stop(i2c);
}
// oled_pos()

void oled_pos(char i2c,char Ypos, char Xpos)
{
	oled_cmd_1byte(i2c,0x00 + (0x0F & Xpos));
	oled_cmd_1byte(i2c,0x10 + (0x0F & (Xpos>>4)));
	oled_cmd_1byte(i2c,0xB0 + Ypos);
}

// oled_blank()
void oled_blank(char i2c)
{
	int i,j;
	oled_pos(i2c,0, 0);
	for(i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{
			oled_data(i2c,0x00);
		}
	}
	oled_pos(i2c,0, 0);
}

//oled_print
void oled_print(char i2c,char str[])
{
	int i,j;
	i=0;
	while(str[i])
	{
		for(j=0;j<5;j++)
		{
			oled_data(i2c,ASCII[(str[i]-32)][j]);
		}
		i++;
	}
}

//oled_msg
void oled_msg(char i2c,char Ypos, char Xpos,char str[])
{
	oled_pos(i2c,Ypos,Xpos);
	oled_print(i2c,str);
}
void clear_buffer(unsigned char screen_buffer[][128])
{
	int i,j;
	for (i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{
			screen_buffer[i][j] = 0;
		}
	}
}

void update_buffer(ImgType img, unsigned short img_num, unsigned char screen_buffer[][128])
{
int x_dir, y_dir, endx,endy, cnt;
	if((img.w+img.x_pos)>128)
	{
		endx = 127;
	}
	else
		{
			endx = img.w+img.x_pos-1;
		}
	if((img.h+ img.y_pos)>8)
	{
		endy = 7;
	}
	else
		{
			endy = img.h+img.y_pos-1;
		}
	cnt = 0;
		for(y_dir = img.y_pos;y_dir<=endy;y_dir++)
		{
			for (x_dir= img.x_pos;x_dir <= endx; x_dir ++)
			{
				cnt =(y_dir-img.y_pos)*img.w +x_dir-img.x_pos;
				screen_buffer[y_dir][x_dir] = img.image[img_num][cnt];
				
			}
		}
}
void update_str_buffer(short Ypos, short Xpos,char str[], unsigned char screen_buffer[][128])
{
int i,j, cnt_col,cnt_row;
	
cnt_col= Xpos;
cnt_row = Ypos;
i=0;
	while(str[i])
	{
		if(cnt_row>8)
		{break;}
		for(j=0;j<5;j++)
		{
			screen_buffer[cnt_row][cnt_col] = ASCII[str[i]-32][j];
			if((cnt_col+1)>127)
			{
				if((cnt_row+1)>8)
				{
					break;
				}
				else{
					cnt_row ++;
					cnt_col = Xpos;
				}
			}
			else
				{
				 cnt_col ++;
				}
		}
		i++;
	}

}

void print_buffer(char i2c,unsigned char screen_buffer[][128])
{
	oled_pos(i2c,0,0);

	int i,j;
		for (i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{
			 oled_data(i2c,screen_buffer[i][j]);
		}
	}
	
}

// update_buffer_bit()

void update_buffer_bit(ImgType img,unsigned short img_num,unsigned char screen_buffer[][128])
{
	int endx, startx,x_dir,endy, starty,y_dir,y_offset,cnt_1,cnt_2 ;
	int buffer_height = 8;
	int buffer_witdh = 128;
	int start_img_byte =0;
	int start_img_x, start_img_x_temp;
	int bit_y_pos_byte =0;
/*Getting the dimentions */
//--> Working on the X axe dimentions
		// Find endx
			if(img.x_pos>buffer_witdh)
			{
				endx = buffer_witdh;
			}
			else if(img.x_pos<1)
			{
				endx = 0;
			}
			else
			{
				endx = img.x_pos;
			}
		// Find startx
			startx = img.x_pos - img.w;
			if(startx > buffer_witdh)
			{
				startx = buffer_witdh;
			}
			else if (startx <0)
			{
				startx = 0;
			}
		// Starting the picture x_location to start from
			start_img_x = img.w - img.x_pos;
			if(start_img_x <0)
			{
				start_img_x = 0;
			}
		
//--> working on the Y axe dimensions
			y_offset = img.bit_y_pos % 8;
			bit_y_pos_byte = img.bit_y_pos /8;
			if(bit_y_pos_byte>buffer_height)
			{
				bit_y_pos_byte = buffer_height;
			}
		// Find endy
			endy = buffer_height - bit_y_pos_byte +1;
			if(endy<0)
			{
				endy = buffer_height;
			}
			else
			{
				endy = bit_y_pos_byte +1;
			}
		// Find starty
			starty = img.bit_y_pos / 8 - img.h;
			if(starty > buffer_height)
			{
				starty = buffer_height;
			}
			else if(starty < 0)
			{
				starty =0;
			}
			
		// Starting the picture y_location to start from
			start_img_byte = img.h - bit_y_pos_byte -1;
			if(start_img_byte < 0)
			{
				start_img_byte = -1;
			}

// Running the display
			for(y_dir=starty;y_dir<endy;y_dir++)
			{
				start_img_x_temp = start_img_x;
				for(x_dir=startx;x_dir<endx;x_dir++)
				{
						if(start_img_byte == -1)
						{
							cnt_1 = start_img_x;
						}		
						else
						{
							cnt_1 = (start_img_byte)*img.w + start_img_x_temp;
						}
							cnt_2 = (start_img_byte+1)*img.w + start_img_x_temp;
						  start_img_x_temp++;
						//Start building the picture
								
								if(start_img_byte == -1)
								{
									// Beg of the picture
									screen_buffer[y_dir][x_dir] = (img.image[img_num][cnt_2] << (y_offset));
								}
								else if (start_img_byte < img.h-1)
								{
									// inside of the picture
									screen_buffer[y_dir][x_dir] = (img.image[img_num][cnt_2] << (y_offset)) | (img.image[img_num][cnt_1] >> (8-y_offset));
								}
								else
								{
									screen_buffer[y_dir][x_dir] = (img.image[img_num][cnt_1] >> (8-y_offset));
								}
				}
				start_img_byte ++;
			}
	
}
void update_str_buffer_bit(short Ypos, short Xpos,int text_space,char str[], unsigned char screen_buffer[][128])
{
	int i,j;
	int x_dir, y_dir,startx, endx,endy,starty,cnt, cnt_1,cnt_3,y_offset;
	int bit_y_pos_byte =0; // get the number of bytes
	int start_img_x, start_img_x_temp;
	int start_img_byte = 0; /// Variable to check from where getting the downlad
	int buffer_height = 8;
	int buffer_width = 127;
	//int text_space =72;
	int str_w,str_h,str_len;
	
	// Get str dimension
	i=0;
	str_len=0;
	while(str[i])
	{
		str_len++;
		i++;
	}

	str_len *= 5;
	if(text_space == -1)
	{
		text_space = str_len;
	}
	else if(text_space>buffer_width)
	{
		text_space = buffer_width;
	}
	if(str_len>text_space)
	{
		str_w = text_space;
	}
	else
	{
		str_w = str_len;
	}
	str_h = str_len / text_space;
	if(str_len % text_space)
	{
		str_h++;
	}
	
	// Find endx
	if((Xpos)>buffer_width)
	{
		endx = buffer_width;
	}
	else if((Xpos)<1)
	{
		endx = 0;
	}
	else{
		endx = Xpos;
	}
	//find startx
	startx = Xpos-str_w;
	if(startx > buffer_width)
	{
		startx = buffer_width;
	}
	else if(startx<0)
	{
		startx = 0;
	}
		// Starting x_location from the 
	
	start_img_x = str_w - Xpos;
	if(start_img_x<0)
	{
		start_img_x = 0;
	}
	

	y_offset = Ypos % 8;

		bit_y_pos_byte = Ypos/8;
		if(Ypos%8)
		
		endy =  bit_y_pos_byte +1;
		if(endy> buffer_height)
		{
			endy = buffer_height;
		}
		
		start_img_byte =   str_h - bit_y_pos_byte -1;
		starty = Ypos / 8 - str_h;

		
		if(starty > buffer_height)
		{
			starty = buffer_height;
		}
		else if (starty < 0)
		{
			starty = 0;

		}
		else
		{
			//starty--;
			start_img_byte = -1;
		}
		
i=0;
			for(y_dir = starty; y_dir<endy; y_dir++)
		{
			start_img_x_temp =start_img_x;
			cnt=0;
			for (x_dir= startx;x_dir < endx; x_dir ++)
			{
				if(start_img_byte==-1)
				{
				cnt_1 = start_img_x_temp;
				}
				else
				{
				cnt_1 =(start_img_byte)*str_w +start_img_x_temp;
				}
				cnt_3 =(start_img_byte+1)*str_w +start_img_x_temp;
					
				//
				if((cnt%5)==0)
				{
					
					for(j=0;j<5;j++)
					{
								if((cnt_1+j) > (str_len))
								{
									break;
								}
								 if(start_img_byte<0)
										{
											//Draw the beg of the pic
											screen_buffer[y_dir][x_dir] = (ASCII[str[cnt_1/5]-32][j]<<(y_offset));
										}
								else if(start_img_byte<str_h-1)
									{
										
										if(cnt_3 <= str_len)
										{
										screen_buffer[y_dir][x_dir] = (ASCII[str[cnt_3/5]-32][j]<<( y_offset)) | (ASCII[str[cnt_1/5]-32][j]>>(8- y_offset)) ;
										}
										else
										{
											screen_buffer[y_dir][x_dir] = (ASCII[str[cnt_1/5]-32][j]>>(8- y_offset)) ;
										}
									}
								else
									{
										//Draw the end of the pic

											screen_buffer[y_dir][x_dir] = (ASCII[str[cnt_1/5]-32][j]>> (8-y_offset));
											

									}
								start_img_x_temp++;
								cnt++;
								x_dir++;
								if(x_dir >= endx)
									{
										break;
									}
					}
					
					x_dir--;
					
						if(cnt_1 > str_len)
						{
							break;
						}
				}
				else
				{
					start_img_x_temp++;
					cnt++;
				}
				
			
			}
			start_img_byte++;
		}
}

// Data Title logger 
void oled_Title_logger(char i2c,char title_num, char str[])
{
	oled_msg(i2c,title_num,10,str);
}
// Data logger 
void oled_Data_logger(char i2c,char data_num,int data)
{
	char num[10];
	
	oled_msg(i2c,data_num,50,"          ");
	int2char(data,num);
	oled_msg(i2c,data_num,50,num);
	str_empty(num);
}
