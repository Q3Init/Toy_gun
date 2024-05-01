#include "Os_EvtHdl.h"
#include "Os_TimerHdl.h"

OS_LOCAL uint8 Os_TaskHdl_Lv1_Task0(void);
OS_LOCAL uint8 Os_TaskHdl_Lv1_Task1(void);
OS_LOCAL uint8 Os_TaskHdl_Lv1_Task2(void);
OS_LOCAL uint8 Os_TaskHdl_Lv1_Task3(void);

uint8 Os_TaskHdl_lv1(void)
{
    uint8 ret = OS_RET_NG;
    switch (OsEvt_Get(EVT_LV1)) {
        case OS_LV1_TASK0:
            ret = Os_TaskHdl_Lv1_Task0();
            break;
        case OS_LV1_TASK1:
            ret = Os_TaskHdl_Lv1_Task1();
            break;
        case OS_LV1_TASK2:
            ret = Os_TaskHdl_Lv1_Task2();
            break;
        case OS_LV1_TASK3:
            ret = Os_TaskHdl_Lv1_Task3();
            break;
    }
    return ret;
}

OS_LOCAL uint8 Os_TaskHdl_Lv1_Task0(void)
{
    uint8 ret = OS_RET_OK;
    return ret;
}

OS_LOCAL uint8 Os_TaskHdl_Lv1_Task1(void)
{
    uint8 ret = OS_RET_OK;

    return ret;
}

OS_LOCAL uint8 Os_TaskHdl_Lv1_Task2(void)
{
    uint8 ret = OS_RET_OK;
    return ret;
}

OS_LOCAL uint8 Os_TaskHdl_Lv1_Task3(void)
{
    uint8 ret = OS_RET_OK;
    return ret;
}

