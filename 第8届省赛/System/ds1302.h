#ifndef _DS1302_H
#define _DS1302_H




#include <config.h>

#include <intrins.h>


extern unsigned char code DS1302_Write_Addr[7];


void Write_Ds1302(unsigned  char temp);

void Write_Ds1302_Byte( unsigned char address,unsigned char dat );

unsigned char Read_Ds1302_Byte ( unsigned char address );


void Ds1302TimerRead();

void Ds1302Init();

void DS1302Start();

void DS1302Stop();











#endif
