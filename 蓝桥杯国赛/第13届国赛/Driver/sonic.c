#include "sonic.h"


sbit TX = P1^0;
sbit RX = P1^1;

unsigned int Sonic_Data_Distence = 0;

bit flag_Sonic_Far = 0;


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


void SonicDataRead()
{
	unsigned int Sonic_Time_Buf = 0;
	float Distence_Buf = 0;
	
	TH1 = 0x00;
	TL1 = 0x00;
	
	SendWave();
	TR1 = 1;
	while((TF1 == 0) && (RX == 1));
	TR1 = 0;
	
	if(TF1 == 1)
	{
		TF1 = 0;
		flag_Sonic_Far = 1;
	}
	else
	{
		flag_Sonic_Far = 0;
		Sonic_Time_Buf = TH1;
		Sonic_Time_Buf = (Sonic_Time_Buf << 8) | TL1;
		Distence_Buf = Sonic_Time_Buf;
		Distence_Buf = Distence_Buf*0.017;
		Sonic_Data_Distence = Distence_Buf; 
	}	
}



















