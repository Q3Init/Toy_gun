#include "App_test.h"
#include "Lib_Log_Util.h"
#include "OS_TASK.h"
#include "MCAL_Timer.h"
#include "MCAL_GPIO.h"
#include "mpu6050.h"

float32 Pitch,Roll,Yaw;

void APP_test_init(void)
{

}

void APP_test_mainfunction(void)
{
    Read_DMP(&Pitch,&Roll,&Yaw);
    Log_d("channels:%2.f,%2.f,%2.f\r\n",Pitch,Roll,Yaw);
    MCAL_GPIO_FlipcBit(GPIOC,GPIO_Pin_13);
}

