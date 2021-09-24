#include "stm32f10x.h"
#include "MyTimer.h"
#include <stdlib.h>

int main(void)
{
	/*
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // enabling TIM2
	TIM2->CR1 |= 0x0;
	TIM2->PSC = 35999; // prescaled
	TIM2->ARR = 999;  // auto-reload register
	TIM2->CR1 |= 0x1;
	*/
	MyTimer_Struct_TypeDef * Timer = malloc(sizeof(MyTimer_Struct_TypeDef));
	Timer->Timer = TIM2;
	Timer->shortPSC = 35999;
	Timer->shortARR = 999;
	
	MyTimer_Base_Init(Timer);
	MyTimer_Base_Start(Timer);
	while(1);
}
