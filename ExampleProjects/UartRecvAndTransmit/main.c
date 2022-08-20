#include "reg52.h"
#include "uart.h"
void main()
{
	extern unsigned char flag_recv;
	ConfigUART(9600);
	while(1)
	{
		if(flag_recv)
		{
			flag_recv=0;
			print("Hello\r\n");
		}
	}
}
