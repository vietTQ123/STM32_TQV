#include "sensor.h"

void Sensor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitTypeDefStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDefStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitTypeDefStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitTypeDefStructure.GPIO_Pin = SENSOR_PIN1 | SENSOR_PIN2 | SENSOR_PIN3 | SENSOR_PIN4 | SENSOR_PIN5;
	GPIO_Init(SENSOR_PORT, &GPIO_InitTypeDefStructure);
}

uint8_t Sensor_Read(uint8_t pin){
	if(GPIO_ReadInputDataBit(SENSOR_PORT, pin) == Bit_SET)
		return SENSOR_ON;
	else
		return SENSOR_OFF;
}


uint8_t  Sensor_Bit()
{
	uint8_t bit=0x00;
	if(Sensor_Read(SENSOR_PIN1)==SENSOR_ON)
	{
		bit |= 0x01;
	}
	if(Sensor_Read(SENSOR_PIN2)==SENSOR_ON)
	{
		bit |= 0x02;
	}
	if(Sensor_Read(SENSOR_PIN3)==SENSOR_ON)
	{
		bit |= 0x04;
	}
	if(Sensor_Read(SENSOR_PIN4)==SENSOR_ON)
	{
		bit |= 0x08;
	}
	if(Sensor_Read(SENSOR_PIN5)==SENSOR_ON)
	{
		bit |= 0x10;
	}
	return bit;
}
