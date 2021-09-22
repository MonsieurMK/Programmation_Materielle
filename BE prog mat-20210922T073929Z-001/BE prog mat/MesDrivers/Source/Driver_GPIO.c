
#include "stm32f10x.h"
#include "Driver_GPIO.h"


void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) {
	
	if (GPIOStructPtr->GPIO_Pin>7) {  //les pin sont séparés en 2 registres
		GPIOStructPtr->GPIO->CRH &= ~(~GPIOStructPtr->GPIO_Conf<< 2*(2*GPIOStructPtr->GPIO_Pin-16));
		GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf<< 2*(2*GPIOStructPtr->GPIO_Pin-16)); //On commence par mettre les 0, puis on met les 1
		
	}
	else {
		GPIOStructPtr->GPIO->CRL &= ~(~GPIOStructPtr->GPIO_Conf<< (2*GPIOStructPtr->GPIO_Pin));
		GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf<< (2*GPIOStructPtr->GPIO_Pin));  
	}
}

int MyGPIO_Read(GPIO_TypeDef * GPIO , char GPIO_Pin )  // renvoie 0 ou autre chose d i f f e r e n t de 0
{
	return ((GPIO->IDR) & ( 0x01 << GPIO_Pin)) >> GPIO_Pin;
}
	
void MyGPIO_Set(GPIO_TypeDef * GPIO , char GPIO_Pin ) 
{
	GPIO->BSRR = (0x01 << GPIO_Pin ) | ((~0x01)<< (GPIO_Pin +16));
}
void MyGPIO_Reset(GPIO_TypeDef * GPIO , char GPIO_Pin ) 
{
	GPIO->ODR &= ~(0x01 << GPIO_Pin) ;
}
void MyGPIO_Toggle(GPIO_TypeDef * GPIO , char GPIO_Pin ) 
{
	GPIO->ODR ^= (0x01 << GPIO_Pin) ;
}


