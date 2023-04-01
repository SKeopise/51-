#ifndef _KEY_H
#define _KEY_H



#include <config.h>



void KeyDriver();

void KeyScan();

void MainShowModeChange();

void DataParmShowModeChange();

void SonicDataReadAndSaveModeChange();

void ParmDataChangeAndSave();






sbit KEY_OUT_0 = P3^0;
sbit KEY_OUT_1 = P3^1;
sbit KEY_OUT_2 = P3^2;
sbit KEY_OUT_3 = P3^3;

sbit KEY_IN_0 = P4^4;
sbit KEY_IN_1 = P4^2;
sbit KEY_IN_2 = P3^5;
sbit KEY_IN_3 = P3^4;








#endif
