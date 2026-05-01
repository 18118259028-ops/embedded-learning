#include "stm32f10x.h"                  // Device header

extern uint16_t Num;

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStcture;
	GPIO_InitStcture.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStcture.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStcture.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStcture);
	
	
	//内部时钟就是设定psc和arr使得系统内部数数时间到预定值产生中断加1
	//外部时钟就是读取引脚电平边缘，读取有效边缘（psc）并计数，然后计数到自动重装值（arr）产生一次中端然后加1
	
	
	
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, 
                             TIM_ExtTRGPolarity_NonInverted, 0x00);//选择外部时钟模式2
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1 ;     //分频到滤波器,此处1不分频
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=10-1 ; //ARR，计多少次cnt才更新一次中断
	TIM_TimeBaseInitStruct.TIM_Prescaler= 1-1;//PSE,多少个有效边沿计数一次
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0 ;//高级定时器的重复计数功能	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update) ;// 手动清除标志位直接进入预分频器
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef  NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn ;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM2, ENABLE);//开启定时器

}

uint16_t Timer_GetCounter(void)
{
	return TIM_GetCounter(TIM2);
	
}


void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update)==SET)//检测哪个定时器工作
	{
		
		Num ++;//定时器中断触发才加


	 TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	//清除中断标志位
	}
	
	
	
}	














