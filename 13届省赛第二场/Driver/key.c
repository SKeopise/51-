#include "key.h"


unsigned char code Key_Map[4] = {'7','6','5','4'};


unsigned char Key_Sta[4] = {1,1,1,1}; 



unsigned int Parm_ADC_MAX = 450;
unsigned int Parm_ADC_MAX_Buf = 450;

unsigned int Parm_ADC_MIN = 50;
unsigned int Parm_ADC_MIN_Buf = 50;


unsigned char Show_Mode = 0;

bit Parm_Mode = 0;





void KeyAction0(unsigned char keycode)
{
    if(keycode == '7')
    {
        if(Show_Mode == 2)
        {
            KeyParmReduce();
        }
    }
    else if(keycode == '6')
    {
        if(Show_Mode == 2)
        {
            KeyParmAdd();
        }
    }
    else if(keycode == '5')
    {
        KeyParmModeChange();
    }
    else if(keycode == '4')
    {
        KeyShowModeChange();
    }    
}


void KeyShowModeChange()
{
    Show_Mode++;
    if(Show_Mode > 2)
    {
        Show_Mode = 0;
        Parm_ADC_MAX = Parm_ADC_MAX_Buf;
        Parm_ADC_MIN = Parm_ADC_MIN_Buf;
    }
}

void KeyParmModeChange()
{
    if(Show_Mode == 2)
    {
        if(Parm_Mode == 0)
        {
            Parm_Mode = 1;
        }
        else
        {
            Parm_Mode = 0;
        }
    }
}

void KeyParmAdd()
{
    if(Parm_Mode == 0)
    {
        Parm_ADC_MAX_Buf += 50;
        if(Parm_ADC_MAX_Buf > 500)
        {
            Parm_ADC_MAX_Buf = 50;
        }
    }
    else
    {
        Parm_ADC_MIN_Buf += 50;
        if(Parm_ADC_MIN_Buf > 500)
        {
            Parm_ADC_MIN_Buf = 50;
        }
    }
}

void KeyParmReduce()
{
    if(Parm_Mode == 0)
    {
        Parm_ADC_MAX_Buf -= 50;
        if(Parm_ADC_MAX_Buf < 50)
        {
            Parm_ADC_MAX_Buf = 500;
        }
    }
    else
    {
        Parm_ADC_MIN_Buf -= 50;
        if(Parm_ADC_MIN_Buf < 50)
        {
            Parm_ADC_MIN_Buf = 500;
        }
    }
}




void KeyDriver()
{
    unsigned char i = 0;
    static unsigned char Key_Backup[4] = {1,1,1,1};

    for(i=0;i<4;i++)
    {
        if(Key_Backup[i] != Key_Sta[i])
        {
            if(Key_Backup[i] == 1)
            {
                KeyAction0(Key_Map[i]);
            }

            Key_Backup[i] = Key_Sta[i];
        }
    }

}





void KeyScan()
{
    static unsigned char Key_Out = 0;
    static unsigned char Key_Buff[4] = {0xFF,0xFF,0xFF,0xFF};


    switch(Key_Out)
    {
        case 0: Key_Buff[0] = (Key_Buff[0] << 1) | KEY_OUT_0; break;
        case 1: Key_Buff[1] = (Key_Buff[1] << 1) | KEY_OUT_1; break;
        case 2: Key_Buff[2] = (Key_Buff[2] << 1) | KEY_OUT_2; break;
        case 3: Key_Buff[3] = (Key_Buff[3] << 1) | KEY_OUT_3; break;
        default: break;
    }

    if((Key_Buff[Key_Out] & 0x0F) == 0X00)
    {
        Key_Sta[Key_Out] = 0;
    }
    else if((Key_Buff[Key_Out] & 0x0F) == 0X0F)
    {
        Key_Sta[Key_Out] = 1;
    }    

    Key_Out++;
    Key_Out &= 0x03;
}













