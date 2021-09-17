#include "uart_drive.h"
#include "help_func.h"



void basic_msg(char uart, int val);
void sync(char uart,char channels);
void make_msg(char uart,  char channels, int * data);
void make_msg_check(char uart, char channels,  int * data);
int InsertData(int num,char * wip);
