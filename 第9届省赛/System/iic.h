#ifndef _IIC_H
#define _IIC_H

#include <config.h>

#include <intrins.h>

sbit SDA = P2^1;
sbit SCL = P2^0;




unsigned char AD_RB2_AIN3();

unsigned char EEPROM_Read(unsigned char addr);

void EEPROM_Write(unsigned char addr,unsigned char dat);


void IIC_Start(void); 
void IIC_Stop(void);  
bit IIC_WaitAck(void);  
void IIC_SendAck(bit ackbit); 
void IIC_SendByte(unsigned char byt); 
unsigned char IIC_RecByte(void); 

#endif