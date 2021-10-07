#include "MyTimer.h"

void (* ptrFunction) (void);

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

void MyTimer_ActiveIT(TIM_TypeDef*Timer ,char Prio, void (*IT_function) ())
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
	
	ptrFunction = IT_function;
}

void MyTimer_PWM_init(TIM_TypeDef*Timer, char Channel)
{	
	// voir datasheet p. 31
	MyGPIO_Struct_TypeDef * GPIO_PWM = malloc(sizeof(MyGPIO_Struct_TypeDef));
	GPIO_PWM->GPIO_Conf = AltOut_Ppull;
	
	if (Timer == TIM1) {
		Timer->BDTR |= TIM_BDTR_MOE;
	}
	
	switch (Channel) {
		// reference manual 14.4.14 etc
		case 1:
			Timer->CCMR1 &= ~TIM_CCMR1_OC1M_0;
			Timer->CCMR1 |= TIM_CCMR1_OC1M_1;
			Timer->CCMR1 |= TIM_CCMR1_OC1M_2;
			Timer->CCMR1 |= TIM_CCMR1_OC1PE;
			Timer->CCMR1 &= ~TIM_CCMR1_CC1S_0;
			Timer->CCMR1 &= ~TIM_CCMR1_CC1S_1;
		
			Timer->CCER |= TIM_CCER_CC1E;
			break;
		case 2:
			Timer->CCMR1 &= ~TIM_CCMR1_OC2M_0;
			Timer->CCMR1 |= TIM_CCMR1_OC2M_1;
			Timer->CCMR1 |= TIM_CCMR1_OC2M_2;
			Timer->CCMR1 |= TIM_CCMR1_OC2PE;
			Timer->CCMR1 &= ~TIM_CCMR1_CC2S_0;
			Timer->CCMR1 &= ~TIM_CCMR1_CC2S_1;
		
			Timer->CCER |= TIM_CCER_CC2E;
			break;
		case 3:
			Timer->CCMR2 &= ~TIM_CCMR2_OC3M_0;
			Timer->CCMR2 |= TIM_CCMR2_OC3M_1;
			Timer->CCMR2 |= TIM_CCMR2_OC3M_2;
			Timer->CCMR2 |= TIM_CCMR2_OC3PE;
			Timer->CCMR2 &= ~TIM_CCMR2_CC3S_0;
			Timer->CCMR2 &= ~TIM_CCMR2_CC3S_1;
		
			Timer->CCER |= TIM_CCER_CC3E;
			break;
		default:
			Timer->CCMR2 &= ~TIM_CCMR2_OC4M_0;
			Timer->CCMR2 |= TIM_CCMR2_OC4M_1;
			Timer->CCMR2 |= TIM_CCMR2_OC4M_2;
			Timer->CCMR2 |= TIM_CCMR2_OC4PE;
			Timer->CCMR2 &= ~TIM_CCMR2_CC4S_0;
			Timer->CCMR2 &= ~TIM_CCMR2_CC4S_1;	

			Timer->CCER |= TIM_CCER_CC4E;
			break;
	}
	
	if (Timer == TIM1)
	{
		GPIO_PWM->GPIO = GPIOA;
		switch (Channel) {
			case 1:
				GPIO_PWM->GPIO_Pin = 8;
			break;
			case 2:
				GPIO_PWM->GPIO_Pin = 9;
			break;
			case 3:
				GPIO_PWM->GPIO_Pin = 10;
			break;
			default:
				GPIO_PWM->GPIO_Pin = 11;
			break;
		}
	} else if (Timer == TIM2)
	{
		GPIO_PWM->GPIO = GPIOA;
		switch (Channel) {
			case 1:
				GPIO_PWM->GPIO_Pin = 0;
			break;
			case 2:
				GPIO_PWM->GPIO_Pin = 1;
			break;
			case 3:
				GPIO_PWM->GPIO_Pin = 2;
			break;
			default:
				GPIO_PWM->GPIO_Pin = 3;
			break;
		}
	} else if (Timer == TIM3)
	{
		switch (Channel) {
			case 1:
				GPIO_PWM->GPIO = GPIOA;
				GPIO_PWM->GPIO_Pin = 6;
			break;
			case 2:
				GPIO_PWM->GPIO = GPIOA;
				GPIO_PWM->GPIO_Pin = 7;
			break;
			case 3:
				GPIO_PWM->GPIO = GPIOB;
				GPIO_PWM->GPIO_Pin = 0;
			break;
			default:
				GPIO_PWM->GPIO = GPIOB;
				GPIO_PWM->GPIO_Pin = 1;
			break;
		}
	} else
	{
		GPIO_PWM->GPIO = GPIOB;
		
		switch (Channel) {
			case 1:
				GPIO_PWM->GPIO_Pin = 6;
			break;
			case 2:
				GPIO_PWM->GPIO_Pin = 7;
			break;
			case 3:
				GPIO_PWM->GPIO_Pin = 8;
			break;
			default:
				GPIO_PWM->GPIO_Pin = 9;
			break;
		}
	}
	
	MyGPIO_Init(GPIO_PWM);
}

void MyTimer_PWM_set_rapp_cyclique(TIM_TypeDef * Timer, char Channel, int value)
{
	switch(Channel) {
		case 1:
			Timer->CCR1 = value;
			break;
		case 2:
			Timer->CCR2 = value;
			break;
		case 3:
			Timer->CCR3 = value;
			break;
		default:
			Timer->CCR4 = value;
			break;
	}
}

void MyTimer_PWM(TIM_TypeDef * Timer, char Channel, int value)
{
	MyTimer_PWM_init(Timer, Channel);
	MyTimer_PWM_set_rapp_cyclique(Timer, Channel, value);
}

void TIM1_UP_IRQHandler(void)
{
	TIM1->SR &= ~TIM_SR_UIF;
	if (ptrFunction != 0)
		(*ptrFunction) ();
}

void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~TIM_SR_UIF;
	if (ptrFunction != 0)
		(*ptrFunction) ();
}

void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF;
	if (ptrFunction != 0)
		(*ptrFunction) ();
}

void TIM4_IRQHandler(void)
{
	TIM4->SR &= ~TIM_SR_UIF;
	if (ptrFunction != 0)
		(*ptrFunction) ();
}
