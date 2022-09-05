#ifndef _DS18B20_H_
#define _DS18B20_H_




#include <config.h>
#include <onewire.h>
#include <led.h>



bit Get18B20Ack();

bit Start18B20();

bit Get18B20Temp();

void DS18B20_Read();






#endif