#include "pcf8951.h"










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











