#include "RTE.h"
#include "Os_EvtHdl.h"
#include "Os_TimerHdl.h"
#include "Os_TaskHdl_Lv0.h"
/* User defined */
#include "stm32f10x.h"
#include "sys.h"
#include "MCAL_GPIO.h"
#include "MCAL_Uart.h"

static volatile boolean rteBswRdyFlg = FALSE;
void RTE_Init(void)
{
    __DISENBLE_IRQ(); /* chip disable irq */
    /* System Tick */
    SysTick_Config(SystemCoreClock/1000); /* 72M / 1000 = 1ms*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    /* OS Init */
#ifdef EASY_OS
    OsEvt_Init();
    OsTimer_Init();
#endif
    /* MCAL Init */
    MCAL_GPIO_Init();
    MCAL_Uart_Init();
    /* BSW Init */

    /* application Init */

    rteBswRdyFlg = TRUE; /* Init complete flag */
    __ENABLE_IRQ(); /* chip enable irq */
}


boolean Get_rteBswRdyFlg(void)
{
	return(rteBswRdyFlg);
}


