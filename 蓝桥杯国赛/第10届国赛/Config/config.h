#ifndef _CONFIG_H
#define _CONFIG_H





#include <STC15F2K60S2.H>
#include <intrins.h>
#include <stdio.h>
#include <string.h>


#include "init.h"
#include "key.h"
#include "led.h"
#include "pcf8951.h"
#include "eeprom.h"
#include "iic.h"
#include "onewire.h"
#include "uart.h"
#include "sonic.h"



extern unsigned int Key_SetTime;

extern unsigned int Temp_Data;

extern bit DAC_Mode;




#endif
