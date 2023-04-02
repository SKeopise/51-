#include <config.h>



unsigned int ADC_Data = 0;


bit flag_100ms = 0;
bit flag_300ms = 0;
bit flag_01s = 0;


bit flag_Sonic_Reda_Start = 0;



void OutputSonicDAC();
void ReadData();

void main()
{

    LedBuzzInit();
    Timer0Init();
    

    
    while(1)
    {
        SmgShowMode();
        KeyDriver();
        ReadData();
    }

}


void Timer0Int() interrupt 1
{
    static unsigned int cnt = 0;

    cnt++;
    if((cnt % 100) == 0)
    {
        flag_100ms = 1;
        flag_01s = ~flag_01s;
    }
    if(cnt >= 300)
    {
        cnt = 0;
        flag_300ms = 1;
    }




    LedDisplay();
    SmgDisplay();
    KeyScan();

}


void ReadData()
{
    float ADC_Buf = 0;

    if(flag_100ms == 1)
    {
        flag_100ms = 0;
        ADC_Buf = ADC_ReadAIN3();
        ADC_Buf = ADC_Buf/51;
        ADC_Buf = ADC_Buf*100;
        ADC_Data = ADC_Buf;
    }
    if(flag_300ms == 1)
    {
        flag_300ms = 0;
        if((ADC_Data < Parm_ADC_MAX) && (ADC_Data > Parm_ADC_MIN_Buf))
        {
            flag_Sonic_Reda_Start = 1;
        }
        else
        {
            flag_Sonic_Reda_Start = 0;
        }
        if(flag_Sonic_Reda_Start == 1)
        {
            SonicReadDistence();
        }
        OutputSonicDAC();
    }
    
}

void OutputSonicDAC()
{
    float DAC_Dist_Buf = 0;

    if(flag_Sonic_Reda_Start == 1)
    {
        if(Sonic_Dist < 20)
        {
            OutputDAC(53);
        }
        else if(Sonic_Dist > 80)
        {
            OutputDAC(255);
        }
        else
        {
            DAC_Dist_Buf = Sonic_Dist;
            DAC_Dist_Buf = ((DAC_Dist_Buf/15)-0.333333);
            DAC_Dist_Buf = DAC_Dist_Buf*53.125;
            OutputDAC(DAC_Dist_Buf);
        }
    }
    else
    {
        OutputDAC(0);
    }
}


