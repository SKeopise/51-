#include "Sonic.h"


sbit TX = P1^0;
sbit RX = P1^1;

unsigned int Sonic_Dist = 0;

bit Sonic_Dist_Far = 0;

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


void SonicReadDistence()
{
    unsigned int Sonic_Time = 0;
    float Sonic_Dist_Buf = 0;

    TH1 = 0x00;
    TL1 = 0x00;

    SendWave();

    TR1 = 1;
    while((TF1 == 0) && (RX == 1));
    TR1 = 0;

    if(TF1 == 1)
    {
        TF1 = 0;
        Sonic_Dist_Far = 1;
    }
    else
    {
        Sonic_Dist_Far = 0;
        Sonic_Time = TH1;
        Sonic_Time = Sonic_Time << 8;
        Sonic_Time = Sonic_Time | TL1;
        Sonic_Dist_Buf = Sonic_Time;
        Sonic_Dist_Buf = Sonic_Dist_Buf * 0.017;
        Sonic_Dist = Sonic_Dist_Buf;
    }


}


















