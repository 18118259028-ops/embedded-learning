#include "stm32f10x.h"                  // Device header
#include <stdio.h>  
 void Serial_Init(void)
 {	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	 
	 USART_InitTypeDef USART_InitStruct;
	 USART_InitStruct.USART_BaudRate=9600;
	 USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	 USART_InitStruct.USART_Mode=USART_Mode_Tx;
	 USART_InitStruct.USART_Parity=USART_Parity_No;
	 USART_InitStruct.USART_StopBits=USART_StopBits_1;
	 USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	 USART_Init(USART1,  &USART_InitStruct);
	 
	 USART_Cmd(USART1,ENABLE);
 }	 
 
 void Serial_SendByte(uint8_t Byte)//发送字节的函数
 {
	 USART_SendData(USART1, (uint16_t)Byte);
	 while (USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
 }
 
 void Serial_SendArray(uint8_t *Array,uint16_t Length)//发送无符号数组的函数
 {
	 uint16_t i;
	 for(i=0;i<Length;i++)
	 {
		  Serial_SendByte(Array[i]);
	 }
 }
	 
 void Serial_SendString(char *String)//发送字符串
 {
	  uint8_t i;
	 for(i=0;String[i]!=0;i++)
	 {
		  Serial_SendByte(String[i]);
	 }
	 
 }
 
 uint32_t Seria_Pow(uint32_t X,uint32_t Y)//x的Y次方函数
 {
	 uint32_t Result =1;
	 while(Y--)
	 {
		 Result*=X;
	 }
	 return Result;
 }
 
 
 
 void Serial_SendNumber(uint32_t Number,uint8_t Length)	 //发送字符串
 {
	 uint8_t i;
	 for(i=0;i<Length;i++)
	 {
		  Serial_SendByte(Number/Seria_Pow(10,Length-i-1)%10+'0');
	 }
 
 }	 
	 
int fputc(int ch,FILE *f) //将printf重定义到串口
{
	Serial_SendByte(ch);
	return ch;	
}
 
 
 
 