#include "stm32f10x.h"                  // Device header
#include "Delay.h" 
#include "OLED.h" 
#include "Serial.h" 

int main(void)
{
	OLED_Init();
	Serial_Init();
	Serial_SendByte(0x41);//0x41根据ASCII就是A
	uint8_t MyArray[]={0x41,0x42,0x43,0x44,0x45};
	Serial_SendArray(MyArray,5);
	Serial_SendString("你好，世界!\r\n");
	Serial_SendNumber(12345, 5);
	printf("Num=%d\r\n",666);
	while(1)
	{
		
	
	
	
	}
}
