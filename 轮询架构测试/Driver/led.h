#ifndef _LED_H_
#define _LED_H_




#include <config.h>
#include <init.h>


extern int temp;
extern unsigned char workmod;
extern unsigned char pdata Timer[7];



//void Led_Display();

void Led_interrupt();

//void Led_DS18B20();

void Led_18B20Buff();

void Led_DS1302Buff();









#endif