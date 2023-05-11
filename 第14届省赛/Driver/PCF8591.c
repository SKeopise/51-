
#include "PCF8591.h"




unsigned char PCF8951AIN1ReadData()
{
	unsigned char DataBuf = 0;
	
	I2CStart();
	I2CSendByte(0x90);
	I2CWaitAck();
	I2CSendByte(0x01);
	I2CWaitAck();	
	
	I2CStart();
	I2CSendByte(0x91);
	I2CWaitAck();	
	
	DataBuf = I2CReceiveByte();
	I2CSendAck(1);
	I2CStop();
	
	return DataBuf; 
}

























