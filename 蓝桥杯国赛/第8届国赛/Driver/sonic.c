#include "sonic.h"



sbit TX = P1^0;
sbit RX = P1^1;


unsigned int Sonic_HistoryData[10] = {0,0,0,0,0,0,0,0,0,0};

unsigned int Sonic_Distence = 0;



void Delay13us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 36;
	while (--i);
}



void PCA_Init()
{
	CMOD |= 0x80;
	CCON = 0x00;
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



void Sonic_DistenceRead()
{
	float Data_Buf = 0;
	unsigned int Time_Buf = 0;
	
	CH = 0x00;
	CL = 0x00;
	
	SendWave();
	CR = 1;
	while((RX == 1) && (CF == 0));
	CR = 0;
	
	if(CF == 1)
	{
		CF = 0;
		Sonic_Distence = 0;
	}
	else
	{
		Time_Buf = CH;
		Time_Buf = (Time_Buf << 8) | CL;
		Data_Buf = Time_Buf;
		Data_Buf *= 0.017;
		Sonic_Distence = Data_Buf;
	}
	
}











