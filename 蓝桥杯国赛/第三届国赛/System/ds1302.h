#ifndef __DS1302_H
#define __DS1302_H


#include <intrins.h>
#include <config.h>

   



void Write_Ds1302(unsigned char temp);
void Write_Ds1302_Byte( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302_Byte( unsigned char address );

void Ds1302Init();

void Ds1302Read();






#endif
