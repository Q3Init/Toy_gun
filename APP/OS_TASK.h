#ifndef  OS_TASK_H_
#define  OS_TASK_H_

#include "Platform_Types.h"
#include "Os_EvtHdl.h"
#include "Os_TimerHdl.h"
#include "Os_TaskHdl_Lv0.h"
#include "Os_TaskHdl_Lv1.h"
#include "Os_TaskHdl_Lv2.h"

OS_LOCAL uint8 Os_TaskHdl_Lv0_Task0(void);
OS_LOCAL uint8 Os_TaskHdl_Lv0_Task1(void);
OS_LOCAL uint8 Os_TaskHdl_Lv0_Task2(void);
OS_LOCAL uint8 Os_TaskHdl_Lv0_Task3(void);
extern void OS_Delay_us(uint32 counter);

#endif
