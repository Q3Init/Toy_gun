#include "Os_EvtHdl.h"
#include "Os_TimerHdl.h"

#define TIME_1MS_BASE_1MS 1
#define TIME_5MS_BASE_1MS 5
#define TIME_10MS_BASE_1MS 10
#define TIME_20MS_BASE_1MS 20
#define TIME_50MS_BASE_1MS 50
#define TIME_100MS_BASE_1MS 100

OS_LOCAL void OsTimer_lInit(OsTimerTbl* tbl, uint8 tblSize);
OS_LOCAL void OsTimer_lStartTimer(OsTimerTbl* tbl, uint8 tblSize, uint8 no);
OS_LOCAL void OsTimer_lStopTimer(OsTimerTbl* tbl, uint8 tblSize, uint8 no);
OS_LOCAL void OsTimer_lCheckTimeout(uint8 evtLv, OsTimerTbl* tbl, uint8 tblSize);

static  OsTimerTbl timerTblLv0Array[OS_LV_TASK_CNT] = 
{
    {
        .no = OS_LV0_TASK0,
        .on = TIMER_ON,
        .type = TIMER_CYCLE,
        .period = TIME_5MS_BASE_1MS,
        .delay = 0,
        .tick = 0
    },
    {
        .no = OS_LV0_TASK1,
        .on = TIMER_ON,
        .type = TIMER_CYCLE,
        .period = TIME_10MS_BASE_1MS,
        .delay = 4,
        .tick = 0
    },
    {
        .no = OS_LV0_TASK2,
        .on = TIMER_ON,
        .type = TIMER_CYCLE,
        .period = TIME_50MS_BASE_1MS,
        .delay = 22,
        .tick = 0
    },
    {
        .no = OS_LV0_TASK3,
        .on = TIMER_ON,
        .type = TIMER_CYCLE,
        .period = TIME_100MS_BASE_1MS,
        .delay = 33,
        .tick = 0
    }
};

static  OsTimerTbl timerTblLv1Array[OS_LV_TASK_CNT] = 
{
    {
        .no = OS_LV1_TASK0,
        .on = TIMER_ON,
        .type = TIMER_CYCLE,
        .period = TIME_5MS_BASE_1MS,
        .delay = 2,
        .tick = 0
    },
    {
        .no = OS_LV1_TASK1,
        .on = TIMER_ON,
        .type = TIMER_CYCLE,
        .period = TIME_10MS_BASE_1MS,
        .delay = 8,
        .tick = 0

    },
    {
        .no = OS_LV1_TASK2,
        .on = TIMER_ON,
        .type = TIMER_CYCLE,
        .period = TIME_20MS_BASE_1MS,
        .delay = 11,
        .tick = 0

    },
    {
        .no = OS_LV1_TASK3,
        .on = TIMER_ON,
        .type = TIMER_CYCLE,
        .period = TIME_100MS_BASE_1MS,
        .delay = 23,
        .tick = 0

    }
};

static  OsTimerTbl timerTblLv2Array[OS_LV_TASK_CNT] = 
{
    {
        .no = OS_LV2_TASK0,
        .on = TIMER_ON,
        .type = TIMER_CYCLE,
        .period = TIME_1MS_BASE_1MS,
        .delay = 0,
        .tick = 0
    },
    {
        .no = OS_LV2_TASK1,
        .on = TIMER_OFF,
        .type = TIMER_CYCLE,
        .period = TIME_10MS_BASE_1MS,
        .delay = 0,
        .tick = 0

    },
    {
        .no = OS_LV2_TASK2,
        .on = TIMER_OFF,
        .type = TIMER_CYCLE,
        .period = TIME_20MS_BASE_1MS,
        .delay = 0,
        .tick = 0

    },
    {
        .no = OS_LV2_TASK3,
        .on = TIMER_OFF,
        .type = TIMER_CYCLE,
        .period = TIME_100MS_BASE_1MS,
        .delay = 0,
        .tick = 0

    }
};

