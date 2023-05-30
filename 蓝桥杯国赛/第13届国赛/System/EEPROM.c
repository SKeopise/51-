#include "EEPROM.h"


#define FIRST_ADDR 0X89
#define FIRST_DATA 0x8E



void FirstReadEEPROM()
{
	unsigned char First_Data_Buf = 0;
	
	DataReadEEPROM(FIRST_ADDR,&First_Data_Buf);
	if(First_Data_Buf != FIRST_DATA)
	{
		DataWriteEEPROM(FIRST_ADDR,FIRST_DATA);
		DataWriteEEPROM(0x00,Relay_Cnt);
	}
	DataReadEEPROM(0x00,&Relay_Cnt);
}


void Delay5ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 59;
	j = 90;
	do
	{
		while (--j);
	} while (--i);
}


void DataReadEEPROM(unsigned char addr,unsigned char *dat)
{
	I2CStart();
	I2CSendByte(0xA0);
	I2CWaitAck();
	I2CSendByte(addr);
	I2CWaitAck();

	I2CStart();
	I2CSendByte(0xA1);
	I2CWaitAck();
		
	*dat = I2CReceiveByte();
	I2CSendAck(1);
	I2CStop();
}

void DataWriteEEPROM(unsigned char addr,unsigned char dat)
{
	I2CStart();
	I2CSendByte(0xA0);
	I2CWaitAck();
	I2CSendByte(addr);
	I2CWaitAck();
	I2CSendByte(dat);
	I2CWaitAck();
	I2CStop();	

	Delay5ms();
}
















