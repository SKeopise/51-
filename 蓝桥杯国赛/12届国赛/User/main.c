
#include <config.h>

#define LIGHT_DARK 51


unsigned int Sonic_Data_Save_Buff = 0;
unsigned int Sonic_Data_MAX = 0;
unsigned int Sonic_Data_MIN = 500;
unsigned int Sonic_Data_Sympal = 0;

unsigned int Sonic_Len_Data = 0;

unsigned char ADC_AIN1_Data = 0;

unsigned char flag_L5 = 0;

bit flag_Light_Dark = 0;

bit flag_Read_Sonic_Len = 0;
bit flag_First_Read = 0;

bit flag_100ms = 0;
bit flag_200ms = 0;


void ReadData();
void ReadSonicLens();
void SonicOutputDAC();
void SonicDataSave();



void main()
{

    LedBuzzInit();
    Timer0Init();
    Ds1302Init();
    Sonic_Data_Save_Buff = SonicDataRead();
    Sonic_Len_Data = Sonic_Data_Save_Buff;

    while(1)
    {
        ReadData();
        SmgShowMode();
        KeyDriver();
    }
}


void Timer0Int() interrupt 1
{
    static unsigned int cnt = 0;

    cnt++;

    if((cnt % 100) == 0)
    {
        flag_100ms = 1;

    }
    if(cnt>=250)
    {
        flag_200ms = 1;
        cnt = 0;
    }


    KeyScan();
    SmgDisplay();
    LedDisplay();

}


void ReadData()
{
    if(flag_200ms == 1)
    {
        flag_200ms = 0;
        Ds1302TimerRead();
    }
    if(flag_100ms == 1)
    {
        flag_100ms = 0;
        ADC_AIN1_Data = ADC_InputAIN1();
        if(ADC_AIN1_Data < LIGHT_DARK)
        {
            flag_Light_Dark = 0;
        }
        else
        {
            flag_Light_Dark = 1;
        }
    }
    ReadSonicLens();
    SonicDataSave();
    SonicOutputDAC();
}

void ReadSonicLens()
{
    unsigned char Timer_Data_Buff = 0;

    if(Read_Lens_Mode == 0)
    {
        if(ADC_AIN1_Data < LIGHT_DARK)
        {
            if(flag_First_Read == 0)
            {
                Sonic_Len_Data = SonicDataRead();
                flag_First_Read = 1;
                if((Sonic_Len_Data >= (Len_Parm-5)) && (Sonic_Len_Data <= (Len_Parm+5)))
                {
                    if(flag_L5 < 3)
                    {
                        flag_L5++;
                    }
                }
                else
                {
                    flag_L5 = 0;
                }                
            }     
        }
        else
        {
            flag_First_Read = 0;
        }
    }
    else
    {
        Timer_Data_Buff = (Timer_Data[0]>>4)*10 + (Timer_Data[0]&0x0F);
        if((Timer_Data_Buff % Read_Timer_Parm) == 0)
        {
            flag_Read_Sonic_Len = 1;
        }
        else
        {
            flag_Read_Sonic_Len = 0;
            flag_First_Read = 0;
        }
    }

    if((flag_Read_Sonic_Len == 1)&&(flag_First_Read == 0))
    {
        Sonic_Len_Data = SonicDataRead();
        flag_First_Read = 1;
        if((Sonic_Len_Data >= (Len_Parm-5)) && (Sonic_Len_Data <= (Len_Parm+5)))
        {
            if(flag_L5 < 3)
            {
                flag_L5++;
            }
        }
        else
        {
            flag_L5 = 0;
        }        
    }    
}


void SonicOutputDAC()
{
    unsigned char Output_Data = 0;
    float Data_Buf = 0;
    if(Sonic_Len_Data <= 10)
    {
        OutputDAC(53);
    }
    else if(Sonic_Len_Data >= 80)
    {
        OutputDAC(255);
    }
    else
    {
        Data_Buf = Sonic_Len_Data;
        Data_Buf = (0.057142*Data_Buf);
        Data_Buf = Data_Buf + 0.428571;
        Data_Buf = Data_Buf * 53.125;
        Output_Data = Data_Buf;
        OutputDAC(Output_Data);
    }

}

void SonicDataSave()
{
    float Sonic_Data_Sympal_Buf = 0;

    if(Sonic_Len_Data != Sonic_Data_Save_Buff)
    {
        Sonic_Data_Save_Buff = Sonic_Len_Data;

        if(Sonic_Data_Save_Buff > Sonic_Data_MAX)
        {
            Sonic_Data_MAX = Sonic_Data_Save_Buff;
        }

        if(Sonic_Data_Save_Buff < Sonic_Data_MIN)
        {
            if(Sonic_Data_Save_Buff != 0)
            {
                Sonic_Data_MIN = Sonic_Data_Save_Buff;
            }
        }

        Sonic_Data_Sympal_Buf = Sonic_Data_Sympal;
        Sonic_Data_Sympal_Buf = Sonic_Data_Sympal_Buf/10;
        Sonic_Data_Sympal_Buf = Sonic_Data_Sympal_Buf + Sonic_Data_Save_Buff;
        Sonic_Data_Sympal_Buf = Sonic_Data_Sympal_Buf/2;
        Sonic_Data_Sympal_Buf = Sonic_Data_Sympal_Buf*10;
        Sonic_Data_Sympal = Sonic_Data_Sympal_Buf;
    }
}


