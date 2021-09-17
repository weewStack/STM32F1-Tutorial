#include "msg_drive.h"


void basic_msg(char uart, int val)
{
	char num[10];
	int2char(val,num);
	UART_SEND(uart,num);
	str_empty(num);
	UART_TX(2,'\n');
}


void sync(char uart,char channels)
{
 char sync_mesg[20] = "#!";
 char wip[20];
	InsertData(channels,wip);
	Concatstr(sync_mesg,wip);
	Concatstr(sync_mesg,"#\n");
	UART_SEND(2,sync_mesg);
	str_empty(sync_mesg);
	str_empty(wip);
}

void make_msg(char uart, char channels,  int * data)
{
	char i = 0;
	char wip[20];
	char myMsg[100] = "#D";

	
	
	for(i=0; i < channels;i++)
	{		
		InsertData(data[i],wip);
		Concatstr(myMsg,wip);
	}
	Concatstr(myMsg,"#\n");
	UART_SEND(uart,myMsg);
	str_empty(myMsg);
}


void make_msg_check(char uart, char channels,  int * data)
{
	char i = 0;
	char wip[20];
	char myMsg[100] = "#D";
  int msg_len = 0;
	
	
	for(i=0; i < channels;i++)
	{		
		msg_len += InsertData(data[i],wip);
		Concatstr(myMsg,wip);
	}
	
	InsertData(msg_len,wip);
	Concatstr(myMsg,wip);
	
	Concatstr(myMsg,"#\n");
	UART_SEND(uart,myMsg);
	str_empty(wip);
	str_empty(myMsg);
}

//Update message and output he number of char inside the message
int InsertData(int num,char * wip)
{
	int cnt = 0;
	char numWip[20];
	
	int2char(num,numWip);
	cnt = len_str(numWip);
	str_empty(wip);
	Concatstr(wip,"#");
	Concatstr(wip,numWip);
	str_empty(numWip);
	
	
	return cnt;

}
