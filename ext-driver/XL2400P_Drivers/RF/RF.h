#ifndef	RF_H
#define	RF_H

/************************ 寄存器定义 ******************************/

#define CFG_TOP				(0X00)//配置寄存器
#define	EN_AA				(0X01)//使能自动应答寄存器
#define	EN_RXADDR			(0X02)//接收地址允许寄存器
#define	SETUP_AW			(0X03)//设置地址宽度
#define	SETUP_RETR			(0X04)//
#define	RF_CH				(0X05)//频点 RF通道 工作通道频率
#define	RF_SETUP			(0X06)
#define	RF_STATUS			(0X07)//状态寄存器
#define	OBSERVE_TX			(0X08)
#define	RSSI				(0X09)
#define	RX_ADDR_P0			(0X0A)
#define	RX_ADDR_P1			(0X0B)
#define	RX_ADDR_P2			(0X2)
#define	RX_ADDR_P3			(0X3)
#define	RX_ADDR_P4			(0X4)
#define	RX_ADDR_P5			(0X5)
#define	RX_ADDR_P2TOP5		(0X0C)
#define	BER_RESULT			(0X0D)
#define	AGC_SETTING			(0X0E)
#define	PGA_SETTING			(0X0F)
#define	TX_ADDR				(0X10)
#define	RX_PW_PX			(0X11)
#define	ANALOG_CFG0			(0X12)
#define	ANALOG_CFG1			(0X13)
#define	ANALOG_CFG2			(0X14)
#define	ANALOG_CFG3			(0X15)
#define	STATUS_FIFO			(0X17)
#define	RSSIREC				(0X18)
#define	TXPROC_CFG			(0X19)
#define	RXPROC_CFG			(0X1A)	
#define	DYNPD				(0X1C)
#define	FEATURE				(0X1D)
#define	RAMP_CFG			(0X1E)


/************************ 操作指令 ******************************/

#define R_REG					0x00
#define	R_REGISTER				0x00//读寄存器指令                        				
#define W_REG 					0x20//写寄存器指令
#define	W_REGISTER				0x20//写寄存器指令
#define R_RX_PLOAD 			0x61//读接收数据，读操作通常由第 0 字节开始，读完过后数据将从 RX FIFO 中删除，接收模式下执行。
#define W_TX_PLOAD			0xA0//写发射数据，写操作通常由 0 字节开始
#define FLUSH_TX			0xE1//清 TX FIFO   
#define FLUSH_RX			0xE2//清 RX FIFO 
#define REUSE_TX_PL			0xE3//用在 PTX 端，再次使用最后一帧发送的数据并且发送。该命令在刚发送数据并执行 FLUSH_TX 命令后可用。该命令不可以在发送数据的过程中使用

#define R_RX_PL_WID			0x60//读 RX FIFO 最顶部 RX-payload 数据宽度
#define W_ACK_PLOAD			0xA8//
#define W_TX_PLOAD_NOACK	0xB0//
#define CMD_NOP				0xFF//空操作。可用来操作状态寄存器

/* STATUS Interrupt status */
#define RX_DR    		(0x40)//接收到数据中断标志位
#define TX_DS    		(0x20)//发送数据完成中断标志位
#define MAX_RT   		(0x10)//达到最大发送次数中断标志位

//////////////////////////RF parameter//////////////////////////////////////////
//1Mpbs---->0dBm
//250Kpbs:
#define	C_RF10dBm               0x3f                            				// 10dBm
#define	C_RF9dBm                0x38                            				// 9dbm
#define	C_RF8dBm                0x34                            				// 8dbm
#define	C_RF7dBm                0x30                            				// 7dbm
#define	C_RF6dBm                0x2c                            				// 6dbm
#define	C_RF5dBm                0x28                            				// 5dbm
#define	C_RF4dBm                0x24                            				// 4dbm
#define	C_RF3dBm                0x20                            				// 3dbm
#define	C_RF2dBm                0x14                            				// 2dbm
#define	C_RF0dBm                0x10                            				// 0dBm
#define	C_RF_2dBm               0x0c                            				// -2dBm
#define	C_RF_6dBm               0x08                            				// -6dBm
#define	C_RF_12dBm              0x04                            				// -12dBm
#define	C_RF_18dBm              0x02                            				// -18dBm
#define	C_RF_24dBm              0x01                            				// -24dBm
//---------------------------------------------------------------
#define C_DR_1M                 0x02						//1Mpbs					
#define C_DR_250K               0x22					   //250Kpbs			
//---------------------------------------------------------------

//----------------------------------------------------------
#define RF_PACKET_SIZE			8//数据长度


void RF_Init(void);
void RF_CE_High(void);
void RF_CE_Low(void);
void RF_Clear_Buf(void);
void RF_Reset(void);
void RF_Set_Chn(unsigned char Chn);
void RF_Set_Address(unsigned char * AddrBuff);
void RF_Set_Power(unsigned char Power);
void RF_Sleep(void);
void RF_Tx_Mode(void);
void RF_Rx_Mode(void);
void RFAPIChannelNext(void);
void RFAPIChannelNext_RX(void);

unsigned char RF_Send_Data(unsigned char *Data_Buff ,unsigned char Send_len);





#endif
