#ifndef _LED_H
#define _LED_H



#include <config.h>








void SmgDisplay();

void SmgShowTimer();

void SmgShowMode();

void SmgShowLenData();

void SmgShowSaveDataMode();

void SmgShowParmSet();

void SmgShowInit();

void LedDisplay();


sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit LED4 = P0^3;
sbit LED5 = P0^4;
sbit LED6 = P0^5;
sbit LED7 = P0^6;
sbit LED8 = P0^7;











#endif
