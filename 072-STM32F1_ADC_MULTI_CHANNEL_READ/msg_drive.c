#include "msg_drive.h"


void basic_msg(char uart, int val)
{
	char num[10];
	int2char(val,num);
	UART_SEND(uart,num);
	str_empty(num);
	UART_TX(2,'\n');
}


void make_msg(char uart, char channels,  int * data)
{
	char i = 0;
	char wip[20];
	char myMsg[100] = "#D#";
	
	
	for(i=0; i < channels;i++)
	{		
		InsertData(data[i],wip);
		Concatstr(myMsg,wip);
	}
	Concatstr(myMsg,"\n");
	UART_SEND(uart,myMsg);
	str_empty(myMsg);
}

void InsertData(int num,char * wip)
{
	char numWip[20];
	
	int2char(num,numWip);
	str_empty(wip);
	Concatstr(wip,numWip);
	Concatstr(wip,"#");
	str_empty(numWip);
	
}