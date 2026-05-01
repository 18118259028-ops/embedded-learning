#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[4];


void AD_Init(void)
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AIN;//采用模拟输入
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);	

	ADC_RegularChannelConfig(ADC1,ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
	
	
	
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_ContinuousConvMode=ENABLE;//单次扫描或连续扫描
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;//数据右对齐
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//不使用内部触发为软件触发
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;//通道独立
	ADC_InitStruct.ADC_NbrOfChannel=4;//扫描模式下用的通道数目（最好用DMA实现）
	ADC_InitStruct.ADC_ScanConvMode=ENABLE;//开启扫描模式
	ADC_Init(ADC1,&ADC_InitStruct);
	
	
	DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)&ADC1->DR;//外设起始地址（32位）
	DMA_InitStruct.DMA_PeripheralDataSize= DMA_PeripheralDataSize_HalfWord; //数据宽度此处低16位是adc1的数据
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //地址是否自增
	DMA_InitStruct.DMA_MemoryBaseAddr=(uint32_t)AD_Value;//存储器
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord; 
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralSRC ;//传DMA_MemoryInc_Enable;输方向
	DMA_InitStruct.DMA_BufferSize=4;//传输计数器
	DMA_InitStruct.DMA_Mode=DMA_Mode_Circular ;//是否使用自动重装
	DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;//选择存储器软件（EN）触发还是硬件触发
	DMA_InitStruct.DMA_Priority=DMA_Priority_Medium ;//优先级
	
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	ADC_DMACmd(ADC1,ENABLE);
	
	ADC_Cmd(ADC1,ENABLE);//开启ADC
	
	ADC_ResetCalibration(ADC1);//复位校准
	while(ADC_GetResetCalibrationStatus(ADC1)==SET);//1说明正在复位初始化等待复位校准完成即可跳出
	ADC_StartCalibration(ADC1);//启动校准
	while (ADC_GetCalibrationStatus(ADC1)==SET);//

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//如果是连续转换软件触发一次即可

}




