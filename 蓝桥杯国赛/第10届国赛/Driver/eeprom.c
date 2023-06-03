#include "eeprom.h"

#define FIRST_ADDR 0x77
#define FIRST_DATA 0x66



void FirstRead_EEPROM()
{
	unsigned char Data_Buf = 0;
	
	EEPROM_ReadData(FIRST_ADDR,&Data_Buf);
	if(Data_Buf != FIRST_DATA)
	{
		EEPROM_WriteData(FIRST_ADDR,FIRST_DATA);
		EEPROM_WriteUnsignedInt(PARM_CNT_ADDR_HIGH,PARM_CNT_ADDR_LOW,&Parm_ChangCnt);	
	}
	else
	{
		EEPROM_ReadUnsignedInt(PARM_CNT_ADDR_HIGH,PARM_CNT_ADDR_LOW,&Parm_ChangCnt);
	}
}

void EEPROM_WriteUnsignedInt(unsigned char addrH,unsigned char addrL,unsigned int *dat)
{
	unsigned char Data_Buf = 0;
	
	Data_Buf = (unsigned char)(*dat & 0x0F); 
	EEPROM_WriteData(addrL,Data_Buf);
	Data_Buf = (unsigned char)(*dat >> 8);
	EEPROM_WriteData(addrH,Data_Buf);			
}

void EEPROM_ReadUnsignedInt(unsigned char addrH,unsigned char addrL,unsigned int *dat)
{
	unsigned char Data_Buf = 0;
	EEPROM_ReadData(addrH,&Data_Buf);
	*dat = Data_Buf;
	*dat <<= 8;
	EEPROM_ReadData(addrL,&Data_Buf);	
	*dat |= Data_Buf;	
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



void EEPROM_ReadData(unsigned char addr,unsigned char *dat)
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


void EEPROM_WriteData(unsigned char addr,unsigned char dat)
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













