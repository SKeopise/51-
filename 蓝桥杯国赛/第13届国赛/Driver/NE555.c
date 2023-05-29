#include "NE555.h"



unsigned int NE555_Freq = 0;



void NE555Init()
{
	TH0 = 0x00;
	TL0 = 0x00;
	TMOD |= 0x05;
	TR0 = 1;
	TF0 = 0;
	ET0 = 0;
}


void NE555FreqReadData(unsigned int *freq)
{
	if(TF0 == 0)
	{
		*freq = TH0;
		*freq = (*freq << 8) | TL0;
	}
	else
	{
		TF0 = 0;
	}
	TH0 = 0x00;
	TL0 = 0x00;	
}













