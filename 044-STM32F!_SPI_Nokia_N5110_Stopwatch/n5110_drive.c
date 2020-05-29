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

void n5110_add_print(short Ypos, short Xpos, char str[])
{
	int i,j;
	i = 0;
	
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


// n5110_clear

void n5110_clear(void)
{
	int j;
n5110_pos(0,0);
	W_GP(PA,1,HIGH);
	for(j=0;j<504;j++)
	{
		spi_tx(1,0x00);
	}
}
//clear buffer
void clear_buffer(unsigned char screen_buffer[][84])
{
	int i,j;
	for (i=0;i<6;i++)
	{
		for(j=0;j<84;j++)
		{
			screen_buffer[i][j] = 0;
		}
	}
}

//print buffer
void print_buffer(unsigned char screen_buffer[][84])
{
	 n5110_clear();
		n5110_pos(0,0);
	int i,j;
	W_GP(PA,1,HIGH);
	for (i=0;i<6;i++)
	{
		for(j=0;j<84;j++)
		{
			 spi_tx(1,screen_buffer[i][j]);
		}
	}
	W_GP(PA,1,LOW);
}

//update_buffer
void update_buffer(ImgType img, unsigned short img_num, unsigned char screen_buffer[][84])
{
int x_dir, y_dir, endx,endy, cnt;
	if((img.w+img.x_pos)>84)
	{
		endx = 83;
	}
	else
		{
			endx = img.w+img.x_pos-1;
		}
	if((img.h+ img.y_pos)>5)
	{
		endy = 5;
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

//update str buffer
void update_str_buffer(short Ypos, short Xpos,char str[], unsigned char screen_buffer[][84])
{
int i,j, cnt_col,cnt_row;
	
cnt_col= Xpos;
cnt_row = Ypos;
i=0;
	while(str[i])
	{
		if(cnt_row>5)
		{break;}
		for(j=0;j<5;j++)
		{
			screen_buffer[cnt_row][cnt_col] = ASCII[str[i]-32][j];
			if((cnt_col+1)>83)
			{
				if((cnt_row+1)>5)
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
