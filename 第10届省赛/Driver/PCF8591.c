#include "PCF8591.h"







unsigned char PCF8591_ADC()
{
	unsigned char AD_Buf = 0;
	
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();
	IIC_SendByte(0x03);
	IIC_WaitAck();	
	
	IIC_Start();
	IIC_SendByte(0x91);
	IIC_WaitAck();

	AD_Buf = IIC_RecByte();
	IIC_SendAck(1);
	IIC_Stop();
	
	return AD_Buf;
}

void PCF8591DAC(unsigned char dat)
{
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();
	IIC_SendByte(0x40);
	IIC_WaitAck();
	IIC_SendByte(dat);
	IIC_WaitAck();
	IIC_Stop();	
}

















