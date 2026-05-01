#include "stm32f10x.h"                  // Device header

void LED_Init(void)						//Init初始化LED
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1| GPIO_Pin_2);
} 


void LED1_ON(void)	                      //点亮1
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}	
void LED1_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	}
}
void LED2_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
}

void LED1_OFF(void)	                      //熄灭1
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}	

void LED2_ON(void)	                      //点亮2
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}	

void LED2_OFF(void)	                      //熄灭2
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}	
