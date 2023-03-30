#ifndef _CONFIG_H
#define _CONFIG_H




#include <STC15F2K60S2.H>



#include "init.h"
#include "onewire.h"
#include "led.h"
#include "key.h"









extern unsigned char TimeLast;

extern unsigned char pdata Mode;

extern unsigned char xdata Mode_Buf;

extern unsigned char Temp;


extern bit Stop;




sbit BUZZ = P0^6;
sbit RELAY = P0^4;

sbit PWM_OUT = P3^4;

sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;






#endif
