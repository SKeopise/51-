#ifndef _IIC_H
#define _IIC_H



#include <config.h>



void I2CStart(void);

void I2CStop(void);

void I2CSendByte(unsigned char byt);

unsigned char I2CReceiveByte(void);

unsigned char I2CWaitAck(void);

void I2CSendAck(unsigned char ackbit);









#endif
