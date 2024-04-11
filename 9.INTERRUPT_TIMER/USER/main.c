#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

char flag=0;

void Gpio_Init()
{
	GPIO_InitTypeDef gpio_init;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	gpio_init.GPIO_Mode  = GPIO_Mode_Out_PP;
  gpio_init.GPIO_Pin   = GPIO_Pin_1;
  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&gpio_init);
}

void Timer_Init()
{
	TIM_TimeBaseInitTypeDef timer_init;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	timer_init.TIM_CounterMode = TIM_CounterMode_Up;
	timer_init.TIM_Period = 36000;
	timer_init.TIM_ClockDivision = 0;
	timer_init.TIM_RepetitionCounter = 0;
	timer_init.TIM_Prescaler = 2;	
	TIM_TimeBaseInit(TIM2,&timer_init);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	NVIC_EnableIRQ(TIM2_IRQn);
	TIM_Cmd(TIM2,ENABLE);
}

void TIM2_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM2, TIM_IT_Update)!=RESET)
	{
		flag = !flag;
  }
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}

void Delay_1ms(void)
{
	Timer_Init();
	TIM_Cmd(TIM2,ENABLE); 
	TIM_SetCounter(TIM2,0); 
	while(TIM_GetCounter(TIM2)<36000); 
	TIM_Cmd(TIM2,DISABLE); 
}

void Delay_ms(unsigned int time)
{
  while(time--)
	{
			Delay_1ms();
  }
}

int main ()
{
	Gpio_Init();
	Timer_Init();
	while(1)
	{
		if(flag)
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		}
		else
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_1);
		}
	}
}
