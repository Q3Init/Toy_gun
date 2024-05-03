#ifndef  MCAL_TIMER_H_
#define  MCAL_TIMER_H_

#include "Platform_Types.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"

extern void MCAL_TIMER_Init(void);
extern void Delay_us(u16 xus);
extern void Delay_ms(u16 xms);

#endif
