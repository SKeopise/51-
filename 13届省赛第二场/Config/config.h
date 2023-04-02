#ifndef _CONFIG_H
#define _CONFIG_H




#include <STC15F2K60S2.H>
#include <intrins.h>


#include "init.h"
#include "key.h"
#include "led.h"
#include "iic.h"
#include "Sonic.h"







extern unsigned int ADC_Data;
extern unsigned int Sonic_Dist;
extern unsigned char Show_Mode;

extern unsigned int Parm_ADC_MAX;
extern unsigned int Parm_ADC_MAX_Buf;
extern unsigned int Parm_ADC_MIN;
extern unsigned int Parm_ADC_MIN_Buf;



extern bit flag_Sonic_Reda_Start;
extern bit Sonic_Dist_Far;
extern bit Parm_Mode;
extern bit flag_01s;











#endif
