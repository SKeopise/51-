#include "PCF8591.h"






void ADC_Data_Read_AIN3(unsigned char *dat)
{
	I2CStart();
	I2CSendByte(0x90);
	I2CWaitAck();
	I2CSendByte(0x03);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(0x91);
	I2CWaitAck();	
	
	*dat = I2CReceiveByte();
	I2CSendAck(1);
	I2CStop();
}

void DAC_Output(unsigned char dat)
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












