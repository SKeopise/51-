#ifndef _EEPROM_H_
#define _EEPROM_H_


#include <config.h>



unsigned char ReadEEPROM(unsigned char addr);

void WriteEEPROM(unsigned char addr,unsigned char dat);

void AT24C02PasswordRead();

void AT24C02PasswordWrite();

void AT24C02FirstRead();








#endif
