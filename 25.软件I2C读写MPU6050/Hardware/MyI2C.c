#include "stm32f10x.h"                  // Device header
#include "Delay.h"  

void MyI2C_w_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);	
	Delay_us(10);
}

void MyI2C_w_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);	
	Delay_us(10);
}

uint8_t MyI2C_R_SDA(void)
{
	uint8_t BitValue;
	BitValue=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return BitValue;
}	


 

void MyI2C_Init(void)//初始化
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_OD;//不是复用，开漏输出也能输入
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_10| GPIO_Pin_11);

} 
void MyI2C_Start(void)//开启
{	MyI2C_w_SDA(1);
	MyI2C_w_SCL(1);
	MyI2C_w_SDA(0);
	MyI2C_w_SCL(0);
}
void MyI2C_Stop(void)//终止
{	MyI2C_w_SDA(0);
	MyI2C_w_SCL(1);
	MyI2C_w_SDA(1); 
}

void MyI2C_SendByte(uint8_t Byte)
{
   for (uint8_t i = 0; i < 8; i++)
   {
       // 从最高位开始，每次将二进制数整体右移取出当前要发的 bit
       MyI2C_w_SDA(Byte & (0x80 >> i)); 
       MyI2C_w_SCL(1);   // SCL 拉高，从机采样
       MyI2C_w_SCL(0);   // SCL 拉低，准备下一位
   }
}

uint8_t MyI2C_ReceiveByte(void)
{
	 uint8_t Byte = 0x00;
     MyI2C_w_SDA(1);                    // 释放SDA，让从机控制
     for (uint8_t i = 0; i < 8; i++)
      {
          MyI2C_w_SCL(1);                // SCL拉高，从机把数据放到SDA上
          if (MyI2C_R_SDA() == 1)        // 读SDA电平
          {
              Byte |= (0x80 >> i);       // 对应位置1
          }
          MyI2C_w_SCL(0);                // SCL拉低，准备下一位
      }
     return Byte;
}

void MyI2C_SendAck(uint8_t AckBit)
{ 
       MyI2C_w_SDA(AckBit); 
       MyI2C_w_SCL(1);  
       MyI2C_w_SCL(0);   
}

uint8_t MyI2C_ReceiveAck(void)
{
	 uint8_t AckBit;
     MyI2C_w_SDA(1);                    
	 MyI2C_w_SCL(1);               
     AckBit = MyI2C_R_SDA();          
	 MyI2C_w_SCL(0);                
     return AckBit;
}






