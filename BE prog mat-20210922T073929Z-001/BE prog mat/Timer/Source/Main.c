#include "stm32f10x.h"
#include "MyTimer.h"
#include <stdlib.h>

void fct_IT()
{
	MyGPIO_Struct_TypeDef * GPIO_LED = malloc(sizeof(MyGPIO_Struct_TypeDef));
	
	GPIO_LED->GPIO = GPIOA;
	GPIO_LED->GPIO_Pin = 5;
	GPIO_LED->GPIO_Conf = Out_Ppull;
	
	MyGPIO_Init(GPIO_LED);
	
	MyGPIO_Toggle(GPIO_LED->GPIO, 5);
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
	//MyTimer_ActiveIT(Timer->Timer, 8, fct_IT);
	//MyTimer_Base_Start(Timer);
	MyTimer_PWM(Timer->Timer, 1);
	MyTimer_PWM_Config(Timer->Timer, 1, 199);
	MyTimer_PWM_Start(Timer->Timer, 1);
	while(1);
}
