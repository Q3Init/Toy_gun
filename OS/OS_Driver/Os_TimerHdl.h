#ifndef OS_TIMER_HANDLE_H_
#define OS_TIMER_HANDLE_H_
#include "Os_Common.h"

#define TIMER_ON TRUE
#define TIMER_OFF FALSE

#define TIMER_CYCLE   1
#define TIMER_ONESHOT 0

#define OS_LV0_TASK0 0
#define OS_LV0_TASK1 1
#define OS_LV0_TASK2 2
#define OS_LV0_TASK3 3

#define OS_LV1_TASK0 0
#define OS_LV1_TASK1 1
#define OS_LV1_TASK2 2
#define OS_LV1_TASK3 3

#define OS_LV2_TASK0 0
#define OS_LV2_TASK1 1
#define OS_LV2_TASK2 2
#define OS_LV2_TASK3 3

#define OS_LV_TASK_CNT 4

typedef struct {
    uint8 no;
    boolean on;
    uint8 type;
    uint16 period;
    uint16 delay;
    uint16 tick;
}OsTimerTbl;

OS_EXTERN void OsTimer_Init(void);
OS_EXTERN void OsTimer_CheckTimeout(uint8 evtLv);
OS_EXTERN void OsTimer_StartTimer(uint8 evtLv, uint8 no);
OS_EXTERN void OsTimer_StopTimer(uint8 evtLv, uint8 no);
#endif
