#include <PCF8951.h>






void AD_init()
{
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();
	IIC_SendByte(0x43);
	IIC_WaitAck();
	IIC_Stop();
}

unsigned char AD_Get()
{                                               
	unsigned char temp;                 
	
	IIC_Start();
	IIC_SendByte(0x91);
	IIC_WaitAck();	
	temp = IIC_RecByte();
	
	return temp;
}

























