#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void Key_Init(void)						// Init初始化Key
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU;//推挽引脚一开始为高电平
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_11;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);	
} 

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum=0;//这里的0代表按键无状态
	if (GPIO_ReadInputDataBit( GPIOB,GPIO_Pin_1)==0)//这里的0指的是引脚低电平按键按下
	{
		Delay_ms(20);//消抖
		while(GPIO_ReadInputDataBit( GPIOB,GPIO_Pin_1)==0)//检测是否松手，未松手就继续循环检测，松手进入下一行
		Delay_ms(20);	
		KeyNum=1;                   //完成一次按键
		
	}
	if (GPIO_ReadInputDataBit( GPIOB,GPIO_Pin_11)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit( GPIOB,GPIO_Pin_11)==0)
		Delay_ms(20);	
		KeyNum=2;                     
		
	}
	
	return KeyNum;
}		
