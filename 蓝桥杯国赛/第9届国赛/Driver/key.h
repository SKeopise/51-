#ifndef _KEY_H
#define _KEY_H



#include <config.h>






void KeyDriver();

void KeyScan();

void MenuModeSelectS4();

void MenuBackupDataS6();

void MenuParmSetS7();

void SaveDataS5();


extern unsigned char MenuMode_Data;
extern unsigned char MenuMode_Backup;
extern unsigned char MenuMode_Main;

extern bit flag_StartKey6;
extern unsigned int Key6_SetTime;

extern unsigned char ADC_Data_EEPROM;
extern unsigned int Temp_Data_EEPROM;
extern unsigned int Freq_Data_EEPROM;

extern unsigned char Parm_ADC;
extern unsigned char Parm_ADC_Buf;



sbit KEY_OUT_0 = P3^0;
sbit KEY_OUT_1 = P3^1;
sbit KEY_OUT_2 = P3^2;
sbit KEY_OUT_3 = P3^3;






#endif
