#include "reg52.h"
#include "uart.h"
#include "string.h"

unsigned char flag_recv=0;

void ConfigUART(unsigned int baud)
{
	PCON|=0x80;
	SCON=0x50;
	TMOD|=0x20;
	TH1=256-(11059200/12/16)/baud;
	TL1=TH1;
	ET1=0;
	ES=1;
	EA=1;
	TR1=1;
}
void InterruptUART() interrupt 4
{
	if(RI)
	{
		RI=0;
		flag_recv=1;
	}
}
void print(unsigned char* str)
{
	unsigned int cnt=0;
	while(*str)
	{
		SBUF=*str++;
		while(!TI);
		TI=0;
	}
}
