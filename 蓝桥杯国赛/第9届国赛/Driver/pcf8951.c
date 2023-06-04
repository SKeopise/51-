#include "pcf8951.h"










void ADC_ReadAIN3Data(unsigned char *dat)
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
















