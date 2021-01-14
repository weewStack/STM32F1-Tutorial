#include "msg_drive.h"


void basic_msg(char uart, int val)
{
	char num[10];
	int2char(val,num);
	UART_SEND(uart,num);
	str_empty(num);
	UART_TX(2,'\n');
}
