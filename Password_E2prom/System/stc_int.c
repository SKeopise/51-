
#include <config.h>

#include <stc_int.h>


void ConfigTimer0(unsigned int ms)
{
	unsigned long tmp = 0;
	
	tmp = 11059200/12;
	tmp = (tmp*ms)/1000;
	tmp = 65535 - tmp;
	tmp = tmp + 33;
	T0RH = (unsigned char)(tmp >> 8);
	T0RL = (unsigned char)tmp;
	TMOD &= 0x00;
	TMOD |= 0x11;
	TH0 = T0RH;
	TL0 = T0RL;
	ET0 = 1;
	TR0 = 1;
	
}











