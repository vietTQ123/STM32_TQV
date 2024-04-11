#include "exit.h" 

uint8_t flag_exti15 = 0;
uint8_t flag_exti14 = 0;
uint16_t time = 0;
uint16_t flag_out = 0;

int main()
{
	led_Init();
	button_Init();
	nvic_Init();
	exti_Init();
	while(1)
	{
		if(flag_exti14)
		{
			time++;
			if(time <= 200)
			{
				GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		  }
			else
			{
				GPIO_SetBits(GPIOA,GPIO_Pin_1);
				if(time >= 400)
				{
					time = 0;
					flag_out++;
					if(flag_out >= 5)
					{
						flag_exti14 = 0;
						flag_out = 0;
					}
				}
			}
		}
		if(flag_exti15)
		{
			time++;
			if(time <= 100)
			{
				GPIO_ResetBits(GPIOA,GPIO_Pin_1);
			}
			else
			{
				GPIO_SetBits(GPIOA,GPIO_Pin_1);
				if(time >= 200)
				{
					time = 0;
					flag_out++;
					if(flag_out >= 25)
					{
						flag_exti15 = 0;
						flag_out = 0;
					}
				}
			}
		}
	}
}
