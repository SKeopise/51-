#include "sonic.h"


sbit TX = P1^0;
sbit RX = P1^1;

unsigned int Sonic_Data_Distence = 0;

bit flag_Sonic_Far = 0;


void InitPCA()
{
	CMOD |= 0x80;
	CCON = 0x00;
}

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
	
	EA = 0;
	for(i=0;i<8;i++)
	{
		TX = 1;
		Delay13us();
		TX = 0;
		Delay13us();
	}
	EA = 1;
}


void SonicDataRead()
{
	unsigned int Sonic_Time_Buf = 0;
	float Distence_Buf = 0;
	
	CH = 0x00;
	CL = 0x00;
	
	SendWave();
	CR = 1;
	while((CF == 0) && (RX == 1));
	CR = 0;
	
	if(CF == 1)
	{
		CF = 0;
		flag_Sonic_Far = 1;
		Sonic_Data_Distence = 999;
	}
	else
	{
		flag_Sonic_Far = 0;
		Sonic_Time_Buf = CH;
		Sonic_Time_Buf = (Sonic_Time_Buf << 8) | CL;
		Distence_Buf = Sonic_Time_Buf;
		Distence_Buf = Distence_Buf*0.017;
		Sonic_Data_Distence = Distence_Buf; 
	}	
}



















