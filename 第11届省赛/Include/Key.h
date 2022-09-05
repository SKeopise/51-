#ifndef _KEY_H_
#define _KEY_H_


#include <config.h>
#include <init.h>
#include <Led.h>
#include <EEPROM.h>


extern unsigned char code Led_SMG[];



void Key_Btn();
void KeyAction_01(unsigned char keycode);
void Key_Driver();
void Key_Scan();



















#endif