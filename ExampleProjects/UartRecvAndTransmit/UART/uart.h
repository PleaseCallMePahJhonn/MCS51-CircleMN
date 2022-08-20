#include "reg52.h"
#ifndef __UART_H
#define __UART_H
void ConfigUART(unsigned int baud);
void InterruptUART();
void print(unsigned char* str);
#endif
