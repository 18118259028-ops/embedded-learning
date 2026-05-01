#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"
int16_t Speed;			//定义在定时器中断里自增的变量

int main(void)
{

	OLED_Init();		//OLED初始化
	Timer_Init();		//定时中断初始化
	Encoder_Init();
	OLED_ShowString(1, 1, "Speed:");			//1行1列显示字符串Num:
	
	while (1)
	{
		OLED_ShowSignedNum(1, 7, Speed, 5);			//不断刷新显示Num变量
	}
}

void TIM2_IRQHandler(void)//利用定时器2的中断函数来每隔一秒产生一次读数
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)		//判断是否是TIM2的更新事件触发的中断
	{
		Speed=Encoder_Get();												//Num变量自增，用于测试定时中断
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);			//清除TIM2更新事件的中断标志位
															//中断标志位必须清除
															//否则中断将连续不断地触发，导致主程序卡死
	}
}
