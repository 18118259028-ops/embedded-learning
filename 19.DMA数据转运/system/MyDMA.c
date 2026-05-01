#include "stm32f10x.h"                  // Device header

uint16_t MyDMA_Size;

void MyDMA_Init(uint32_t AddrA,uint32_t AddrB,uint16_t Size)
{	
	MyDMA_Size=Size;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_PeripheralBaseAddr=AddrA;//外设起始地址（32位）
	DMA_InitStruct.DMA_PeripheralDataSize= DMA_PeripheralDataSize_Byte; //数据宽度
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Enable; //地址是否自增
	
	DMA_InitStruct.DMA_MemoryBaseAddr=AddrB;//存储器
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte; 
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralSRC ;//传输方向
	DMA_InitStruct.DMA_BufferSize=Size;//传输计数器
	DMA_InitStruct.DMA_Mode=DMA_Mode_Normal ;//是否使用自动重装
	DMA_InitStruct.DMA_M2M=DMA_M2M_Enable;//选择存储器软件（EN）触发还是硬件触发
	DMA_InitStruct.DMA_Priority=DMA_Priority_Medium ;//优先级
	
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	DMA_Cmd(DMA1_Channel1, DISABLE);
}	


void MyDMA_Transfer(void)//调用一次转运一次
{
	DMA_Cmd(DMA1_Channel1, DISABLE);//失能DMA
	DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size); //重新赋值计数器
	DMA_Cmd(DMA1_Channel1, ENABLE);
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);//等待标志位置1
	DMA_ClearFlag(DMA1_FLAG_TC1);
	
}
	
	
