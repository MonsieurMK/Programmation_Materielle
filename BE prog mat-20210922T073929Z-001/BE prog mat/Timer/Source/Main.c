#include "stm32f10x.h"
#include "Driver_GPIO.h"
#define positionB 8
#define positionL	10
#define GPIOLed GPIOC
#define GPIOBtn GPIOC

int main(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // enabling TIM2
	TIM2->CR1 |= 0x1;
	TIM2->PSC = 72000; // prescaled
	TIM2->ARR = 500;  // auto-reload register
	
	while(1);
}
