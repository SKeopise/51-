#ifndef _LED_H
#define _LED_H





#include <config.h>






void SmgDisplay();

void SmgMenuMain();

void SmgMenuDistence();

void SmgMenuBackup();

void SmgMenuParm();

void LedDisplay();





extern bit flag_Led1;
extern bit flag_LedFlash;

extern unsigned char Led_FlashCnt;

sbit LED1 = P0^0;
sbit LED7 = P0^6;
sbit LED8 = P0^7;






#endif
