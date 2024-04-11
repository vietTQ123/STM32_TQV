#include "sensor.h"

void delay_ms(uint16_t time)
{
 uint16_t i,j;
 for(i = 0; i < time; i++)
 {
  for(j = 0; j < 0x2AFF; j++);
 }
}


int main()
{
	Sensor_Init();
	while(1)
	{
		
	}
}
