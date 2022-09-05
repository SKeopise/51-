#ifndef _STC_UART_H_
#define _STC_UART_H_







void ConfigUART(unsigned int baud);
void UartWrite(unsigned char *buf,unsigned char len);
unsigned char UartRead(unsigned char *buf,unsigned char len);
void UartRxMonitor(unsigned char ms);
void UartDriver();

extern void UartAction(unsigned char *buf,unsigned char len);




#endif