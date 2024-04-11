#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

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
  led_init.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_3;
  led_init.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&led_init);
}

void led_Blink_1()
{
  GPIO_ResetBits (GPIOA,GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_3);
  delay_ms(1000);
  GPIO_SetBits   (GPIOA,GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_3);
  delay_ms(1000);
}

void led_Blink_2()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	delay_ms(1000);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	delay_ms(1000);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	delay_ms(1000);
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	delay_ms(1000);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	delay_ms(1000);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	delay_ms(1000);
}

void led_Blink_3()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	delay_ms(1000);
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	delay_ms(1000);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	delay_ms(1000);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	delay_ms(1000);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	delay_ms(1000);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	delay_ms(1000);
}

int main()
{
	led_Init();
	while(1)
	{
		led_Blink_3();
	}
}
