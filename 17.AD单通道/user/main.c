#include "stm32f10x.h"                  // Device header
#include "Delay.h" 
#include "OLED.h" 
#include "AD.h" 

uint16_t ADValue;
double Voltage;//用float也可以
int main(void)
{
	OLED_Init();
	AD_Init();
	OLED_ShowString(1,1,"ADVaule:");
	OLED_ShowString(2,1,"Voltage:0.00V");
	while(1)
	{
	ADValue=AD_GetValue();
	OLED_ShowNum(1,9,ADValue,4);
	Voltage=(double)ADValue/4095*3.3;
	OLED_ShowNum(2,9,Voltage,1);	
	OLED_ShowNum(2,11,(uint16_t)(Voltage*100)%100,2);
	
	Delay_ms(100);
	}
}
