#ifndef EXT_MPU6050_H_
#define EXT_MPU6050_H_

#include "Platform_Types.h"
#include "stm32f10x.h"

#define MPU6050_RA_SMPLRT_DIV       0x19
#define MPU6050_RA_CONFIG           0x1A
#define MPU6050_RA_GYRO_CONFIG      0x1B
#define MPU6050_RA_ACCEL_CONFIG     0x1C

#define MPU6050_RA_PWR_MGMT_1       0x6B
#define MPU6050_RA_PWR_MGMT_2       0x6C

#define MPU6050_WHO_AM_I        0x75
#define MPU6050_SMPLRT_DIV      0  //8000Hz  fix me
#define MPU6050_DLPF_CFG        0  //fix me
#define MPU6050_GYRO_OUT        0x43     //MPU6050陀螺仪数据寄存器地址
#define MPU6050_ACC_OUT         0x3B     //MPU6050加速度数据寄存器地址

#define MPU6050_SLAVE_ADDRESS (0x68<<1)
#define MPU6050_RA_TEMP_OUT_H 0x41

extern void i2c_GPIO_Config(void);
extern void i2c_Start(void);
extern void i2c_Stop(void);
extern void i2c_SendByte(uint8_t _ucByte);
extern uint8_t i2c_ReadByte(u8 ack);
extern uint8_t i2c_WaitAck(void);
extern void i2c_Ack(void);
extern void i2c_NAck(void);
extern uint8_t i2c_CheckDevice(uint8_t _Address);
extern void MPU6050_Init(void);
extern void MPU6050_WriteReg(u8 reg_add,u8 reg_dat);
extern void MPU6050_ReadData(u8 reg_add,unsigned char*Read,u8 num);
extern void MPU6050ReadGyro(short *gyroData);
extern void MPU6050ReadAcc(short *accData);
extern void MPU6050_ReturnTemp(float *Temperature);
extern uint8_t MPU6050ReadID(void);

#endif
