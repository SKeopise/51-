
#include <config.h>
#include <EEPROM.h>
#include <stc_i2c.h>



void E2Read(unsigned char *buf,unsigned char addr,unsigned char len)
{
	do
	{
		I2CStart();
		if(I2CWrite(0x50<<1))
		{
			break;
		}
		I2CStop();
	}while(1);
	I2CWrite(addr);
	I2CStart();
	I2CWrite((0x50<<1)|0x01);
	while(len>1)
	{
		*buf++ = I2CReadACK();
		len--;
	}
	*buf = I2CReadNAK();
	I2CStop();
	
}


void E2Write(unsigned char *buf,unsigned char addr,unsigned char len)
{
	while(len > 0)
	{
		do{
				I2CStart();
				if(I2CWrite(0x50<<1))
				{
					break;
				}
				I2CStop();
			}while(1);
			I2CWrite(addr);
			while(len>0)
			{
				I2CWrite(*buf++);
				len--;
				addr++;
				if((addr&0x07) == 0)
				{
					break;
				}
			}
			I2CStop();	
	}
}


































