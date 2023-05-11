#ifndef _LED_H_
#define _LED_H_



#include <config.h>





void SmgDisplay();

void SmgMenuMain();

void SmgMenuTimer();

void SmgMenuBackupDataTempC();

void SmgMenuBackupDataHumidityH();

void SmgMenuBackupDataTimerAndTripF();

void SmgMenuBackup();

void SmgMenuParmData();

void SmgMenuInterruptTempHum();

void LedDisplay();



sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit LED4 = P0^3;
sbit LED5 = P0^4;
sbit LED6 = P0^5;
sbit LED7 = P0^6;






#endif



