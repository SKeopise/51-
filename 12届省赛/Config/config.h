#ifndef _CONFIG_
#define _CONFIG_




#include <STC15F2K60S2.H>

#include "Led.h"

#include "key.h"
#include "init.h"
#include "onewire.h"
#include "iic.h"


extern unsigned int temp;
extern unsigned char Show_Mode;
extern unsigned char parm;
extern unsigned char parmbuf;
extern bit DAC_Mode;
extern float DAC;
extern unsigned int DAC_Number;


sbit LED0 = P0^0;
sbit LED1 = P0^1;
sbit LED2 = P0^2;
sbit LED3 = P0^3;

sbit KEY_OUT_0 = P3^0;
sbit KEY_OUT_1 = P3^1;
sbit KEY_OUT_2 = P3^2;
sbit KEY_OUT_3 = P3^3;

sbit KEY_IN_0 = P4^4;
sbit KEY_IN_1 = P4^2;
sbit KEY_IN_2 = P3^5;
sbit KEY_IN_3 = P3^4;



















#endif