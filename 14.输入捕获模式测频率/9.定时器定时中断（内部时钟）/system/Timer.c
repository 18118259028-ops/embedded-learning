#include "stm32f10x.h"                  // Device header

extern uint16_t Num;

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//1.开启RCC时钟

	TIM_InternalClockConfig(TIM2);//2.选择对应的定时器
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1 ;     //分频到滤波器,此处/1不分频
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数模式
	TIM_TimeBaseInitStruct.TIM_Period=10000-1 ; //ARR自动重装计数器
	TIM_TimeBaseInitStruct.TIM_Prescaler= 7200-1;//PSE预分频
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0 ;//高级定时器的重复计数功能	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);//3.配置时钟时基单元结构体并读取
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update) ;// 手动清除标志位直接进入预分频器
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//4.使定时器连接到NVIC

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//NVIC先分组
	NVIC_InitTypeDef  NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn ;//根据芯片存储类型和所用定时器选择
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStruct);//5.配置NVIC初始化结构体
	
	TIM_Cmd(TIM2, ENABLE);//6.开启定时器

}

void TIM2_IRQHandler(void)//7.配置定时器中断函数
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update)==SET)
	{
		
		Num ++;


	 TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	//清零中断标志位防止卡在函数里
	}
	
	
	
}	














