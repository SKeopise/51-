#include "eeprom.h"


#define FIRST_ADDR 0xAE
#define FIRST_DATA 0x8C





void FirstReadData()
{
	unsigned char Data_Buf = 0;
	
	EEPROM_ReadByte(FIRST_ADDR,&Data_Buf);
	if(Data_Buf != FIRST_DATA)
	{
		EEPROM_WriteByte(FIRST_ADDR,FIRST_DATA);

		ClearEEPROM();
		ReadHistoryData();
	}
	else
	{
		ReadHistoryData();
		EEPROM_ReadByte(DISTENCE_CNT_ADDR,&Distence_Cnt);
		EEPROM_ReadByte(PARM_ADDR,&Parm_Distence);
		
		EEPROM_ReadInt((SONIC_DATA_ADDR+(Distence_Cnt-1)*0x02),(SONIC_DATA_ADDR+(Distence_Cnt-1)*0x02+0x01),&Sonic_Distence);
		
		if(Distence_Cnt > 1)
		{
			Distence_LastIncNow = Sonic_Distence + Sonic_HistoryData[Distence_Cnt - 2];
		}
		else
		{
			Distence_LastIncNow = Sonic_Distence + Sonic_HistoryData[8 + Distence_Cnt];
		}		
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


void ClearEEPROM()
{
	unsigned char i = 0;
	unsigned char Addr_Buf = SONIC_DATA_ADDR;
	
	for(i=0;i<10;i++)
	{
		EEPROM_WriteInt(Addr_Buf,Addr_Buf+0x01,&Sonic_HistoryData[i]);
		Addr_Buf += 0x02;
	}
}


void ReadHistoryData()
{
	unsigned char i = 0;
	unsigned char Addr_Buf = SONIC_DATA_ADDR;
	
	for(i=0;i<10;i++)
	{
		EEPROM_ReadInt(Addr_Buf,Addr_Buf+0x01,&Sonic_HistoryData[i]);
		Addr_Buf += 0x02;
	}	
}


void EEPROM_WriteInt(unsigned char addrH,unsigned char addrL,unsigned int *dat)
{
	unsigned char Data_Buf;
	
	Data_Buf = (unsigned char)(*dat >> 8);
	EEPROM_WriteByte(addrH,Data_Buf);
	Data_Buf = (unsigned char)(*dat & 0x00FF);
	EEPROM_WriteByte(addrL,Data_Buf);	
}

void EEPROM_ReadInt(unsigned char addrH,unsigned char addrL,unsigned int *dat)
{
	unsigned char Data_Buf_High;
	unsigned char Data_Buf_Low;
	
	EEPROM_ReadByte(addrH,&Data_Buf_High);
	EEPROM_ReadByte(addrL,&Data_Buf_Low);
	*dat = Data_Buf_High;
	*dat = (*dat << 8) | Data_Buf_Low;
}


void EEPROM_WriteByte(unsigned char addr,unsigned char dat)
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


void EEPROM_ReadByte(unsigned char addr,unsigned char *dat)
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
















