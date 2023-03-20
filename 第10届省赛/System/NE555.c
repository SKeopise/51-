#include "NE555.h"



unsigned int NE555_Timer_Cnt = 0;
unsigned int NE555_Freq = 0;






void NE555Timer0Init()
{
	TH0 = 0xFF;
	TL0 = 0xFF;
	
	TMOD |= 0x06;
	TF0 = 0;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

void NE555Timer0Int() interrupt 1
{
	NE555_Timer_Cnt++;
}
















