#include "stm32f10x.h" 


//###########################################
/*
void TIM1_UP_IRQHandler(){}
void TIM2_IRQHandler(){}
void TIM3_IRQHandler(){}
void TIM4_IRQHandler(){}

*/


enum timers{
	T,T1,T2,T3,T4
};

void TDelay_Micros(char timer, int microS);
void TDelay_Millis(char timer, int milliS);
void TDelay_Micro( int microS);
void TDelay_Milli( int milliS);
int get_time_micros(char timer);
int get_time_millis(char timer);
void timer_stop(char timer);

void timer_irq_micro_start(char timer, int microS);
void timer_irq_millis_start(char timer, int microS);
void timer_irq_Rflag(char timer);
void timer_irq_stop(char timer);

