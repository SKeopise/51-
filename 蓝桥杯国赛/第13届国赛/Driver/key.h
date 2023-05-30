#ifndef _KEY_H
#define _KEY_H




#include <config.h>



void KeyDriver();

void KeyScan();

void MenuSelectModeS4();

void ParmSelectModeS5();

void ParmDataIncS6();

void ParmDataDecS7();




extern unsigned char Menu_Mode;
extern unsigned char Menu_Parm;

extern unsigned int Parm_Freq;
extern unsigned int Parm_Freq_Buf;

extern unsigned char Parm_RH;
extern unsigned char Parm_RH_Buf;

extern unsigned char Parm_Distence;
extern unsigned char Parm_Distence_Buf;

extern bit freq_mode;
extern bit distence_mode;

extern bit flag_S7_LongSet;



sbit KEY_OUT_0 = P3^0;
sbit KEY_OUT_1 = P3^1;
sbit KEY_OUT_2 = P3^2;
sbit KEY_OUT_3 = P3^3;







#endif
