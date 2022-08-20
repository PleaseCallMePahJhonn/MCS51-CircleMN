#include "reg52.h"
#include "exti.h"
void delay(unsigned int i)
{
	while(i--);
}
void ConfigExti0()
{
	IT0=1;
	EX0=1;
	EA=1;
}
void InterruptExti0() interrupt 0
{
	delay(1000);
	if(k3==0)
	{
		led=!led;
	}
}
