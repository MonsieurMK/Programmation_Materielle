#ifndef DRIVER_ADC
#define DRIVER_ADC
#include "stm32f10x.h"

// init
void Init_ADC_Single_Conv(ADC_TypeDef * ADC, uint16_t Duree_ech_us);

// set mode
// autre modes non implémentés, on reste sur du single discontinuous, sans DMA
void Set_Mode_ADC(ADC_TypeDef * ADC, char isContinuous);

// store in register
uint16_t Get_ADC_Values(ADC_TypeDef * ADC);

// start
void Start_ADC(ADC_TypeDef * ADC);

// stop
void Stop_ADC(ADC_TypeDef * ADC);

#endif