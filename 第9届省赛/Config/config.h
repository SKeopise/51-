#ifndef _CONFIG_H_
#define _CONFIG_H_




#include <STC15F2K60S2.H>


#include "key.h"
#include "iic.h"
#include "led.h"
#include "init.h"



extern unsigned int Led_Timer;
extern unsigned int Led_Timer_Buff;
extern unsigned char Led_Running_Code;
extern unsigned char ADC;
extern unsigned char Smg_Mode;
extern unsigned char Led_Running_Mode;
extern unsigned char Led_Running_Mode_Buff;
extern unsigned char Pwm_Mode;
extern unsigned char flag08s;

extern unsigned int Led_Timer_Buff_Mode[4];

extern bit flag08s_change;
extern bit Led_Running_Open;
extern bit Led_Open;
extern bit Led_Change;
extern bit Pwm_Mode_Show;



sbit BUZZ = P0^6;
sbit RELAY = P0^4;

sbit KEY_OUT_0 = P3^0;
sbit KEY_OUT_1 = P3^1;
sbit KEY_OUT_2 = P3^2;
sbit KEY_OUT_3 = P3^3;














#endif
