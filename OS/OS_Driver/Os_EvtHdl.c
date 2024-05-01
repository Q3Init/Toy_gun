#include "string.h"
#include "Os_EvtHdl.h"
OS_LOCAL void OsEvt_lInit(OsEvtType * pEvt);
OS_LOCAL boolean OsEvt_lIsFull(OsEvtType * pEvt);
OS_LOCAL boolean OsEvt_lIsEmpty(OsEvtType * pEvt);
OS_LOCAL boolean OsEvt_lPutEvt(OsEvtType * pEvt, uint8 no);
OS_LOCAL uint8 OsEvt_lGetEvt(OsEvtType * pEvt);

/* background level, and Lv0 priority > lv1 priority */
OS_LOCAL OsEvtType osEvtLv0;
OS_LOCAL OsEvtType osEvtLv1;
/* frontground level */
OS_LOCAL OsEvtType osEvtLv2;

void OsEvt_Init(void)
{
    OsEvt_lInit(&osEvtLv0);
    OsEvt_lInit(&osEvtLv1);
    OsEvt_lInit(&osEvtLv2);
}

void OsEvt_Put(uint8 lv, const uint8 no)
{
    if (lv == EVT_LV0) {
        (void)OsEvt_lPutEvt(&osEvtLv0, no);
        return;
    }
    if (lv == EVT_LV1) {
        (void)OsEvt_lPutEvt(&osEvtLv1, no);
        return;
    }
    if (lv == EVT_LV2) {
        (void)OsEvt_lPutEvt(&osEvtLv2, no);
        return;
    }
}

uint8 OsEvt_Get(uint8 lv)
{
    uint8 no = EVT_NONE;
    if (lv == EVT_LV0) {
        no = OsEvt_lGetEvt(&osEvtLv0);
    }
    if (lv == EVT_LV1) {
        no = OsEvt_lGetEvt(&osEvtLv1);
    }
    if (lv == EVT_LV2) {
        no = OsEvt_lGetEvt(&osEvtLv2);
    }
    return no;
}

uint8 osEvt_GetBackPrio(void)
{
    uint8 prio = 0;
    if (OsEvt_lIsEmpty(&osEvtLv0) == FALSE) {
        prio += 0x01;
    }
    if (OsEvt_lIsEmpty(&osEvtLv1) == FALSE) {
        prio += 0x02;
    }
    return prio;
}

uint8 osEvt_GetFrontPrio(void)
{
    uint8 prio = 0;
    if (OsEvt_lIsEmpty(&osEvtLv2) == FALSE) {
        prio += 0x04;
    }
    return prio;
}

OS_LOCAL void OsEvt_lInit(OsEvtType * pEvt)
{
    pEvt->cnt = 0;
    pEvt->head = 0;
    pEvt->tail = 0;
    (void)memset((void*)pEvt->no, 0, EVT_MAX);
    return;
}

OS_LOCAL boolean OsEvt_lIsFull(OsEvtType * pEvt)
{
    boolean full = FALSE;
    if (pEvt->cnt == EVT_MAX) {
        full = TRUE;
    }
    return full;
}

OS_LOCAL boolean OsEvt_lIsEmpty(OsEvtType * pEvt)
{
    boolean empty = FALSE;
    if (pEvt->cnt == 0) {
        empty = TRUE;
    }
    return empty;
}

OS_LOCAL boolean OsEvt_lPutEvt(OsEvtType * pEvt, uint8 no)
{
    if (OsEvt_lIsFull(pEvt)) {
        return FALSE;
    }
    _DI();
    pEvt->no[pEvt->tail] = no;
    pEvt->tail++;
    if (pEvt->tail >= EVT_MAX) {
        pEvt->tail = 0;
    }
    pEvt->cnt++;
    _EI();
    return TRUE;
}

OS_LOCAL uint8 OsEvt_lGetEvt(OsEvtType * pEvt)
{
    uint8 no;
    if (OsEvt_lIsEmpty(pEvt) == TRUE) {
        return EVT_NONE;
    }
    _DI();
    no = pEvt->no[pEvt->head];
    pEvt->head++;
    if (pEvt->head >= EVT_MAX) {
        pEvt->head = 0;
    }
    pEvt->cnt--;
    _EI();
    return no;
}
