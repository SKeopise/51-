
#include <EEPROM.h>

#define PasswordAddr 0x14
#define FirstAddr 0x78

unsigned char FirstBuf = 0;

void Delay5ms()//延迟5MS，方便EEPROM连续写
{
	unsigned char i, j;

	i = 59;
	j = 90;
	do
	{
		while (--j);
	} while (--i);
}

void AT24C02FirstRead()
{
	FirstBuf = ReadEEPROM(FirstAddr);
	if(FirstBuf != 98)
	{
		PasswordReset();
		WriteEEPROM(FirstAddr,98);
	}
	AT24C02PasswordRead();
}

void AT24C02PasswordRead()
{
	unsigned char i = 0;
	
	for(i=0;i<6;i++)
	{
		PassWord[i] = ReadEEPROM(PasswordAddr+i);
	}
}

void AT24C02PasswordWrite()
{
	unsigned char i = 0;
	
	for(i=0;i<6;i++)
	{
		WriteEEPROM(PasswordAddr+i,PassWord[i]);
		Delay5ms();
	}
}



unsigned char ReadEEPROM(unsigned char addr)
{
	unsigned char temp;
	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck(); 	
	
	IIC_Start();
	IIC_SendByte(0xA1);
	IIC_WaitAck();	
	temp = IIC_RecByte();
	IIC_Stop();	
	
	return temp;
}


void WriteEEPROM(unsigned char addr,unsigned char dat)
{
	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();
	IIC_SendByte(dat);
	IIC_WaitAck();	
	IIC_Stop();
}











