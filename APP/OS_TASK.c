#include "OS_TASK.h"
/* User define */
#include "Rte.h"
#include "sys.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "Lib_Log_Util.h"
#include "MCAL_GPIO.h"

OS_LOCAL uint8 Os_TaskHdl_Lv0_Task0(void)
{
    uint8 ret = OS_RET_OK;

    return ret;
}

OS_LOCAL uint8 Os_TaskHdl_Lv0_Task1(void)
{
    uint8 ret = OS_RET_OK;

    return ret;
}

OS_LOCAL uint8 Os_TaskHdl_Lv0_Task2(void)
{
    uint8 ret = OS_RET_OK;

    return ret;
}

OS_LOCAL uint8 Os_TaskHdl_Lv0_Task3(void)
{
    uint8 ret = OS_RET_OK;
    MCAL_GPIO_FlipcBit(GPIOC,GPIO_Pin_13);
    return ret;
}

void OS_Delay_us(uint32 counter)
{
    counter *=9;
    while(counter--);
}

