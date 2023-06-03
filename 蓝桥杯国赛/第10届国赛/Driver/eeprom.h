#ifndef _EEPROM_H
#define _EEPROM_H





#include <config.h>

#define PARM_CNT_ADDR_HIGH 0x10
#define PARM_CNT_ADDR_LOW 0x11




void EEPROM_ReadData(unsigned char addr,unsigned char *dat);

void EEPROM_WriteData(unsigned char addr,unsigned char dat);

void FirstRead_EEPROM();


void EEPROM_ReadUnsignedInt(unsigned char addrH,unsigned char addrL,unsigned int *dat);

void EEPROM_WriteUnsignedInt(unsigned char addrH,unsigned char addrL,unsigned int *dat);


#endif
