

#include "Sonic.h"


sbit TX = P1^0;
sbit RX = P1^1;


bit Sonic_Too_Far = 0;


void Delay14us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 39;
	while (--i);
}





void SendWave()
{
    unsigned char i = 0;

    for(i=0;i<8;i++)
    {
        TX = 1;
        Delay14us();
        TX = 0;
        Delay14us();
    }
}


unsigned int SonicDataRead()
{
    unsigned int Sonic_Time_Data = 0;
    float Sonic_Dir_Data = 0; 
    unsigned int len = 0;

    TH1 = 0x00;
    TL1 = 0x00;

    SendWave();
    TR1 = 1;
    while((TF1 == 0)&&(RX == 1));
    TR1 = 0;

    if(TF1 == 1)
    {
        TF1 = 0;
        Sonic_Too_Far = 1;
    }
    else
    {
        Sonic_Too_Far = 0;
        Sonic_Time_Data = TH1;
        Sonic_Time_Data = (Sonic_Time_Data<<8)|TL1;
        Sonic_Dir_Data = Sonic_Time_Data;
        Sonic_Dir_Data = Sonic_Dir_Data*0.017;
        len = Sonic_Dir_Data;
    }
    return len;
}






























