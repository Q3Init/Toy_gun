#ifndef  MCAL_GPIO_H_
#define  MCAL_GPIO_H_

#include "Platform_Types.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

extern void MCAL_GPIO_Init(void);
extern void MCAL_GPIO_FlipcBit(GPIO_TypeDef* port, uint16_t pin);

#endif
