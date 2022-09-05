#ifndef __DS1302_H
#define __DS1302_H

#include <STC15F2K60S2.H>
#include <intrins.h>


void Write_Ds1302_Byte(unsigned  char temp);
void Write_Ds1302( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302 ( unsigned char address );
unsigned char shijian[7];


unsigned char Write_DS1302_ADDR[7] = {0x80,0x82,0x84,0x86,0x88,0x8a,0x8c};
unsigned char Read_DS1302_ADDR[7] = {0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};

unsigned char Timer[7] = {0x00,0x30,0x08,0x06,0x04,0x03,0x22};

sbit SCK=P1^7;		
sbit SDA=P2^3;		
sbit RST = P1^3;   // DS1302¸´Î»												

void Write_Ds1302_Byte(unsigned  char temp) 
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

void Write_Ds1302( unsigned char address,unsigned char dat )     
{
 	RST=0;
	_nop_();
 	SCK=0;
	_nop_();
 	RST=1;	
   	_nop_();  
 	Write_Ds1302_Byte(address);	
 	Write_Ds1302_Byte(dat);		
 	RST=0; 
}

unsigned char Read_Ds1302 ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;
	_nop_();
 	SCK=0;
	_nop_();
 	RST=1;
	_nop_();
 	Write_Ds1302_Byte(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;
	_nop_();
 	RST=0;
	SCK=0;
	_nop_();
	SCK=1;
	_nop_();
	SDA=0;
	_nop_();
	SDA=1;
	_nop_();
	return (temp);			
}



void DS1302_Config()
{
	char i;
	Write_Ds1302(0x8E,0x00);
	for(i=0;i<7;i++)
	{
		Write_Ds1302(Write_DS1302_ADDR[i],Timer[i]);
	}
	Write_Ds1302(0x8E,0x80);
}

void DS1302_Read()
{
	char i;
	
	for(i=0;i<7;i++)
	{
		Timer[i] = Read_Ds1302(Read_DS1302_ADDR[i]);
	}
}










#endif