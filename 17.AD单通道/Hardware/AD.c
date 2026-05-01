#include "stm32f10x.h"                  // Device header
void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//设置时钟频率
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AIN;//采用模拟输入
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);//写入哪个通道并设定次序，设定采样时间
	
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;//数据右对齐
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//不使用内部触发，为软件触发
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;//通道独立
	ADC_InitStruct.ADC_NbrOfChannel=1;//扫描模式下用的通道数目
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;
	ADC_Init(ADC1,&ADC_InitStruct);
	
	ADC_Cmd(ADC1,ENABLE);//开启ADC
	ADC_ResetCalibration(ADC1);//复位校准
	while(ADC_GetResetCalibrationStatus(ADC1)==SET);//1说明正在复位初始化等待复位校准完成即可跳出
	ADC_StartCalibration(ADC1);//启动校准
	while (ADC_GetCalibrationStatus(ADC1)==SET);//

//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//如果是连续转换软件触发一次即可

}

uint16_t AD_GetValue(void)
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//软件触发
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);//0说明正在触发跳出即变1触发完成
	return ADC_GetConversionValue(ADC1);
}




