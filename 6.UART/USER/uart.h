#ifndef __UART__
#define __UART__

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "string.h"
#include "stdio.h"

void Delay_ms(uint16_t time);
void Uart_Init(void);
void Uart_Gpio_TxRx_Init(void);
void Uart_Gpio_Init(void);
void Uart_SendChar(char _chr);
void Uart_SendStr(char *str);
void Uart_SendInt(int number);
void Uart_SendFloat(float number);
uint16_t Uart_ReadChar(void);
uint8_t Uart_Compare(char *str1, char * str2);
void USART1_IRQHandler(void);
uint8_t Uart_Debug_Flag(void);

#endif
