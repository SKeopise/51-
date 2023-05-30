#ifndef _CONFIG_H
#define _CONFIG_H




#include <STC15F2K60S2.H>
#include <intrins.h>

#include "init.h"
#include "led.h"
#include "key.h"
#include "iic.h"
#include "EEPROM.h"
#include "sonic.h"
#include "PCF8591.h"
#include "NE555.h"



extern unsigned char RH_Data;

extern bit flag_Led_Flash;

extern unsigned char Relay_Cnt;
extern bit flag_Clear_RelayCnt;


sbit RELAY = P0^4;
sbit BUZZ = P0^6;

sbit Motor = P0^5;




#endif
