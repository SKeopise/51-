#include "led.h"


code unsigned char Led_Number[] =
{
    0xc0, //0
    0xf9, //1
    0xa4, //2
    0xb0, //3
    0x99, //4
    0x92, //5
    0x82, //6
    0xf8, //7
    0x80, //8
    0x90, //9
    0xFF
};


unsigned char Led_Buff[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};






void LedDisplay()
{
    P0 = 0xFF;

    if(Show_Mode == 0)
    {
        LED1 = 0;
    }
    else if(Show_Mode == 1)
    {
        LED2 = 0;
    }
    else
    {
        LED3 = 0;
    }

    if(flag_Sonic_Reda_Start == 1)
    {
        if(flag_01s == 1)
        {
            LED8 = 0;
        }
    }

    HC138Set(4);
    HC138Set(0);
}


void SmgShowMode()
{
    if(Show_Mode == 0)
    {
        SmgShowADC();
    }
    else if(Show_Mode == 1)
    {
        SmgShowSonicDistence();
    }
    else if(Show_Mode == 2)
    {
        SmgShowParmSet();
    }
}


void SmgShowParmSet()
{
    Led_Buff[0] = 0x8C;

    Led_Buff[1] = Led_Number[10];
    Led_Buff[2] = Led_Number[10];
    Led_Buff[5] = Led_Number[10];
    
    if(Parm_Mode == 0)
    {
        Led_Buff[3] = Led_Number[(Parm_ADC_MAX_Buf/100)%10];
        Led_Buff[4] = Led_Number[(Parm_ADC_MAX_Buf/10)%10];
        Led_Buff[6] = Led_Number[10];
        Led_Buff[7] = Led_Number[10];        
    }  
    else
    {
        Led_Buff[6] = Led_Number[(Parm_ADC_MIN_Buf/100)%10];
        Led_Buff[7] = Led_Number[(Parm_ADC_MIN_Buf/10)%10];
        Led_Buff[3] = Led_Number[10];
        Led_Buff[4] = Led_Number[10];                
    }  
}


void SmgShowSonicDistence()
{
    Led_Buff[0] = 0xC7;

    Led_Buff[1] = Led_Number[10];
    Led_Buff[2] = Led_Number[10];
    Led_Buff[3] = Led_Number[10];
    Led_Buff[4] = Led_Number[10];

    if(flag_Sonic_Reda_Start == 0)
    {
        Led_Buff[5] = 0x88;
        Led_Buff[6] = 0x88;
        Led_Buff[7] = 0x88;        
    }    
    else
    {
        if(Sonic_Dist_Far == 0)
        {
            if(Sonic_Dist >= 100)
            {
                Led_Buff[5] = Led_Number[(Sonic_Dist/100)%10];
            }
            else
            {
                Led_Buff[5] = Led_Number[10];
            }
            if(Sonic_Dist >= 10)
            {
                Led_Buff[6] = Led_Number[(Sonic_Dist/10)%10];
            }
            else
            {
                Led_Buff[6] = Led_Number[10];
            }
            Led_Buff[7] = Led_Number[Sonic_Dist%10];       
        }     
        else
        {
            Led_Buff[5] = 0xBF;
            Led_Buff[6] = 0xBF;
            Led_Buff[7] = 0xBF;            
        }
    }
}


void SmgShowADC()
{
    Led_Buff[0] = 0xC1;

    Led_Buff[1] = Led_Number[10];
    Led_Buff[2] = Led_Number[10];
    Led_Buff[3] = Led_Number[10];
    Led_Buff[4] = Led_Number[10];

    Led_Buff[5] = Led_Number[(ADC_Data/100)%10] & 0x7F;
    Led_Buff[6] = Led_Number[(ADC_Data/10)%10];
    Led_Buff[7] = Led_Number[ADC_Data%10];
}







void SmgDisplay()
{
    static unsigned char i = 0;

    P0 = 0x00;
    HC138Set(6);
    P0 = 0x01 << i;
    HC138Set(0);

    P0 = 0xFF;
    HC138Set(7);
    P0 = Led_Buff[i];
    HC138Set(0);

    i++;
    i &= 0x07;

}















