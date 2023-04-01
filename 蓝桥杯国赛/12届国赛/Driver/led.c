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
        if(Show_Data_Mode == 0)
        {
            LED1 = 0;
        }
        else if(Show_Data_Mode == 1)
        {
            LED2 = 0;
        }
        else if(Show_Data_Mode == 2)
        {
            LED3 = 0;
        }
    }

    if(Read_Lens_Mode == 0)
    {
        LED4 = 0;
    }
    else
    {
        if(flag_L5 == 3)
        {
            LED5 = 0;
        }
    }

    if(flag_Light_Dark == 1)
    {
        LED6 = 0;
    }


    HC138Set(4);
    HC138Set(0);
}



void SmgShowMode()
{
    if(Show_Mode == 0)
    {
        if(Show_Data_Mode == 0)
        {
            SmgShowTimer();
        }
        else if(Show_Data_Mode == 1)
        {
            SmgShowLenData();
        }
        else if(Show_Data_Mode == 2)
        {
            SmgShowSaveDataMode();
        }
    }
    else
    {
        SmgShowParmSet();
    }


}

void SmgShowInit()
{
    unsigned char i = 0;
    for(i=0;i<8;i++)
    {
        Led_Buff[i] = Led_Number[10];
    }
}

void SmgShowParmSet()
{
    Led_Buff[0] = 0x8C;

    if(Show_Parm_Mode == 0)
    {
        Led_Buff[1] = Led_Number[1];
        Led_Buff[6] = Led_Number[(Read_Timer_Parm_Buf/10)%10];
        Led_Buff[7] = Led_Number[Read_Timer_Parm_Buf%10];        
    }
    else
    {
        Led_Buff[1] = Led_Number[2];
        Led_Buff[6] = Led_Number[(Len_Parm_Buf/10)%10];
        Led_Buff[7] = Led_Number[Len_Parm_Buf%10];         
    }
    Led_Buff[2] = Led_Number[10];
    Led_Buff[3] = Led_Number[10];
    Led_Buff[4] = Led_Number[10];
    Led_Buff[5] = Led_Number[10];        

}


void SmgShowSaveDataMode()
{
    Led_Buff[0] = 0x89;

    if(Data_Save_Mode == 0)     //最大值显示
    {
        Led_Buff[1] = 0xFE;

        if(Sonic_Data_MAX >= 1000)
        {
            Led_Buff[4] = Led_Number[(Sonic_Data_MAX/1000)%10];
        }
        else
        {
            Led_Buff[4] = Led_Number[10];
        }
        if(Sonic_Data_MAX >= 100)
        {
            Led_Buff[5] = Led_Number[(Sonic_Data_MAX/100)%10];
        }
        else
        {
            Led_Buff[5] = Led_Number[10];
        }  
        if(Sonic_Data_MAX >= 10)
        {
            Led_Buff[6] = Led_Number[(Sonic_Data_MAX/10)%10];
        }
        else
        {
            Led_Buff[6] = Led_Number[10];
        }   
        Led_Buff[7] = Led_Number[Sonic_Data_MAX%10];           
    }
    else if(Data_Save_Mode == 1)    //最小值
    {
        Led_Buff[1] = 0xBF;
        if(Sonic_Data_MIN >= 1000)
        {
            Led_Buff[4] = Led_Number[(Sonic_Data_MIN/1000)%10];
        }
        else
        {
            Led_Buff[4] = Led_Number[10];
        }
        if(Sonic_Data_MIN >= 100)
        {
            Led_Buff[5] = Led_Number[(Sonic_Data_MIN/100)%10];
        }
        else
        {
            Led_Buff[5] = Led_Number[10];
        }  
        if(Sonic_Data_MIN >= 10)
        {
            Led_Buff[6] = Led_Number[(Sonic_Data_MIN/10)%10];
        }
        else
        {
            Led_Buff[6] = Led_Number[10];
        }   
        Led_Buff[7] = Led_Number[Sonic_Data_MIN%10];         
    }
    else if(Data_Save_Mode == 2)
    {
        Led_Buff[1] = 0xF7;
        if(Sonic_Data_Sympal >= 1000)
        {
            Led_Buff[4] = Led_Number[(Sonic_Data_Sympal/1000)%10];
        }
        else
        {
            Led_Buff[4] = Led_Number[10];
        }
        if(Sonic_Data_Sympal >= 100)
        {
            Led_Buff[5] = Led_Number[(Sonic_Data_Sympal/100)%10];
        }
        else
        {
            Led_Buff[5] = Led_Number[10];
        }  
        Led_Buff[6] = Led_Number[(Sonic_Data_Sympal/10)%10] & 0x7F;
        Led_Buff[7] = Led_Number[Sonic_Data_Sympal%10];           
    }
    Led_Buff[2] = Led_Number[10];
    Led_Buff[3] = Led_Number[10];
}


void SmgShowLenData()
{
    Led_Buff[0] = 0xC7;

    if(Read_Lens_Mode == 0)
    {
        Led_Buff[1] = 0xC6;
    }
    else
    {
        Led_Buff[1] = 0x8E;
    }

    Led_Buff[2] = Led_Number[10];
    Led_Buff[3] = Led_Number[10];
    Led_Buff[4] = Led_Number[10];

    if(Sonic_Too_Far == 0)
    {
        if(Sonic_Len_Data < 100)
        {
            Led_Buff[5] = Led_Number[10];
        }            
        else
        {
            Led_Buff[5] = Led_Number[(Sonic_Len_Data/100)%10];
        }

        if(Sonic_Len_Data < 10)
        {
            Led_Buff[6] = Led_Number[10];
        }            
        else
        {
            Led_Buff[6] = Led_Number[(Sonic_Len_Data/10)%10];
        }    
    }

    Led_Buff[7] = Led_Number[Sonic_Len_Data%10];

}



void SmgShowTimer()
{
    Led_Buff[0] = Led_Number[Timer_Data[2]>>4];
    Led_Buff[1] = Led_Number[Timer_Data[2]&0x0F];

    Led_Buff[2] = 0xBF;

    Led_Buff[3] = Led_Number[Timer_Data[1]>>4];
    Led_Buff[4] = Led_Number[Timer_Data[1]&0x0F];

    Led_Buff[5] = 0xBF;

    Led_Buff[6] = Led_Number[Timer_Data[0]>>4];
    Led_Buff[7] = Led_Number[Timer_Data[0]&0x0F];

}








void SmgDisplay()
{
    static unsigned char i = 0;

    P0 = 0x00;
    HC138Set(6);
    P0 = 0x01<<i;
    HC138Set(0);

    P0 = 0xFF;
    HC138Set(7);
    P0 = Led_Buff[i];
    HC138Set(0);

    i++;
    i &= 0x07;
}


















