#ifndef _LED_H
#define _LED_H



#include <config.h>






void SmgMenuMain();

void SmgDisplay();

void SmgMenuDataFreq();

void SmgMenuDataTemp();

void SmgMenuDataADC();

void SmgMenuBackupData();

void SmgMenuParmSet();

void LedDisplay();


sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit LED8 = P0^7;




#endif
