#include "timer_drive.h"

TIM_TypeDef * get_timer(char timer){
	TIM_TypeDef * tim;
	switch(timer)
	{
		case 1 : tim = TIM1;break;
		case 2 : tim = TIM2;break;
		case 3 : tim = TIM3;break;
		case 4 : tim = TIM4;break;
	}
	return tim;
}

TIM_TypeDef * timer_start_micros(char timer, int microS){
	int prescaler = 72-1;
	TIM_TypeDef * tim;

	if(timer==1)
	{
		//Setup the Counter at the bus level
		RCC->APB2ENR |= 0x0800;
	}
	else
	{
		RCC->APB1ENR |= 1 <<(timer-2);
	}
	tim = get_timer(timer);
	
		// Setup the counter to 0
	tim->CNT = 0;
	
	// Setup the prescaler to 72 -> 1 div equal to 1 Micro Sec
	tim->PSC = prescaler;	
	
	// initialize the Auto reload register value
	tim->ARR = (microS-3);	
	
	//Enable the counter
	tim->CR1 |= 0x1;
	
	return tim ;
}

TIM_TypeDef * timer_start_millis(char timer, int millis){
	int prescaler = (36000-1);
	TIM_TypeDef * tim;

	if(timer==1)
	{
		//Setup the Counter at the bus level
		RCC->APB2ENR |= 0x0800;
	}
	else
	{
		RCC->APB1ENR |= 1 <<(timer-2);
	}
	tim = get_timer(timer);
	
		// Setup the counter to 0
	tim->CNT = 0;
	
	// Setup the prescaler to 72 -> 1 div equal to 1 Micro Sec
	tim->PSC = prescaler;	
	
	// initialize the Auto reload register value
	tim->ARR = (millis*2);	
	
	//Enable the counter
	tim->CR1 |= 0x1;
	
	return tim ;
}

int get_time_micros(char timer){
	TIM_TypeDef * tim = get_timer(timer);
	int my_step = tim->PSC;
	int my_time = (my_step*tim->CNT) / (72-1);
	
	return my_time;
}

int get_time_millis(char timer){
	int my_time = get_time_micros(timer) /1000;
	
	return my_time;
}


void TDelay_Micros(char timer, int microS){
	
	TIM_TypeDef * tim = timer_start_micros(timer, microS);

	//Enable the counter
	tim->CR1 |= 0x9;
	
	while(tim->CR1 & 1)
	{}
	
}

void TDelay_Millis(char timer, int milliS){
	int i = 0;
	for(i=0;i<milliS;i++)
	{
		TDelay_Micros(timer,1000);
	}
}

void TDelay_Micro(int microS){
	TDelay_Micros(T4, microS);
}

void TDelay_Milli(int milliS){
	TDelay_Millis(T4, milliS);
}

void timer_irq_micro_start(char timer, int microS){
	TIM_TypeDef * tim = timer_start_micros(timer, microS);
	tim->DIER |= 1;
	
	__disable_irq();
	switch(timer)
	{
		case 1 : NVIC_EnableIRQ(TIM1_UP_IRQn);break;
		case 2 : NVIC_EnableIRQ(TIM2_IRQn);break;
		case 3 : NVIC_EnableIRQ(TIM3_IRQn);break;
		case 4 : NVIC_EnableIRQ(TIM4_IRQn);break;
	}
	__enable_irq();
	
}
void timer_irq_millis_start(char timer, int milliS){
	TIM_TypeDef * tim = timer_start_millis(timer, milliS);
	tim->DIER |= 1;
	
	__disable_irq();
	switch(timer)
	{
		case 1 : NVIC_EnableIRQ(TIM1_UP_IRQn);break;
		case 2 : NVIC_EnableIRQ(TIM2_IRQn);break;
		case 3 : NVIC_EnableIRQ(TIM3_IRQn);break;
		case 4 : NVIC_EnableIRQ(TIM4_IRQn);break;
	}
	__enable_irq();
	
}
void timer_irq_Rflag(char timer){
	TIM_TypeDef * tim = get_timer(timer);
	tim->SR &= 0xFFFE;

}

void timer_irq_stop(char timer){
	TIM_TypeDef * tim = get_timer(timer);
	tim->DIER &= 0xFFFE;
	
	__disable_irq();
	switch(timer)
	{
		case 1 : NVIC_DisableIRQ(TIM1_UP_IRQn);break;
		case 2 : NVIC_DisableIRQ(TIM2_IRQn);break;
		case 3 : NVIC_DisableIRQ(TIM3_IRQn);break;
		case 4 : NVIC_DisableIRQ(TIM4_IRQn);break;
	}
	__enable_irq();

}

void timer_stop(char timer){
	TIM_TypeDef * tim = get_timer(timer);
	tim->CR1 =0;
	if(timer==1)
	{
		//Setup the Counter at the bus level
		RCC->APB2ENR &= ~0x0800;
	}
	else
	{
		RCC->APB1ENR &= ~(1 <<(timer-2));
	}
	timer_irq_stop(timer);
}
