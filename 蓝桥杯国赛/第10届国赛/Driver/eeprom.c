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
		Data_Buf = (unsigned char)(Parm_ChangCnt & 0x0F); 
		EEPROM_WriteData(PARM_CNT_ADDR_LOW,Data_Buf);
		Data_Buf = (unsigned char)(Parm_ChangCnt >> 8);
		EEPROM_WriteData(PARM_CNT_ADDR_HIGH,Data_Buf);		
	}
	else
	{
		EEPROM_ReadData(PARM_CNT_ADDR_HIGH,&Data_Buf);
		Parm_ChangCnt = Data_Buf;
		Parm_ChangCnt <<= 8;
		EEPROM_ReadData(PARM_CNT_ADDR_LOW,&Data_Buf);
		Parm_ChangCnt |= Data_Buf;
	}
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













