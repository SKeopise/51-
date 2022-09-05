#include "ds1302.h"  									


unsigned char code Write_DS1302_ADDR[7] = {0x80,0x82,0x84,0x86,0x88,0x8A,0x8C};
unsigned char code Read_DS1302_ADDR[7] = {0x81,0x83,0x85,0x87,0x89,0x8B,0x8D};

unsigned char pdata Timer[7] = {0x25,0x30,0x08,0x01,0x04,0x02,0x22};

//写字节
void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK = 0;
		SDA = temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

//向DS1302寄存器写入数据
void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

//从DS1302寄存器读出数据
unsigned char Read_Ds1302_Byte ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}


void DS1302_Config()
{
	char i;
	
	Write_Ds1302_Byte(0x8E,0x00);
	for(i=0;i<7;i++)
	{
		Write_Ds1302_Byte(Write_DS1302_ADDR[i],Timer[i]);
	}
	Write_Ds1302_Byte(0x8E,0x00);

}

void DS1302_Read()
{
	if(workmod == 1)
	{
		char i;
		for(i=0;i<7;i++)
		{
			Timer[i] = Read_Ds1302_Byte(Read_DS1302_ADDR[i]);
		}
	}

}





