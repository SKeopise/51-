#include "PCF8591.h"







unsigned char PCF8591_ADC()
{
	unsigned char AD_Buf = 0;
	
	I2CStart();
	I2CSendByte(0x90);
	I2CWaitAck();
	I2CSendByte(0x03);
	I2CWaitAck();	
	
	I2CStart();
	I2CSendByte(0x91);
	I2CWaitAck();

	AD_Buf = I2CReceiveByte();
	I2CSendAck(1);
	I2CStop();
	
	return AD_Buf;
}

void PCF8591DAC(unsigned char dat)
{
	I2CStart();
	I2CSendByte(0x90);
	I2CWaitAck();
	I2CSendByte(0x40);
	I2CWaitAck();
	I2CSendByte(dat);
	I2CWaitAck();
	I2CStop();	
}

















