#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=100-1;//ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler=720-1;//PSC
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit( TIM2, & TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef  TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);// 结构体赋默认初始值，这样写结构体写自己需要的就行
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1 ;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High ;//定义有效电平是高电平
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable ;
	TIM_OCInitStruct.TIM_Pulse=50 ;//CCR的值
	TIM_OC3Init(TIM2,&TIM_OCInitStruct);
	
	 
	GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_AF_PP;//定时器属于片上外设，控制引脚要采用复用输出
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;//若重映射改为相应映射引脚
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIO_InitStruct);

	TIM_Cmd(TIM2,ENABLE);	
}

void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM2,Compare);
	  
	
}




