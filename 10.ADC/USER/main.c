#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "string.h"
#include "stdio.h"

void Delay_ms(uint16_t time)
{
 uint16_t i,j;
 for(i = 0; i < time; i++)
 {
  for(j = 0; j < 0x2AFF; j++);
 }
}

void ADC_Gpio(void)
{
 GPIO_InitTypeDef GPIO_ADC0;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
 GPIO_ADC0.GPIO_Mode = GPIO_Mode_AIN;
 GPIO_ADC0.GPIO_Pin = GPIO_Pin_0;
 GPIO_Init(GPIOA, &GPIO_ADC0);
}

void ADC_Config(void)
{
	ADC_InitTypeDef ADC_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_init.ADC_Mode = ADC_Mode_Independent;
	ADC_init.ADC_ScanConvMode = DISABLE;
	ADC_init.ADC_ContinuousConvMode = ENABLE; //DISABLE;
	ADC_init.ADC_ExternalTrigConv =ADC_ExternalTrigConv_None;
	ADC_init.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_init.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1,&ADC_init);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

unsigned int ADCx_Read(void)
{
 return(ADC_GetConversionValue(ADC1));
}

void Uart_Init()
{
	USART_InitTypeDef usart_typedef;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  usart_typedef.USART_BaudRate = 9600;
	usart_typedef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_typedef.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	usart_typedef.USART_Parity = USART_Parity_No;
	usart_typedef.USART_StopBits = USART_StopBits_1;
	usart_typedef.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &usart_typedef);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	NVIC_EnableIRQ(USART1_IRQn);
	USART_Cmd(USART1, ENABLE);
}

int Map(int x, int in_min, int in_max, int out_min, int out_max)	
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Uart_Gpio_TxRx_Init()
{
	GPIO_InitTypeDef gpio_typedef;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
// congifgure pin Tx - A9;
  gpio_typedef.GPIO_Pin = GPIO_Pin_9;
  gpio_typedef.GPIO_Mode = GPIO_Mode_AF_PP;
  gpio_typedef.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&gpio_typedef);
// configure pin Rx - A10;
  gpio_typedef.GPIO_Pin = GPIO_Pin_10;
  gpio_typedef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  gpio_typedef.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&gpio_typedef);
}

void Uart_SendInt(int number)
{
 char count = 0;
 char digit[7] = "";
 if(number==0)
 {
	 USART_SendData(USART1,'0');
	 while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
 }
 if(number>0)
 {
	 while(number!=0)
	 {
		 digit[count]=number%10;
		 count++;
		 number=number/10;
	 }
	 while(count!=0)
	 {
		 USART_SendData(USART1,digit[count-1]+0x30);
		 while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
		 count--;
	 }
 }
 if(number<0)
 {
	 number=-number;
	 while(number!=0)
	 {
		 digit[count]=number%10;
		 count++;
		 number=number/10;
	 }
	 USART_SendData(USART1,'-');
	 while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	 while(count!=0)
	 {
		 USART_SendData(USART1,digit[count-1]+0x30);
		 while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
		 count--;
	 }
 }
}

void Uart_SendChar(char _chr)
{
  USART_SendData(USART1, _chr);
  while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

int main()
{
	ADC_Gpio();
	ADC_Config();
	Uart_Gpio_TxRx_Init();
	Uart_Init();
	while(1)
	{
		Uart_SendInt(ADCx_Read());
		USART_SendData(USART1,'\n');
		Delay_ms(100);
	}
}
