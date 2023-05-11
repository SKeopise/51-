#ifndef _ONEWIRE_H
#define _ONEWIRE_H



#include <config.h>





void Delay_OneWire(unsigned int t);

void Write_DS18B20(unsigned char dat);

unsigned char Read_DS18B20(void);

bit init_ds18b20(void);


void Ds18b20TempConfig();

void Ds18b20TempRead();






#endif
