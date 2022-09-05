
#include <EEPROM.h>




void Write_EEPROM(unsigned char addr,unsigned char dat)
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


unsigned char Read_EEPROM(unsigned char addr)
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





















