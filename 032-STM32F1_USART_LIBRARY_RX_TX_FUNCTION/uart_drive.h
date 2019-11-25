#include "stm32f10x.h"  
#include "gp_drive.h" 

unsigned long USART_BRR(unsigned short usart, unsigned long BR);
void UART_init(unsigned short usart, unsigned long BR);
char UART_RX(unsigned short uart);
void UART_TX(unsigned short uart,char c);
