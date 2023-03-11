#ifndef _IIC_H
#define _IIC_H

#include <config.h>

#include <intrins.h>





void PCF8951Init();

unsigned char ReadAIN1();





void IIC_Start(void); 
void IIC_Stop(void);  
bit IIC_WaitAck(void);  
void IIC_SendAck(bit ackbit); 
void IIC_SendByte(unsigned char byt); 
unsigned char IIC_RecByte(void); 

#endif