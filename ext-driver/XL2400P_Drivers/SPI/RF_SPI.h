#ifndef	RF_SPI_H
#define	RF_SPI_H

#include "sys.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "Platform_Types.h"

#define RF_SPI 3
/*********************************************** 三线SPI ***********************************************************/
#if RF_SPI == 3//-------------------------------------------------------------------------------

#define SPI_BUS_CLOCK             RCC_APB2Periph_GPIOB
#define SPI_GPIOX                 GPIOB

#define SPI_DATA_GPIO_PIN         GPIO_Pin_12  //DATA
#define SPI_SCK_GPIO_PIN          GPIO_Pin_13  //SCK
#define SPI_CSN_GPIO_PIN          GPIO_Pin_14  //CSN 

#define SCK_High                  GPIO_WriteBit(SPI_GPIOX, GPIO_Pin_13, Bit_SET)
#define SCK_Low                   GPIO_WriteBit(SPI_GPIOX, GPIO_Pin_13, Bit_RESET);

#define SPI_DATA_High             GPIO_WriteBit(SPI_GPIOX, GPIO_Pin_12, Bit_SET);
#define SPI_DATA_Low              GPIO_WriteBit(SPI_GPIOX, GPIO_Pin_12, Bit_RESET);

#define CSN_Low                   GPIO_WriteBit(SPI_GPIOX, GPIO_Pin_14, Bit_SET);
#define CSN_High                  GPIO_WriteBit(SPI_GPIOX, GPIO_Pin_14, Bit_RESET);

#define Read_DATA                 GPIO_ReadOutputDataBit(SPI_GPIOX,GPIO_Pin_12)

/*********************************************** 四线SPI ***********************************************************/
#else//-----------------------------------------------------------------------------------------

#define SPI_MISO_GPIO_PIN         GPIO_PIN_1 //PF1
#define SPI_MOSI_GPIO_PIN         GPIO_PIN_3 //PF3
#define SPI_SCK_GPIO_PIN          GPIO_PIN_0 //PA0
#define SPI_CSN_GPIO_PIN          GPIO_PIN_1 //PA1

#define SCK_High                  GPIO_WriteBit(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
#define SCK_Low                   GPIO_WriteBit(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);

#define SPI_MOSI_High             GPIO_WriteBit(GPIOF, GPIO_PIN_3, GPIO_PIN_SET);
#define SPI_MOSI_Low              GPIO_WriteBit(GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);

#define CSN_Low		              GPIO_WriteBit(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
#define CSN_High		          GPIO_WriteBit(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);

#define Read_MISO                 GPIO_ReadInputDataBit(GPIOF,GPIO_PIN_1)

#endif//---------------------------------------------------------------------------------------

/*********************************************** 函数声明 ***********************************************************/

void RF_GPIO_Init(void);
void RF_SPI_Init(void);
void SPI_Write_Byte(unsigned char buff);
unsigned char SPI_Read_Byte(void);
void SPI_Write_Reg(unsigned char RfAdress,unsigned char RfData);
unsigned char SPI_Read_Reg(unsigned char RfAdress);
void Write_RF_Buff(unsigned char RFAdress , unsigned char *pBuff , unsigned char Len);
void Read_RF_Buff(unsigned char RFAdress , unsigned char *pBuff , unsigned char Len);

#endif

