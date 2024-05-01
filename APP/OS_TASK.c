#include "OS_TASK.h"
/* User define */
#include "Rte.h"
#include "sys.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

void BSW_Dio_FlipcBit(GPIO_TypeDef* port, uint16_t pin)
{
    uint8_t level = GPIO_ReadInputDataBit(port, pin);
    level = (level>0)? 0 : 1;
    GPIO_WriteBit(port, pin, (BitAction)level);
}


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
    BSW_Dio_FlipcBit(GPIOC,GPIO_Pin_13);
    return ret;
}

void OS_Delay_us(uint32 counter)
{
    counter *=9;
    while(counter--);
}

