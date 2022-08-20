#include "reg52.h"
#include "tim.h"
void main()
{
	PreProcessTMOD();
	ConfigT0();
	StartT0();
	while(1);
}
