#include "exit.h"

extern uint8_t flag_exti15;
extern uint8_t flag_exti14;
extern uint16_t time;
extern uint16_t flag_out;

void delay_ms(uint16_t time)
{
   uint16_t i,j;
   for(i = 0; i < time; i++)
	 {
    for(j = 0; j < 0x2aff; j++);
   }
}

void led_Init()
{
  GPIO_InitTypeDef led_init;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  led_init.GPIO_Mode  = GPIO_Mode_Out_PP;
  led_init.GPIO_Pin   = GPIO_Pin_1;
  led_init.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&led_init);
}

void button_Init()
{
	GPIO_InitTypeDef button_init;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	button_init.GPIO_Mode =GPIO_Mode_IPU;
  	button_init.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
  	button_init.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA,&button_init);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource14);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);
}

void exti_Init(void)
{
	EXTI_InitTypeDef exti_init;
	exti_init.EXTI_Line=EXTI_Line14|EXTI_Line15;
	exti_init.EXTI_Mode=EXTI_Mode_Interrupt;
	exti_init.EXTI_Trigger=EXTI_Trigger_Falling;
	exti_init.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti_init);
}

void nvic_Init(void)
{
	NVIC_InitTypeDef NVIC_ST;
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_ST.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_ST.NVIC_IRQChannelSubPriority=0;
	NVIC_ST.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_ST);
}

void EXTI15_10_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line14)!=RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line14);
			flag_exti14 = 1;
	}
	else if(EXTI_GetITStatus(EXTI_Line15)!=RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line15);
			flag_exti15 = 1;
	}	
}
