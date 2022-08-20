#include "reg52.h"
#ifndef __EXTI_H
#define __EXTI_H
sbit led=P2^0;
sbit k3=P3^2;
void ConfigExti0();
void InterruptExti0();
#endif
