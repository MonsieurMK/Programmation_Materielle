#include "stm32f10x.h"
#define positionB 8
#define positionL	10
#define GPIOLed GPIOC
#define GPIOBtn GPIOC

int main(void)
{
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ; // = 0x4002101C
	
	//GPIOA->CRL = 0x44244444;
	//GPIOC->CRH = 0x44444444;
	if (positionL>7) {
		GPIOLed->CRH &= ~(0x02<< 2*(2*positionL-16));
	}
	else {
		GPIOLed->CRL &= ~(0x03<< (2*positionL));
	}
	do{
		vu32 pinB = ((GPIOBtn->IDR) & ( 0x01 << positionB)) >> positionB;
		GPIOLed->BSRR = (pinB << positionL ) | ((~pinB)<< (positionL +16));
		
		//GPIOA->ODR |= ~(((pinB << (15-positionB)) >> 15) << positionL);
		//GPIOC->ODR |= ~(((pinB << (15-positionB)) >> 15) << positionL);
	}while(1) ;
}
