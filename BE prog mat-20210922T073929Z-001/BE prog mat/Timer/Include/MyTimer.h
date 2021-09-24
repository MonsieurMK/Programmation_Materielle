#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"

typedef  struct
{
		TIM_TypeDef*Timer ;   // TIM1 à TIM4
		unsigned shortARR;
		unsigned shortPSC;
} MyTimer_Struct_TypeDef ;

/******************************************************************************************
	*@brief
	*@param-> Paramètre sous forme d’une structure (son adresse) contenant les informations de base
	*@Note-> Fonction à lancer  syst ématiquement avant d ’ a l l e r  plus en dé t a i l  dans  l e sconf  plus  f i n e s  (PWM, codeur  inc . . . )
**************************************************************************************************/

void MyTimer_Base_Init(MyTimer_Struct_TypeDef*Timer);

#define MyTimer_Base_Start(Timer) ( Timer->Timer->CR1 = 0x1 )
#define MyTimer_Base_Stop(Timer)  ( Timer->Timer->CR1 = 0x0 )
#endif
