#ifndef _EEPROM_H
#define _EEPROM_H





#include <config.h>



#define SONIC_DATA_ADDR 0x10

#define DISTENCE_CNT_ADDR 0x02

#define PARM_ADDR 0x05



void EEPROM_WriteByte(unsigned char addr,unsigned char dat);

void EEPROM_ReadByte(unsigned char addr,unsigned char *dat);

void EEPROM_WriteInt(unsigned char addrH,unsigned char addrL,unsigned int *dat);

void EEPROM_ReadInt(unsigned char addrH,unsigned char addrL,unsigned int *dat);

void ReadHistoryData();

void ClearEEPROM();

void FirstReadData();



#endif
