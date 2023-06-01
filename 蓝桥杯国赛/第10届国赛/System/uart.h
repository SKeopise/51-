#ifndef _UART_H
#define _UART_H





#include <config.h>





void UartInit();

void UartSendByte(unsigned char dat);

void UartSendString(unsigned char *str);

void StringCmp(unsigned char *str1,unsigned char *str2);

void UartReadTimerMonitor(unsigned char ms);

void StringClear(unsigned char *str,unsigned char len);

void UartDriver();






#endif
