#include "App_test.h"
#include "Lib_Log_Util.h"
#include "OS_TASK.h"
#include "MCAL_Timer.h"
#include "MCAL_GPIO.h"
#include "mpu6050.h"
#include "OLED.h"
#include "stdio.h"		

uint8 string[10] = {0};	
float32 Pitch,Roll,Yaw;

void APP_test_init(void)
{

}

void APP_test_mainfunction(void)
{
    Read_DMP(&Pitch,&Roll,&Yaw);
    Log_d("channels:%2.f,%2.f,%2.f\r\n",Pitch,Roll,Yaw);
    MCAL_GPIO_FlipcBit(GPIOC,GPIO_Pin_13);
    sprintf((char *)string,"Pitch:%.2f",Pitch);//0300
    OLED_ShowString(16,16,string,16);
    sprintf((char *)string,"Roll :%.2f",Roll);//0300
    OLED_ShowString(16,32,string,16);
    sprintf((char *)string,"Yaw  :%.2f",Yaw);//0300
    OLED_ShowString(16,48,string,16);
    OLED_Refresh();
}

