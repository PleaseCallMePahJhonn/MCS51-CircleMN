#include "reg52.h"
#ifndef __TIM_H
#define __TIM_H
sbit led=P2^0;
void PreProcessTMOD();
void StartT0();
void StopT0();
void ConfigT0();
void LoadT0();
void InterruptT0();
#endif
