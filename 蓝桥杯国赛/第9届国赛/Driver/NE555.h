#ifndef _NE555_H
#define _NE555_H



#include <config.h>





void Timer0Init();

void NE555ReadFreqData(unsigned int *dat);



extern unsigned int Freq_Data;






#endif
