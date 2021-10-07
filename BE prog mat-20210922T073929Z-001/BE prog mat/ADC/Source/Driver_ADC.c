#include "Driver_ADC.h"

void Init_ADC_Single_Conv(ADC_TypeDef * ADC, uint16_t Duree_ech_us)
{
	
}

void Set_Mode_ADC(ADC_TypeDef * ADC, char isContinuous);

uint16_t Get_ADC_Values(ADC_TypeDef * ADC);

void Start_ADC(ADC_TypeDef * ADC);

void Stop_ADC(ADC_TypeDef * ADC);