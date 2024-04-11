#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

uint8_t old=1;
uint8_t new=1;
uint8_t onoff=0;

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
  led_init.GPIO_Pin   = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5;
  led_init.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&led_init);
}

void button_Init()
{
	GPIO_InitTypeDef button_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	button_init.GPIO_Mode =GPIO_Mode_IPU;
  button_init.GPIO_Pin = GPIO_Pin_15;
  button_init.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC,&button_init);
}

int main()
{
	led_Init();
	button_Init();
	
	while(1)
	{
		old=new;
		new=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15);
		
		if(new==0 && old==1)
		{
			onoff++;
			if(onoff % 2 == 0)
			{
			 onoff=1;
			 GPIO_ResetBits (GPIOA,GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5);
			}
			else
			{
			 onoff=0;
			 GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5);
			}
		}
	}
}

	

