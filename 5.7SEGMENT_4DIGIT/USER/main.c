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

void seg_Init()
{
	GPIO_InitTypeDef led_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	led_init.GPIO_Mode = GPIO_Mode_Out_PP;
	led_init.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_12|GPIO_Pin_3|GPIO_Pin_11|GPIO_Pin_5|GPIO_Pin_6;
  led_init.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&led_init);
}

void digit_Init()
{
	GPIO_InitTypeDef digit_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	digit_init.GPIO_Mode = GPIO_Mode_Out_PP;
	digit_init.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  digit_init.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&digit_init);
}

unsigned char led7Hex[]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void LED7_writeByte (unsigned char b)
{
  if(((b>>0)& 0x01)==0)
  {
    GPIO_ResetBits(GPIOA,GPIO_Pin_0);
  }
  else
  {
    GPIO_SetBits(GPIOA,GPIO_Pin_0);
  }
  if(((b>>1)& 0x01)==0)
  {
    GPIO_ResetBits(GPIOA,GPIO_Pin_1);
  }
  else
  {
    GPIO_SetBits(GPIOA,GPIO_Pin_1);
  }
  if(((b>>2)& 0x01)==0)
  {
    GPIO_ResetBits(GPIOA,GPIO_Pin_12);
  }
  else
  {
    GPIO_SetBits(GPIOA,GPIO_Pin_12);
  }
  if(((b>>3)& 0x01)==0)
  {
    GPIO_ResetBits(GPIOA,GPIO_Pin_3);
  }
  else
  {
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
  }
  if(((b>>4)& 0x01)==0)
  {
    GPIO_ResetBits(GPIOA,GPIO_Pin_11);
  }
  else
  {
    GPIO_SetBits(GPIOA,GPIO_Pin_11);
  }
  if(((b>>5)& 0x01)==0)
  {
    GPIO_ResetBits(GPIOA,GPIO_Pin_5);
  }
  else
  {
    GPIO_SetBits(GPIOA,GPIO_Pin_5);
  }
  if(((b>>6)& 0x01)==0)
  {
    GPIO_ResetBits(GPIOA,GPIO_Pin_6);
  }
  else
  {
    GPIO_SetBits(GPIOA,GPIO_Pin_6);
  }
}

int main()
{
	int i,j;
	seg_Init();
	digit_Init();
	while(1)
	{
		for(i=0;i<=9999;i++)
		{
			for(j=0;j<=100;j++)
			{
				GPIO_SetBits(GPIOB,GPIO_Pin_12);
				LED7_writeByte (led7Hex[i%10]);
				delay_ms(1);
				GPIO_ResetBits(GPIOB,GPIO_Pin_12);
				
				GPIO_SetBits(GPIOB,GPIO_Pin_13);
				LED7_writeByte (led7Hex[(i/10)%10]);
				delay_ms(1);
				GPIO_ResetBits(GPIOB,GPIO_Pin_13);
				
				GPIO_SetBits(GPIOB,GPIO_Pin_14);
				LED7_writeByte (led7Hex[(i/100)%10]);
				delay_ms(1);
				GPIO_ResetBits(GPIOB,GPIO_Pin_14);
				
				GPIO_SetBits(GPIOB,GPIO_Pin_15);
				LED7_writeByte (led7Hex[i/1000]);
				delay_ms(1);
				GPIO_ResetBits(GPIOB,GPIO_Pin_15);
			}
		}
	}
}