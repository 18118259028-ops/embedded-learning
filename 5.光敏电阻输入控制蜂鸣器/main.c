#include "stm32f10x.h"                  // Device header
#include "Delay.h" 
#include "LED.h"

int main(void)
{
	LED_Init();                         //初始化
	
	while(1)
	{
		LED1_ON();
		Delay_ms(500);
		LED1_OFF();
		Delay_ms(500);
	}
}
