/*
  ³ÌÐòËµÃ÷: DS1302Çý¶¯³ÌÐò
  Èí¼þ»·¾³: Keil uVision 4.10 
  Ó²¼þ»·¾³: CT107µ¥Æ¬»ú×ÛºÏÊµÑµÆ½Ì¨ 8051£¬12MHz
  ÈÕ    ÆÚ: 2011-8-9
*/

#include "ds1302.h"

sbit SCK = P1^7;		
sbit SDA = P2^3;		
sbit RST = P1^3;

unsigned char code Ds1302_Write_Byte[7] = {
	0x80,0x82,0x84,0x86,0x88,0x8A,0x8C
};
unsigned char code Ds1302_Read_Byte[7] = {
	0x81,0x83,0x85,0x87,0x89,0x8B,0x8D
};

unsigned char TimerData[7] = {            //DS1302çš„æ—¶é—´å­˜å‚¨
	0x00,0x59,0x06,0x05,0x03,0x07,0x23
};

void Ds1302Init()
{
	unsigned char i = 0;
	Write_Ds1302_Byte(0x8E,0x00);
	
	for(i=0;i<7;i++)
	{
		Write_Ds1302_Byte(Ds1302_Write_Byte[i],TimerData[i]);
	}
	
	Write_Ds1302_Byte(0x8E,0x80);		
}

void Ds1302Read()
{
	unsigned char i = 0;
	
	for(i=0;i<7;i++)
	{
		TimerData[i] = Read_Ds1302_Byte(Ds1302_Read_Byte[i]);
	}
}





void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		SDA=temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

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
