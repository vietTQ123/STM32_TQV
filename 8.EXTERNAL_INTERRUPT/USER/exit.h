#ifndef __EXIT__
#define __EXIT__

#include "stm32f10x.h"                  
#include "stm32f10x_gpio.h"             
#include "stm32f10x_rcc.h"              
#include "stm32f10x_exti.h"  

void delay_ms(uint16_t time);
void led_Init(void);
void button_Init(void);
void exti_Init(void);
void nvic_Init(void);
void EXTI15_10_IRQHandler(void);

#endif
