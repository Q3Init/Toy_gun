#include "FreeRTOS_TASK.h"
/* user file */


 /* 创建任务句柄 */
TaskHandle_t AppTaskCreate_Handle = NULL;


void AppTaskCreate(void)
{
#ifndef EASY_OS
  BaseType_t xReturn = pdPASS;
  
  taskENTER_CRITICAL();
  
  vTaskDelete(AppTaskCreate_Handle); //删除AppTaskCreate任务
  
  taskEXIT_CRITICAL();            //退出临界区
#endif
}
