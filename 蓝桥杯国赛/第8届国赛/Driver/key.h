#ifndef _KEY_H
#define _KEY_H





#include <config.h>





void KeyDriver();
void KeyScan();

void DistenceRead_Start();



extern unsigned char Distence_Cnt;

extern unsigned char Menu_Mode;

extern bit flag_DataShowMode;
extern unsigned char DataBackup_Cnt;

extern unsigned char Parm_Distence;
extern unsigned char Parm_Distence_Buf;

extern unsigned int Distence_LastIncNow;



sbit KEY_OUT_0 = P3^0;
sbit KEY_OUT_1 = P3^1;
sbit KEY_OUT_2 = P3^2;
sbit KEY_OUT_3 = P3^3;








#endif
