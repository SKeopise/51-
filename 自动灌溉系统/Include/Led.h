#ifndef _LED_H_
#define _LED_H_



#include <init.h>
#include <ds1302.h>
#include <Led.h>


extern unsigned char WorkMod;

void Led_Driver(unsigned char pos,unsigned char dat);

void Led_shidu();

void Led_yuzhi();

void Led_Mod();
















#endif