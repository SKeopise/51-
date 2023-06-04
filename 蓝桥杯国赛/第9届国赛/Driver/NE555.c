#include "NE555.h"



unsigned int Freq_Data = 0;





void Timer0Init()
{
	TH0 = 0x00;
	TL0 = 0x00;
	TMOD |= 0x05;
	ET0 = 0;
	TF0 = 0;
	TR0 = 1;
}


void NE555ReadFreqData(unsigned int *dat)
{
	if(TF0 == 0)
	{
		*dat = TH0;
		*dat = (*dat << 8) | TL0;
	}
	else
	{
		TF0 = 0;
	}
	TH0 = 0x00;
	TL0 = 0x00;	
}

















