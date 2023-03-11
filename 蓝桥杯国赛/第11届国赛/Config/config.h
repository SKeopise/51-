#ifndef _CONFIG_H_
#define _CONFIG_H_


#include <STC15F2K60S2.H>

#include "init.h"
#include "key.h"
#include "led.h"
#include "iic.h"
#include "onewire.h"
#include "ds1302.h" 


extern bit Smg_Show_Mode;
extern unsigned char Smg_Data_Mode;
extern unsigned char Smg_Parm_Mode;

extern unsigned char TimerData[4];
extern unsigned int TempData;

extern unsigned int RD1_Vin;
extern bit Light_Dark;

extern unsigned char Timer_Parm;
extern unsigned int Temp_Parm;
extern unsigned char Led_Parm;
extern unsigned char Timer_Parm_Buff;
extern unsigned int Temp_Parm_Buff;
extern unsigned char Led_Parm_Buff;

extern bit Parm_Change;
extern unsigned char Parm_Buff;

extern bit flagLed1;
extern unsigned char flag3S;

sbit KEY_IN_0 = P4^4;
sbit KEY_IN_1 = P4^2;
sbit KEY_IN_2 = P3^5;
sbit KEY_IN_3 = P3^4;

sbit KEY_OUT_0 = P3^0;
sbit KEY_OUT_1 = P3^1;
sbit KEY_OUT_2 = P3^2;
sbit KEY_OUT_3 = P3^3;

sbit LED0 = P0^0;
sbit LED1 = P0^1;
sbit LED2 = P0^2;
sbit LED3 = P0^3;
sbit LED4 = P0^4;
sbit LED5 = P0^5;
sbit LED6 = P0^6;
sbit LED7 = P0^7;








#endif
