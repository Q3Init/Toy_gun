#include "App_test.h"
#include "Ext_MPU6050.h"
#include "Lib_Log_Util.h"

uint8 id_ret = 0;
sint16 Accel[3];
sint16 Gyro[3];
float32 Temp;
uint16 tick = 0;

void APP_test_init(void)
{
    i2c_GPIO_Config();
    MPU6050_Init();
    id_ret = MPU6050ReadID();
    Log_d("id_ret : %d\r\n",id_ret);
}

void APP_test_mainfunction(void)
{

    if (id_ret == 1) {
        MPU6050ReadAcc(Accel);			
        Log_d("Accel [%8d][%8d][%8d]\r\n",Accel[0],Accel[1],Accel[2]);
        MPU6050ReadGyro(Gyro);
        Log_d("Gyro: [%8d][%8d][%8d]\r\n",Gyro[0],Gyro[1],Gyro[2]);				
        MPU6050_ReturnTemp(&Temp); 
        Log_d("Temp: [%8.2f]\r\n",Temp);		
    }
}

