#ifndef _CONFIG_H
#define _CONFIG_H




#include <STC15F2K60S2.H>

#include "onewire.h"
#include "ds1302.h"
#include "init.h"
#include "led.h"
#include "key.h"







extern unsigned char TimerData[3];
extern unsigned char Timer_Warring[3];
extern unsigned int Temp_Data;
extern unsigned char Clock_Data_Set;
extern unsigned char Clock_Warring_Time_Set;

extern bit Flag_Warring_Clock;
extern bit flag_1s;
extern bit Temp_Show;
extern bit flag_200ms;
extern unsigned char flag_5s;

sbit BUZZ = P0^6;
sbit RELAY = P0^4;

sbit LED1 = P0^0;








#endif
