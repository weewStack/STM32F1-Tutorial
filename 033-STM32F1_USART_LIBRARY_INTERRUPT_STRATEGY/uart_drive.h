#include "stm32f10x.h"  
#include "gp_drive.h" 
#include "systick_time.h"

unsigned long USART_BRR(unsigned short usart, unsigned long BR);
void UART_init(unsigned short usart, unsigned long BR);
char UART_RX(unsigned short uart);
void UART_TX(unsigned short uart,char c);
void UART_ISR(unsigned short uart,unsigned short bridge, unsigned short * signal, unsigned short * counter, char str[]);
void UART_SEND(unsigned short uart, char str[]);
void str_empty(char str[]);