void OsTimer_Init(void)
{
    OsTimer_lInit(timerTblLv0Array, OS_LV_TASK_CNT);
    OsTimer_lInit(timerTblLv1Array, OS_LV_TASK_CNT);
    OsTimer_lInit(timerTblLv2Array, OS_LV_TASK_CNT);
}

void OsTimer_CheckTimeout(uint8 evtLv)
{
    switch (evtLv)
    {
        case EVT_LV0:
            OsTimer_lCheckTimeout(EVT_LV0, timerTblLv0Array, OS_LV_TASK_CNT);
            break;
        case EVT_LV1:
            OsTimer_lCheckTimeout(EVT_LV1, timerTblLv1Array, OS_LV_TASK_CNT);
            break;
        case EVT_LV2:
            OsTimer_lCheckTimeout(EVT_LV2, timerTblLv2Array, OS_LV_TASK_CNT);
            break;
        default:
            break;
    }
}

void OsTimer_StartTimer(uint8 evtLv, uint8 no)
{
    switch (evtLv)
    {
        case EVT_LV0:
            OsTimer_lStartTimer(timerTblLv0Array, OS_LV_TASK_CNT, no);
            break;
        case EVT_LV1:
            OsTimer_lStartTimer(timerTblLv1Array, OS_LV_TASK_CNT, no);
            break;
        case EVT_LV2:
            OsTimer_lStartTimer(timerTblLv2Array, OS_LV_TASK_CNT, no);
            break;
        default:
            break;
    }
}

void OsTimer_StopTimer(uint8 evtLv, uint8 no)
{
    switch (evtLv)
    {
        case EVT_LV0:
            OsTimer_lStopTimer(timerTblLv0Array, OS_LV_TASK_CNT, no);
            break;
        case EVT_LV1:
            OsTimer_lStopTimer(timerTblLv1Array, OS_LV_TASK_CNT, no);
            break;
        case EVT_LV2:
            OsTimer_lStopTimer(timerTblLv2Array, OS_LV_TASK_CNT, no);
            break;
        default:
            break;
    }
}

OS_LOCAL void OsTimer_lInit(OsTimerTbl* tbl, uint8 tblSize)
{
    uint8 i;
    for (i = 0; i < tblSize; i++) {
        (tbl + i)->tick = (tbl + i)->delay;
    }
}

OS_LOCAL void OsTimer_lStartTimer(OsTimerTbl* tbl, uint8 tblSize, uint8 no)
{
    uint8 i;
    _DI();
    for (i = 0; i < tblSize; i++) {
        if (no == (tbl + i)->no) {
            (tbl + i)->tick = (tbl + i)->delay;
            (tbl + i)->type = TIMER_ON;
            break;
        }
    }
    _EI();
}

OS_LOCAL void OsTimer_lStopTimer(OsTimerTbl* tbl, uint8 tblSize, uint8 no)
{
    uint8 i;
    _DI();
    for (i = 0; i < tblSize; i++) {
        if (no == (tbl + i)->no) {
            (tbl + i)->tick = 0;
            (tbl + i)->type = TIMER_OFF;
            break;
        }
    }
    _EI();
}

OS_LOCAL void OsTimer_lCheckTimeout(uint8 evtLv, OsTimerTbl* tbl, uint8 tblSize)
{
    uint8 no;
    for (no = 0; no < tblSize; no++) {
        if ((tbl + no)->on == TIMER_ON) {
            if ((tbl + no)->tick > 0) {
                (tbl + no)->tick--;
            }
            if ((tbl + no)->tick == 0) {
                OsEvt_Put(evtLv, (tbl + no)->no);
                if ((tbl + no)->type == TIMER_CYCLE) {
                    (tbl + no)->tick = (tbl + no)->period;
                } else {
                    (tbl + no)->on = TIMER_OFF;
                }
            }
        }
    }
}

