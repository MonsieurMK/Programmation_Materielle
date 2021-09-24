#include "stm32f10x.h"
#include "MyTimer.h"
#include <stdlib.h>

void TIM1_UP_IRQHandler(void)
{
	TIM1->SR &= ~TIM_SR_UIF;
}

void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~TIM_SR_UIF;
}

void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF;
}

void TIM4_IRQHandler(void)
{
	TIM4->SR &= ~TIM_SR_UIF;
}

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
	Timer->Timer = TIM1;
	Timer->shortPSC = 35999;
	Timer->shortARR = 999;
	
	MyTimer_Base_Init(Timer);
	MyTimer_ActiveIT(Timer->Timer, 1);
	MyTimer_Base_Start(Timer);
	while(1);
}
