#include "App_test.h"
#include "Lib_Log_Util.h"
#include "OS_TASK.h"
#include "MCAL_Timer.h"
#include "MCAL_GPIO.h"
#include "mpu6050.h"
#include "OLED.h"
#include "stdio.h"		
#include "RF_SPI.h"
#include "RF.h"

uint8 string[10] = {0};	
float32 Pitch,Roll,Yaw;
uint8_t Send_Test[8]={1,2,3,4,5,6,7,8};//发送测试数据
uint16 tick;

void APP_test_init(void)
{
	RF_GPIO_Init();//射频引脚初始化
    RF_SPI_Init();//射频SPI通讯初始化
	RF_Init(); //射频初始化
	Delay_ms(200);
	RF_Tx_Mode();//设置为发射模式
}

void APP_test_mainfunction(void)
{
    tick++;
    Read_DMP(&Pitch,&Roll,&Yaw);
    // Log_d("channels:%2.f,%2.f,%2.f\r\n",Pitch,Roll,Yaw);
    MCAL_GPIO_FlipcBit(GPIOC,GPIO_Pin_13);
    sprintf((char *)string,"Pitch:%.2f",Pitch);//0300
    OLED_ShowString(16,16,string,16);
    sprintf((char *)string,"Roll :%.2f",Roll);//0300
    OLED_ShowString(16,32,string,16);
    sprintf((char *)string,"Yaw  :%.2f",Yaw);//0300
    OLED_ShowString(16,48,string,16);
    OLED_Refresh();
    if (tick == 5) {
        tick = 0;
        RF_Reset();//复位RF
        RFAPIChannelNext();//跳频
        RF_Send_Data(Send_Test);//发送数据
    }
}

