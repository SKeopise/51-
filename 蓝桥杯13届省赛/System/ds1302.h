#ifndef _DS1302_H
#define	_DS1302_H



#include <config.h>

#include <intrins.h>


sbit RST = P1^3;
sbit SCK = P1^7;
sbit SDA = P2^3;

void Write_Ds1302(unsigned  char temp);

void Write_Ds1302_Byte( unsigned char address,unsigned char dat );

unsigned char Read_Ds1302_Byte ( unsigned char address );



void Ds1302_Config();
void Ds1302_Read();

















#endif
