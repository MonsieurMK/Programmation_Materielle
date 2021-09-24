#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"

typedef  struct
{
		TIM_TypeDef*Timer ;   // TIM1 � TIM4
		unsigned shortARR;
		unsigned shortPSC;
} MyTimer_Struct_TypeDef ;

/******************************************************************************************
	*@brief
	*@param-> Param�tre sous forme d�une structure (son adresse) contenant les informations de base
	*@Note-> Fonction � lancer  syst �matiquement avant d � a l l e r  plus en d� t a i l  dans  l e sconf  plus  f i n e s  (PWM, codeur  inc . . . )
**************************************************************************************************/

void MyTimer_Base_Init(MyTimer_Struct_TypeDef*Timer);

#define MyTimer_Base_Start(Timer) ( Timer->Timer->CR1 = 0x1 )
#define MyTimer_Base_Stop(Timer)  ( Timer->Timer->CR1 = 0x0 )
#endif
