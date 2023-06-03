#ifndef _KEY_H
#define _KEY_H





#include <config.h>





void KeyScan();

void KeyDriver();


extern bit flag_Key_Set;

extern bit Menu_Mode;

extern unsigned char Menu_Data;

extern bit Menu_Parm;

extern unsigned int Parm_ChangCnt;

extern unsigned int ParmData_Temp;
extern unsigned int ParmData_Temp_Buf;

extern unsigned char ParmData_Distence;
extern unsigned char ParmData_Distence_Buf;

sbit KEY_OUT_0 = P3^0;
sbit KEY_OUT_1 = P3^1;
sbit KEY_OUT_2 = P3^2;
sbit KEY_OUT_3 = P3^3;

sbit KEY_IN_0 = P4^4;
sbit KEY_IN_1 = P4^2;
sbit KEY_IN_2 = P3^5;
sbit KEY_IN_3 = P3^4;




#endif
