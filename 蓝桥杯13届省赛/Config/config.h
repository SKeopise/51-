/* config.h   */
#ifndef CONFIG_H
#define CONFIG_H

// 防止头文件中的内容被重复定义


#include <STC15F2K60S2.H>

#include <init.h>
#include "led.h"
#include "key.h"
#include "ds1302.h"
#include "onewire.h"
#include "ds1302.h"

extern unsigned char Ds1302_Time[];
extern unsigned int temp;
extern bit workmode;
extern unsigned char Tparm;
extern bit TimeMod;
extern bit Relayflag; 
extern bit flag100ms;
extern bit LED3flag;


sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;

sbit KEY_OUT_0 = P3^0;
sbit KEY_OUT_1 = P3^1;
sbit KEY_OUT_2 = P3^2;
sbit KEY_OUT_3 = P3^3;
sbit KEY_IN_0 = P4^4;
sbit KEY_IN_1 = P4^2;
sbit KEY_IN_2 = P3^5;
sbit KEY_IN_3 = P3^4;


















#endif // CONFIG_H