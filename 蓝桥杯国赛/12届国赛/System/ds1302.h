#ifndef _DS1302_H
#define _DS1302_H



#include <config.h>






void Write_Ds1302_Byte( unsigned char address,unsigned char dat );

unsigned char Read_Ds1302_Byte ( unsigned char address );

void Ds1302Init();

void Ds1302TimerRead();






#endif
