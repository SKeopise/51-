#ifndef __ONEWIRE_H
#define __ONEWIRE_H

#include <config.h>


sbit DQ = P1^4;  


void DS18B20Init();

void ReadTempData();



unsigned char rd_temperature(void);

void Delay_OneWire(unsigned int t);

void Write_DS18B20(unsigned char dat);

unsigned char Read_DS18B20(void);

bit init_ds18b20(void);

#endif
