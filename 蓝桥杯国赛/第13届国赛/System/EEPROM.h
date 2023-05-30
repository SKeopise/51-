#ifndef _EEPROM_H
#define _EEPROM_H




#include <config.h>







void DataReadEEPROM(unsigned char addr,unsigned char *dat);

void DataWriteEEPROM(unsigned char addr,unsigned char dat);

void FirstReadEEPROM();










#endif
