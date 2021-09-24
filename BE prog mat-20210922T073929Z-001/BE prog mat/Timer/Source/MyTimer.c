#include "MyTimer.h"

void MyTimer_Base_Init(MyTimer_Struct_TypeDef*Timer)
{
	
	if (Timer->Timer == TIM1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	} else if (Timer->Timer == TIM2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	} else if (Timer->Timer == TIM3)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	} else
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	}
	Timer->Timer->CR1 |= 0x0;
	Timer->Timer->PSC = Timer->shortPSC;
	Timer->Timer->ARR = Timer->shortARR;
	//Timer->Timer->CR1 |= 0x1;
}

void MyTimer_ActiveIT(TIM_TypeDef*Timer ,char Prio)
{
	Timer->DIER |= TIM_DIER_UIE;
	if (Timer == TIM1)
	{
		NVIC_EnableIRQ(TIM1_UP_IRQn);
		NVIC_SetPriority(TIM1_UP_IRQn, Prio);
	} else if (Timer == TIM2)
	{
		//NVIC->ISER[0] |= NVIC_ISER_SETENA_28; // pour TIM2 n28
		NVIC_EnableIRQ(TIM2_IRQn);
		NVIC_SetPriority(TIM2_IRQn, Prio);
	} else if (Timer == TIM3)
	{
		NVIC_EnableIRQ(TIM3_IRQn);
		NVIC_SetPriority(TIM3_IRQn, Prio);
	} else
	{
		NVIC_EnableIRQ(TIM4_IRQn);
		NVIC_SetPriority(TIM4_IRQn, Prio);
	}
}


