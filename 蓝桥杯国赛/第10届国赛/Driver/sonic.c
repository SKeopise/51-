#include "sonic.h"



sbit TX = P1^0;
sbit RX = P1^1;


bit Distence_Far = 0;
unsigned int Sonic_Distence = 0;



void PCA_Init()
{
	CMOD = 0x80;
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
	
	for(i=0;i<8;i++)
	{
		TX = 1;
		Delay13us();
		TX = 0;
		Delay13us();
	}
}


void Sonic_DataRead()
{
	unsigned int Data_Buf = 0;
	float Distence_Buf = 0;
	
	
	CH = 0x00;
	CL = 0x00;
	
	SendWave();
	CR = 1;
	while((RX == 1) && (CF == 0));
	CR = 0;
	
	if(CF == 1)
	{
		CF = 0;
		Distence_Far = 1;
	}
	else
	{		
		Data_Buf = CH;
		Data_Buf = (Data_Buf << 8) | CL;
		Distence_Buf = Data_Buf;
		Distence_Buf = Distence_Buf * 0.017;
		Data_Buf = Distence_Buf;
		if(Data_Buf > 99)
		{
			Distence_Far = 1;
		}
		else
		{
			Distence_Far = 0;
		}
	}
	
	if(Distence_Far == 0)
	{
		Sonic_Distence = Data_Buf;
	}
	else
	{
		Sonic_Distence = 99;
	}
}















