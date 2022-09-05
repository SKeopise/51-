#ifndef _KEY_H_
#define _KEY_H_


#include <config.h>
#include <init.h>
#include <EEPROM.h>

extern unsigned char WorkMod,LedMod;
extern unsigned char yuzhi;

void Key_Action(unsigned char keycode);

void Key_Driver();

void Key_Scan();





















#endif