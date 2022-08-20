#include "reg52.h"
#include "tim.h"
void PreProcessTMOD()
{
	TMOD=0x00;
}
void StartT0()
{
	TR0=1;
}
void StopT0()
{
	TR0=0;
}
void ConfigT0()
{
	EA=1;
	TMOD|=0x01;
	TH0=0xdc;
	TL0=0x00;
	ET0=1;
}
void LoadT0()
{
	TH0=0xdc;
	TL0=0x00;
}
void InterruptT0() interrupt 1
{
	static unsigned int cnt=0;
	LoadT0();
	cnt++;
	if(cnt==100)
	{
		cnt=0;
		led=!led;
	}
}
