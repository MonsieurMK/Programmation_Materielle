#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include <stdlib.h>

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

/***************************************************************************************************
	*@brief
	*@param :-TIM_TypeDef*Timer  :   Timer concerne
		-char  Prio  :  de 0 a 15*@Note :   La  fonction   MyTimer_Base_Init  doit  avoir  ete  lancee au prealable
***************************************************************************************************/

void MyTimer_ActiveIT(TIM_TypeDef*Timer ,char Prio, void (*IT_function) (void));

/**
*@brief
*@param   . . . .
*@Note    Active le channel spécifié suTimerr  le  timer  spé c i f i é
*la  gestion  de  la  configuration   I /O n ’ est  pas  f a i t e  dans  cette  fonction
*ni  le  r é glage de  la pé riode de  la PWM (ARR, PSC)
*/
void MyTimer_PWM(TIM_TypeDef*Timer, char Channel);

// définit et configure les pins de sortie pour le PWM
void MyTimer_PWM_Start(TIM_TypeDef * Timer, char Channel);

void MyTimer_PWM_Config(TIM_TypeDef * Timer, char Channel, int value);

#define MyTimer_Base_Start(Timer) ( Timer->Timer->CR1 = 0x1 )
#define MyTimer_Base_Stop(Timer)  ( Timer->Timer->CR1 = 0x0 )
#endif
