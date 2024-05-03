#include "MCAL_Timer.h"


void MCAL_TIMER_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	TIM_TimeBaseInitStructure.TIM_Period    = 50000-1; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 60-1;     //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
}

//微秒级延时
void Delay_us(u16 xus)
{
	TIM_Cmd(TIM3,ENABLE); //启动定时器
	while(TIM3->CNT < xus);
	TIM3->CNT = 0;
	TIM_Cmd(TIM3,DISABLE); //关闭定时器
}

//毫秒级延时
void Delay_ms(u16 xms)
{
	int i;
	for(i=0;i<xms;i++)
	{
		Delay_us(1000);
	}
}
