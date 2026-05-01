#include "stm32f10x.h"                  // Device header
#include "Delay.h" 
#include "OLED.h" 
#include "PWM.h" 
#include "IC.h" 

int main(void)
{
	OLED_Init();
	PWM_Init();
	PWM_SetPrescaler(720-1);//频率等于72M/psc+1/ARR+1
	PWM_SetCompare1(50);
	IC_Init();
	OLED_ShowString(1,1,"Freq=00000Hz");
	while(1)
	{
		OLED_ShowNum(1,6,IC_GetFreq(),5);
	
	}
}
