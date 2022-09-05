#ifndef _EEPROM_H_
#define _EEPROM_H_



#include <iic.h>



unsigned char Read_EEPROM(unsigned char addr);

void Write_EEPROM(unsigned char addr,unsigned char dat);





#endif





