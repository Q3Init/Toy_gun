#ifndef OS_EVENT_HANDLE_H_
#define OS_EVENT_HANDLE_H_
#include "Os_Common.h"

#define EVT_MAX 16
#define EVT_NONE 0xFF

#define EVT_LV0 0
#define EVT_LV1 1
#define EVT_LV2 2

#define EVT_LV0_PRIO 1
#define EVT_LV1_PRIO 2
#define EVT_LV2_PRIO 4

typedef struct {
    /* data */
    uint8 head;
    uint8 tail;
    uint8 cnt;
    uint8 no[EVT_MAX];
} OsEvtType;

OS_EXTERN void OsEvt_Init(void);
OS_EXTERN void OsEvt_Put(uint8 lv, const uint8 no);
OS_EXTERN uint8 OsEvt_Get(uint8 lv);
OS_EXTERN uint8 osEvt_GetBackPrio(void);
OS_EXTERN uint8 osEvt_GetFrontPrio(void);

#endif
