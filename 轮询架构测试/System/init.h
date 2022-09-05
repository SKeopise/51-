#ifndef _INIT_H_
#define _INIT_H_

#include <config.h>
#include <led.h>
#include <key.h>
#include <DS18B20.h>
#include <ds1302.h>


void TaskProcess();

void TaskRemarks();




void Timer0init();

void Timer1init();

void HC138(unsigned char Y);

void ALL_INIT();

void delay(unsigned int t);













#endif