#include "RF_SPI.h"

#if RF_SPI == 3/*****************************************************************************************************/
//射频GPIO引脚初始化
void RF_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(SPI_BUS_CLOCK, ENABLE);	 //使能PB端口时钟  

    GPIO_InitStructure.GPIO_Pin = SPI_DATA_GPIO_PIN | SPI_SCK_GPIO_PIN | SPI_CSN_GPIO_PIN;				
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
    GPIO_Init(SPI_GPIOX, &GPIO_InitStructure);					 
    GPIO_SetBits(SPI_GPIOX,SPI_DATA_GPIO_PIN | SPI_SCK_GPIO_PIN | SPI_CSN_GPIO_PIN);			
}

//Data切换为输出
void DATA_Output(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(SPI_BUS_CLOCK, ENABLE);	 //使能PB端口时钟  

    GPIO_InitStructure.GPIO_Pin = SPI_DATA_GPIO_PIN;				
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
    GPIO_Init(SPI_GPIOX, &GPIO_InitStructure);					 
}
//Data切换为输入
void DATA_Input(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(SPI_BUS_CLOCK, ENABLE);	 //使能PB端口时钟  

    GPIO_InitStructure.GPIO_Pin = SPI_DATA_GPIO_PIN;				
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
    GPIO_Init(SPI_GPIOX, &GPIO_InitStructure);					 
}

//SPI写数据（1字节）
//参数 需要写入的数据
void SPI_Write_Byte(unsigned char buff)
{
	DATA_Output();
    for(unsigned char i = 0; i < 8; i++)
	{
        SCK_Low;

        if(buff & 0x80)
		{
            SPI_DATA_High;
		}
        else
		{
            SPI_DATA_Low;
		}

        buff = buff << 1;

        SCK_High;
    }
    SPI_DATA_High;
    SCK_Low;
}

//SPI读数据（1字节）
//返回 读取到的数据
unsigned char SPI_Read_Byte(void)
{
	DATA_Input();
    unsigned char  buff = 0;

    for(unsigned char i = 0; i < 8; i++)
    {
        SCK_Low;
        buff = buff << 1;
        SCK_High;
        if(Read_DATA)
		{
			buff |= 0x01;
		}         
    }
    SCK_Low;

    return buff;
}

#else/*****************************************************************************************************/

//射频GPIO引脚初始化
void RF_GPIO_Init(void)
{
	/*使能模块时钟*/
	__HAL_RCC_GPIOF_CLK_ENABLE();//PF
	__HAL_RCC_GPIOA_CLK_ENABLE();//PA

	GPIO_InitTypeDef   GPIO_InitStruct;
	/* MISO */
    GPIO_InitStruct.Pin   = GPIO_PIN_1;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	/* MOSI */
	GPIO_InitStruct.Pin   = GPIO_PIN_3;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	/* SCK */
    GPIO_InitStruct.Pin   = GPIO_PIN_0;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* CSN */
	GPIO_InitStruct.Pin   = GPIO_PIN_1;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

//SPI写数据（1字节）
//参数 需要写入的数据
void SPI_Write_Byte(unsigned char buff)
{
    for(unsigned char i = 0; i < 8; i++)
	{
        SCK_Low;

        if(buff & 0x80)
		{
            SPI_MOSI_High;
		}
        else
		{
            SPI_MOSI_Low;
		}

        buff = buff << 1;

        SCK_High;
    }
    SPI_MOSI_High;
    SCK_Low;
}

//SPI读数据（1字节）
//返回 读取到的数据
unsigned char SPI_Read_Byte(void)
{  
    unsigned char  buff = 0;

    for(unsigned char i = 0; i < 8; i++)
    {
        SCK_Low;
        buff = buff << 1;
        SCK_High;
        if(Read_MISO)
		{
			buff |= 0x01;
		}         
    }
    SCK_Low;

    return buff;
}

#endif/*****************************************************************************************************/

//SPI通讯初始化
void RF_SPI_Init(void)
{
	CSN_High;
	SCK_Low;
}

//SPI写数据到寄存器
//参数1 寄存器地址+写指令
//参数2 需要写入的数据
void SPI_Write_Reg(unsigned char RfAdress,unsigned char RfData)
{
	CSN_Low;//拉低片选
	SPI_Write_Byte(RfAdress);//1写入地址
	SPI_Write_Byte(RfData);//2写入数据
	CSN_High;//写入完成拉高片选
}

//SPI从寄存器读取数据
//参数 寄存器地址+读指令
//返回 读取到的数据
unsigned char SPI_Read_Reg(unsigned char RfAdress)
{
	unsigned char rTemp;
	CSN_Low;
	SPI_Write_Byte(RfAdress);//写入地址+读取指令
	rTemp = SPI_Read_Byte();//读取数据
	CSN_High;
	return rTemp;
}

//写入多个数据到寄存器
//参数1 寄存器地址+指令
//参数2 需要写入的数据地址
//参数3 写入次数
void Write_RF_Buff(unsigned char RFAdress , unsigned char *pBuff , unsigned char Len)
{
	unsigned char rTemp;
	CSN_Low;
	SPI_Write_Byte(RFAdress);
	for(unsigned char i = 0 ; i < Len ; i++)
	{
		rTemp = pBuff[i];
        SPI_Write_Byte(rTemp);
	}
	CSN_High;
}

//从寄存器读取多个数据
//参数1 寄存器地址+指令
//参数2 读取到的数据存放地址
//参数3 读取的次数
void Read_RF_Buff(unsigned char RFAdress , unsigned char *pBuff , unsigned char Len)
{
	CSN_Low;
	SPI_Write_Byte(RFAdress);
	for(unsigned char i = 0 ; i < Len ; i++)
	{
		pBuff[i] = SPI_Read_Byte();
	}
	CSN_High;
}
