#include "uart.h"

char 	data; 			
int		flag; 			 
int 	count=0; 		
extern char	  string[100];

void Delay_ms(uint16_t time)
{
 uint16_t i,j;
 for(i = 0; i < time; i++)
 {
  for(j = 0; j < 0x2AFF; j++);
 }
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

void Uart_Gpio_Init()
{
	GPIO_InitTypeDef gpio_led;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	gpio_led.GPIO_Pin  = GPIO_Pin_1;
	gpio_led.GPIO_Mode  = GPIO_Mode_Out_PP;
	gpio_led.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_led);
}

void Uart_SendChar(char _chr)
{
  USART_SendData(USART1, _chr);
  while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

void Uart_SendStr(char *str)
{
 while(*str)
 {
	USART_SendData(USART1,*str);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	str++;
 }
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

void Uart_SendFloat(float number)
{
	uint8_t count1=0;
	uint8_t count2=0;
	char arr1[10]="";
	char arr2[10]="";
	int x,z;
	float y;
	
	if(number==0.0)
	{
		USART_SendData(USART1,'0');
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	}
	
	if(number>0)
	{
		x= (int)number;
		y= (float)number - x;
		z=  y*1000;
		
		while (x != 0) 
    {
      arr1[count1] = x%10;
      count1++;
      x = x/10;
    }
		
		while (count1!=0)
		{
			USART_SendData(USART1,arr1[count1-1]+0x30);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
			count1--;
		}
		
		USART_SendData(USART1,'.');
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
		
		while (z != 0) 
    {
      arr2[count2] = z%10;
      count2++;
      z = z/10;
    }
		
		while(count2 !=0)
		{
			USART_SendData(USART1,arr2[count2-1]+0x30);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
			count2--;
		}
	}
	
	if(number<0)
	{
		number=number*(-1);
		x= (int)number;
		y= (float)number - x;
		z= y*1000;
		
		while (x != 0) 
    {
      arr1[count1] = x%10;
      count1++;
      x = x/10;
    }
		
		USART_SendData(USART1,'-');
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
		
		while (count1!=0)
		{
			USART_SendData(USART1,arr1[count1-1]+0x30);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
			count1--;
		}
		
		USART_SendData(USART1,'.');
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
		
		while (z != 0) 
    {
      arr2[count2] = z%10;
      count2++;
      z = z/10;
    }
		
		while(count2 !=0)
		{
			USART_SendData(USART1,arr2[count2-1]+0x30);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
			count2--;
		}
	}
}

uint16_t Uart_ReadChar()
{
	return USART_ReceiveData(USART1);
}

uint8_t Uart_Compare(char *str1, char * str2)
{
	while(*str1 && *str2)
	{
		if(*str1 != *str2)
		{
			return 0;
		}
		str1++;
		str2++;
	}
	if (*str1 == '\0' && *str2 == '\0') 
	{
   return 1; 
  } 
	else 
	{
   return 0; 
  }
}

void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE)!=RESET)
	{
		data = Uart_ReadChar();
		if(data == '\n')
		{
			flag = 1; 
			string[count-1] = NULL;
			count = 0;
		}
		else
		{
		 string[count] = data;
		 count++;
		}
	}
}

uint8_t Uart_Debug_Flag()
{
	if(flag==1)
	{
		flag=0;
		return 1;
	}
	return 0;
}
