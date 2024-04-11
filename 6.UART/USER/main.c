#include "uart.h"
		
//int		Flag; 			 		
char	string[100];

int main()
{
 Uart_Init();
 Uart_Gpio_TxRx_Init();
 Uart_Gpio_Init();
 while(1)
 {
//		uart_SendChar('A');
//		USART_SendData(USART1,'\n');
//		delay_ms(1000);
		
//		uart_SendStr("HI");
//		USART_SendData(USART1,'\n');
//		delay_ms(100);
		
//		uart_SendInt(99);
//		USART_SendData(USART1,'\n');
//		delay_ms(100);
		
//		uart_SendFloat(-10.585);
//		USART_SendData(USART1,'\n');
//		delay_ms(100);
		
//		if(USART_ReceiveData(USART1) == 'B')
//		{
//			GPIO_ResetBits(GPIOC,GPIO_Pin_1);
//		}
//		else if(USART_ReceiveData(USART1) == 'T')
//		{
//			GPIO_SetBits(GPIOC,GPIO_Pin_1);
//		}

//		if(Flag==1)
//		{
//			Flag=0;
//			if(strcmp(String,"ON")==0)
//			{
//				GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//			}
//			else if (strcmp(String,"OFF")==0)
//			{
//				GPIO_SetBits(GPIOA,GPIO_Pin_1);
//			}
//		}

		if(Uart_Debug_Flag()==1)
		{
			if(Uart_Compare(string,"ON")==1)
			{
				GPIO_ResetBits(GPIOA,GPIO_Pin_1);
			}
			else if (Uart_Compare(string,"OFF")==1)
			{
				GPIO_SetBits(GPIOA,GPIO_Pin_1);
			}
		}
 }
}
