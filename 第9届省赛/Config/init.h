#ifndef _INIT_H_
#define _INIT_H_



#include <config.h>



void HC138(unsigned char Y);

void BuzzLedInit();

void Timer0Init(void);

bit LedPwm(unsigned char pwm);

void LedTimerDataRead();

void LedTimerDataWrite(unsigned char DataCode);

void LedTimerRead();










#endif
