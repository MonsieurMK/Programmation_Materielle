#include "Driver_GPIO.h"
#include <stdlib.h>

int main(void)
{
	MyGPIO_Struct_TypeDef * GPIO_LED = malloc(sizeof(MyGPIO_Struct_TypeDef));
	
	GPIO_LED->GPIO = GPIOA;
	GPIO_LED->GPIO_Pin = 5;
	GPIO_LED->GPIO_Conf = Out_Ppull;
	
	MyGPIO_Init(GPIO_LED);
	
	while(1)
	{
		
		
		MyGPIO_Set(GPIO_LED->GPIO, GPIO_LED->GPIO_Pin);
		
		
		
	}
	
}
