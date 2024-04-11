#ifndef __SENSOR_H
#define __SENSOR_H

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define SENSOR_PORT		GPIOA
#define SENSOR_PIN1		GPIO_Pin_7
#define SENSOR_PIN2		GPIO_Pin_6
#define SENSOR_PIN3		GPIO_Pin_5
#define SENSOR_PIN4		GPIO_Pin_4
#define SENSOR_PIN5		GPIO_Pin_8


typedef enum {
	SENSOR_OFF = 0,
	SENSOR_ON = 1
}Sensor_Val;

void Sensor_Init(void);
uint8_t Sensor_Read(uint8_t pin);
uint8_t  Sensor_Bit(void);

#endif
