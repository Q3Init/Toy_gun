#include "RTE.h"
#ifdef EASY_OS
#include "Os_TaskHdl_Lv0.h"
#include "Os_EvtHdl.h"
#else
#include "freertos.h"
#include "task.h"
#include "FreeRTOS_TASK.h"
#endif



int main(void)
{
#ifdef EASY_OS
	uint8 Priority;
	(void)RTE_Init();
#else
	/* 定义一个创建信息返回值，默认为pdPASS */
	BaseType_t xReturn = pdPASS;
	(void)RTE_Init();

	xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* 任务入口函数 */
							(const char*    )"AppTaskCreate",/* 任务名字 */
							(uint16_t       )512,  /* 任务栈大小 */
							(void*          )NULL,/* 任务入口函数参数 */
							(UBaseType_t    )1, /* 任务的优先级 */
							(TaskHandle_t*  )&AppTaskCreate_Handle);/* 任务控制块指针 */ 
	/* 启动任务调度 */           
	if(pdPASS == xReturn) {
		vTaskStartScheduler();   /* 启动任务，开启调度 */
	} else {
		return -1; 
	}
     
#endif
	while(1)
	{
#ifdef EASY_OS
		Priority = osEvt_GetBackPrio();
		while ((Priority & EVT_LV0_PRIO) > 0) 
		{
			if (Os_TaskHdl_lv0() == OS_RET_NG) {
				break;
			}
        	Priority = osEvt_GetBackPrio();
   		} 
#else

#endif
	}
}
