#include "Os_EvtHdl.h"
#include "Os_TimerHdl.h"

OS_LOCAL uint8 Os_TaskHdl_Lv0_Task0(void);
OS_LOCAL uint8 Os_TaskHdl_Lv0_Task1(void);
OS_LOCAL uint8 Os_TaskHdl_Lv0_Task2(void);
OS_LOCAL uint8 Os_TaskHdl_Lv0_Task3(void);

uint8 Os_TaskHdl_lv0(void)
{
    uint8 ret = OS_RET_NG;
    switch (OsEvt_Get(EVT_LV0)) {
        case OS_LV0_TASK0:
            ret = Os_TaskHdl_Lv0_Task0();
            break;
        case OS_LV0_TASK1:
            ret = Os_TaskHdl_Lv0_Task1();
            break;
        case OS_LV0_TASK2:
            ret = Os_TaskHdl_Lv0_Task2();
            break;
        case OS_LV0_TASK3:
            ret = Os_TaskHdl_Lv0_Task3();
            break;
        default:
            /* wrong event number */
            break;
    }
    return ret;
}

__weak OS_LOCAL uint8 Os_TaskHdl_Lv0_Task0(void)
{
    uint8 ret = OS_RET_OK;

    return ret;
}

__weak OS_LOCAL uint8 Os_TaskHdl_Lv0_Task1(void)
{
    uint8 ret = OS_RET_OK;

    return ret;
}

__weak OS_LOCAL uint8 Os_TaskHdl_Lv0_Task2(void)
{
    uint8 ret = OS_RET_OK;
     
    return ret;
}

__weak OS_LOCAL uint8 Os_TaskHdl_Lv0_Task3(void)
{
    uint8 ret = OS_RET_OK;

    return ret;
}
