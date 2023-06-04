#ifndef _EEPROM_H
#define _EEPROM_H



#include <config.h>


#define ADC_DATA_ADDR 0x05

#define TEMP_DATA_ADDR_HIGH 0x10
#define TEMP_DATA_ADDR_LOW 0x11

#define FREQ_DATA_ADDR_HIGH 0x20
#define FREQ_DATA_ADDR_LOW 0x21





void EEPROM_ReadData(unsigned char addr,unsigned char *dat);

void EEPROM_WriteData(unsigned char addr,unsigned char dat);


void EEPROM_WriteDataUint(unsigned char addrH,unsigned char addrL,unsigned int dat);

void EEPROM_ReadDataUint(unsigned char addrH,unsigned char addrL,unsigned int *dat);

void EEPROM_FirstRead();





#endif
