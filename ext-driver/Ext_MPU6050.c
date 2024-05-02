#include "Ext_MPU6050.h"
#include "stm32f10x.h"
#include "Lib_Log_Util.h"

#define I2C_WR 0

#define GPIO_PORT_I2C	GPIOB			/* GPIO端口*/
#define RCC_I2C_PORT 	RCC_APB2Periph_GPIOB		/* GPIO时钟*/
#define I2C_SCL_PIN		GPIO_Pin_10			/* 连接SCL的GPIO */
#define I2C_SDA_PIN		GPIO_Pin_11			/* 连接SDL的GPIO */

#define I2C_SCL_1()  GPIO_SetBits(GPIO_PORT_I2C, I2C_SCL_PIN)		/* SCL = 1 */
#define I2C_SCL_0()  GPIO_ResetBits(GPIO_PORT_I2C, I2C_SCL_PIN)		/* SCL = 0 */

#define I2C_SDA_1()  GPIO_SetBits(GPIO_PORT_I2C, I2C_SDA_PIN)		/* SDA = 1 */
#define I2C_SDA_0()  GPIO_ResetBits(GPIO_PORT_I2C, I2C_SDA_PIN)		/* SDA = 0 */

#define I2C_SDA_READ()  GPIO_ReadInputDataBit(GPIO_PORT_I2C, I2C_SDA_PIN)	/*读SDA数据 */

static void i2c_Delay(void)
{
	uint8_t i;
	for (i = 0; i < 10; i++);
}

//当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号
void i2c_Start(void)
{
    /*    _____
     *SDA      \_____________
     *    __________
     *SCL           \________
     */
	I2C_SDA_1();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
}

//当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号
void i2c_Stop(void)
{
    /*               _______
     *SDA __________/
     *          ____________
     *SCL _____/
     */
	I2C_SDA_0();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_1();
}

/*CPU向I2C总线设备发送8bit数据

*/
void i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	/* 先发送高7位，*/
	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			I2C_SDA_1();//发送的1
		}
		else
		{
			I2C_SDA_0();//发送的0
		}
		i2c_Delay();
		I2C_SCL_1();
		i2c_Delay();	
		I2C_SCL_0();
		if (i == 7)
		{
			 I2C_SDA_1(); //释放总线
		}
		_ucByte <<= 1;	/*左移一个 bit */
		i2c_Delay();
	}
}

/*
CPU从I2C设备读取8bit数据
*/
uint8_t i2c_ReadByte(u8 ack)
{
	uint8_t i;
	uint8_t value;

	/* 读取到第一个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		I2C_SCL_1();
		i2c_Delay();
		if (I2C_SDA_READ())
		{
			value++;
		}
		I2C_SCL_0();
		i2c_Delay();
	}
	if(ack==0)
		i2c_NAck();
	else
		i2c_Ack();
	return value;
}

/*
CPU产生一个时钟，并读取器件的ACK应答信号
*/
uint8_t i2c_WaitAck(void)
{
	uint8_t re;

	I2C_SDA_1();	/* CPU释放SDA总线 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU驱动SCL = 1, 此器件会返回ACK应答 */
	i2c_Delay();
	if (I2C_SDA_READ())	/* CPU读取SDA口状态 */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	I2C_SCL_0();
	i2c_Delay();
	return re;
}

/*
CPU产生一个ACK信号

*/
void i2c_Ack(void)
{

    /*           ____
     *SCL ______/    \______
     *    ____         _____
     *SDA     \_______/
     */
	I2C_SDA_0();	/* CPU驱动SDA = 0 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU产生1个时钟 */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
	I2C_SDA_1();	/* CPU释放SDA总线 */
}

/*
CPU产生1个NACK信号
*/
void i2c_NAck(void)
{
    /*           ____
     *SCL ______/    \______
     *    __________________
     *SDA
     */
	I2C_SDA_1();	/* CPU驱动SDA = 1 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU产生一个时钟 */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();	
}

/*
配置I2C总线的GPIO
*/
void i2c_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_I2C_PORT, ENABLE);	//时钟

	GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN | I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //开漏输出
	GPIO_Init(GPIO_PORT_I2C, &GPIO_InitStructure);

	//停止信号，复位I2C总线上的所有设备
	i2c_Stop();
}

/*
CPU发送设备地址，然后读取设备应答是否有设备
*/
uint8_t i2c_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;

	i2c_GPIO_Config();		/* 配置GPIO */
	
	i2c_Start();		/*I2C开始信号*/

	/* 发送设备地址和读写控制bit（0=写，1=读）bit7位先传 */
	i2c_SendByte(_Address|I2C_WR);
	ucAck = i2c_WaitAck();	/*检测设备应答 */

	i2c_Stop();			/* I2C结束信号 */

	return ucAck;
}

void MPU6050_WriteReg(u8 reg_add,u8 reg_dat)
{
	i2c_Start();
	i2c_SendByte(MPU6050_SLAVE_ADDRESS);
	i2c_WaitAck();
	i2c_SendByte(reg_add);
	i2c_WaitAck();
	i2c_SendByte(reg_dat);
	i2c_WaitAck();
	i2c_Stop();
}

void MPU6050_ReadData(u8 reg_add,unsigned char*Read,u8 num)
{
	unsigned char i;
	
	i2c_Start();
	i2c_SendByte(MPU6050_SLAVE_ADDRESS);
	i2c_WaitAck();
	i2c_SendByte(reg_add);
	i2c_WaitAck();
	
	i2c_Start();
	i2c_SendByte(MPU6050_SLAVE_ADDRESS+1);
	i2c_WaitAck();
	
	for(i=0;i<(num-1);i++){
		*Read=i2c_ReadByte(1);
		Read++;
	}
	*Read=i2c_ReadByte(0);
	i2c_Stop();
}


void MPU6050_Init(void)
{
  int i=0,j=0;
  for(i=0;i<1000;i++)
  {
    for(j=0;j<1000;j++);
  }
	MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x01);
	MPU6050_WriteReg(MPU6050_RA_SMPLRT_DIV , 0x07);	//值得设置
	MPU6050_WriteReg(MPU6050_RA_CONFIG , 0x03);//值得设置
	MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG , 0x00);
	MPU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);
}

void MPU6050ReadGyro(short *gyroData)
{
    u8 buf[6];
    MPU6050_ReadData(MPU6050_GYRO_OUT,buf,6);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}

void MPU6050ReadAcc(short *accData)
{
    u8 buf[6];
    MPU6050_ReadData(MPU6050_ACC_OUT, buf, 6);
    accData[0] = (buf[0] << 8) | buf[1];
    accData[1] = (buf[2] << 8) | buf[3];
    accData[2] = (buf[4] << 8) | buf[5];
}

void MPU6050_ReturnTemp(float *Temperature)
{
	short temp3;
	u8 buf[2];
	
	MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2); 
    temp3= (buf[0] << 8) | buf[1];	
	*Temperature=((double) temp3/340.0)+36.53;
}

uint8_t MPU6050ReadID(void)
{
	unsigned char Re = 0;
	MPU6050_ReadData(0x75,&Re,1); //读器件地址
	if (Re != 0x68) {
		Log_d("check MPU6050 module fail\r\n");
		return 0;
 	} else {
		Log_d("MPU6050 ID = %d\r\n",Re);
	    return 1;
	}
}
