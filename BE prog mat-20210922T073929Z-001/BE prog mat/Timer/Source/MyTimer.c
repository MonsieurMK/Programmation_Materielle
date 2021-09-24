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
