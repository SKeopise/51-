#ifndef _DS18B20_H
#define	_DS18B20_H



#include <config.h>


sbit DQ = P1^4;  



void Delay_OneWire(unsigned int t);

void Write_DS18B20(unsigned char dat);


unsigned char Read_DS18B20(void);

bit init_ds18b20(void);

unsigned int DS18B20_Read();










#endif
