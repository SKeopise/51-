#ifndef _KEY_H
#define _KEY_H




#include <config.h>



void KeyDriver();

void KeyScan();






sbit KEY_OUT_0 = P3^0;
sbit KEY_OUT_1 = P3^1;
sbit KEY_OUT_2 = P3^2;
sbit KEY_OUT_3 = P3^3;







#endif
