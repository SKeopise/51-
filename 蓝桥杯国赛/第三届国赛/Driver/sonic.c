
#include "sonic.h"


bit Sonic_Far = 0;
unsigned int Sonic_Time = 0;
float Sonic_Dist = 0;

void Delay13us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 36;
	while (--i);
}



void SendWave()
{
	unsigned char i = 0;
	
	for(i=0;i<8;i++)
	{
		TX = 1;
		Delay13us();
		TX = 0;
		Delay13us();
	}
}

void Sonic()
{
	TL1 = 0x00;
	TH1 = 0x00;
	
	SendWave();
	TR1 = 1;
	while((RX == 1) && (TF1 == 0));
	TR1 = 0;
	
	if(TF1 == 1)
	{
		TF1 = 0;
		Sonic_Far = 1;
	}
	else
	{
		Sonic_Far = 0;
		Sonic_Time = TH1;
		Sonic_Time = (Sonic_Time << 8) | TL1;
		Sonic_Dist = Sonic_Time*0.017;
		if((Door_Mod == 0)&&(Door_Open != 1))
		{
			if(Sonic_Dist <= 30)
			{
				Door_Open = 1;
			}
		}
	}	
}













