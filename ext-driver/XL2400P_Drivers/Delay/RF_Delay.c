#include "RF_Delay.h"
#include "MCAL_Timer.h"
#include "Platform_Types.h"


//微秒延时函数
void DelayUs(unsigned char Time)
{
	Delay_us((uint16_t)Time);
} 

//毫秒延时函数
void DelayMs(unsigned char Time)
{
	Delay_ms((uint16_t)Time);
}


