#ifndef _CONFIG_H
#define _CONFIG_H

#include <STC15F2K60S2.H>



#include "iic.h"
#include "key.h"
#include "led.h"
#include "init.h"
#include "NE555.h"
#include "PCF8591.h"





extern unsigned int NE555_Timer_Cnt;
extern unsigned int NE555_Freq;
extern unsigned int AD_Show_Number;

extern bit Show_Mode;
extern bit DAC_Mode;
extern bit flag_500ms;
extern bit Smg_Open;
extern bit Led_Open;


sbit BUZZ = P0^6;
sbit RELAY = P0^4;

sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit LED4 = P0^3;
sbit LED5 = P0^4;
sbit LED6 = P0^5;
sbit LED7 = P0^6;









#endif
