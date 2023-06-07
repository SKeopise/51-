#include "eeprom.h"


#define FIRST_ADDR 0xB7
#define FIRST_DATA 0xC2



void EEPROM_FirstRead()
{
	unsigned char Data_Buf = 0;
	
	EEPROM_ReadData(FIRST_ADDR,&Data_Buf);
	if(Data_Buf != FIRST_DATA)
	{
		EEPROM_WriteData(FIRST_ADDR,FIRST_DATA);
		EEPROM_WriteData(ADC_DATA_ADDR,ADC_Data_EEPROM);
		EEPROM_WriteDataUint(TEMP_DATA_ADDR_HIGH,TEMP_DATA_ADDR_LOW,Temp_Data_EEPROM);
		EEPROM_WriteDataUint(FREQ_DATA_ADDR_HIGH,FREQ_DATA_ADDR_LOW,Freq_Data_EEPROM);
	}
	else
	{
		EEPROM_ReadData(ADC_DATA_ADDR,&ADC_Data_EEPROM);
		EEPROM_ReadDataUint(TEMP_DATA_ADDR_HIGH,TEMP_DATA_ADDR_LOW,&Temp_Data_EEPROM);
		EEPROM_ReadDataUint(FREQ_DATA_ADDR_HIGH,FREQ_DATA_ADDR_LOW,&Freq_Data_EEPROM);
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

void EEPROM_WriteDataUint(unsigned char addrH,unsigned char addrL,unsigned int dat)
{
	unsigned char Data_Buf = 0;
	
	Data_Buf = (unsigned char)(dat >> 8);
	EEPROM_WriteData(addrH,Data_Buf);
	Data_Buf = (unsigned char)(dat & 0x00FF);
	EEPROM_WriteData(addrL,Data_Buf);	
}

void EEPROM_ReadDataUint(unsigned char addrH,unsigned char addrL,unsigned int *dat)
{
	unsigned char Data_Buf = 0;
	
	EEPROM_ReadData(addrH,&Data_Buf);
	*dat = Data_Buf;
	EEPROM_ReadData(addrL,&Data_Buf);
	*dat = (*dat << 8) | Data_Buf;
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

















