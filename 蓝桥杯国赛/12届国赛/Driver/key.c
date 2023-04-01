#include "key.h"




unsigned char code Key_Map[4][4] = {
    {'0','0','0','0'},
    {'0','0','0','0'},
    {'5','9','0','0'},
    {'4','8','0','0'}
};

unsigned char pdata Key_Sta[4][4] = {
    {1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
};


unsigned char Read_Timer_Parm = 2;
unsigned char Read_Timer_Parm_Buf = 2;
unsigned char Len_Parm = 20;
unsigned char Len_Parm_Buf = 20;

bit Show_Mode = 0;

unsigned char pdata Show_Data_Mode = 0;
bit Show_Parm_Mode = 0;

bit Read_Lens_Mode = 0;
unsigned char Data_Save_Mode = 0;



void KeyAction0(unsigned char keycode)
{
    SmgShowInit();
    if(keycode == '4')
    {
        MainShowModeChange();
    }
    else if(keycode == '5')
    {
        DataParmShowModeChange();
    }
    else if(keycode == '8')
    {
        SonicDataReadAndSaveModeChange();
    }
    else if(keycode == '9')
    {
        ParmDataChangeAndSave();
    }

}



void KeyDriver()
{
    unsigned char i,j;
    static unsigned char pdata Key_Backup[4][4] = {
        {1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
    };

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(Key_Backup[i][j] != Key_Sta[i][j])
            {
                if(Key_Backup[i][j] == 1)
                {
                    KeyAction0(Key_Map[i][j]);
                }

                Key_Backup[i][j] = Key_Sta[i][j];
            }
        }
    }

}





void KeyScan()
{
    unsigned char i = 0;
    static unsigned char Key_Out = 0;
    static unsigned char Key_Buff[4][4] = {
        {0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
        {0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF}
    };

    Key_Buff[Key_Out][0] = (Key_Buff[Key_Out][0] << 1) | KEY_IN_0;
    Key_Buff[Key_Out][1] = (Key_Buff[Key_Out][1] << 1) | KEY_IN_1;
    Key_Buff[Key_Out][2] = (Key_Buff[Key_Out][2] << 1) | KEY_IN_2;
    Key_Buff[Key_Out][3] = (Key_Buff[Key_Out][3] << 1) | KEY_IN_3;

    for(i=0;i<4;i++)
    {
        if((Key_Buff[Key_Out][i] & 0x0F) == 0x00)
        {
            Key_Sta[Key_Out][i] = 0;
        }
        else if((Key_Buff[Key_Out][i] & 0x0F) == 0x0F)
        {
            Key_Sta[Key_Out][i] = 1;
        }        
    }

    Key_Out++;
    Key_Out &= 0x03;

    switch(Key_Out)
    {
        case 0: KEY_OUT_0 = 0; KEY_OUT_3 = 1; break;
        case 1: KEY_OUT_1 = 0; KEY_OUT_0 = 1; break;
        case 2: KEY_OUT_2 = 0; KEY_OUT_1 = 1; break;
        case 3: KEY_OUT_3 = 0; KEY_OUT_2 = 1; break;
        default: break;
    }
}





void MainShowModeChange()
{
    if(Show_Mode == 0)
    {
        Show_Mode = 1;
        Show_Parm_Mode = 0;
        Len_Parm_Buf = Len_Parm;
        Read_Timer_Parm_Buf = Read_Timer_Parm;
    }
    else
    {
        Show_Mode = 0;
        Show_Data_Mode = 0;
        Len_Parm = Len_Parm_Buf;
        Read_Timer_Parm = Read_Timer_Parm_Buf;
    }
}

void DataParmShowModeChange()
{
    if(Show_Mode == 0)
    {
        Show_Data_Mode++;
        if(Show_Data_Mode > 2)
        {
            Show_Data_Mode = 0;
        }
        else if(Show_Data_Mode == 2)
        {
            Data_Save_Mode = 0;
        }
    }
    else if(Show_Mode == 1)
    {
        if(Show_Parm_Mode == 0)
        {
            Show_Parm_Mode = 1;
        }
        else
        {
            Show_Parm_Mode = 0;
        }
    }    
}


void SonicDataReadAndSaveModeChange()
{
    if(Show_Data_Mode == 1)
    {
        if(Read_Lens_Mode == 0)
        {
            Read_Lens_Mode = 1;
        }
        else
        {
            Read_Lens_Mode = 0;
            flag_First_Read = 0;
        }        
    }
    else if(Show_Data_Mode == 2)
    {
        Data_Save_Mode++;
        if(Data_Save_Mode > 2)
        {
            Data_Save_Mode = 0;
        }        
    }
}

void ParmDataChangeAndSave()
{
    static unsigned i = 0;
    unsigned char pdata Read_Timer_Parm_Buff[5] = {2,3,5,7,9};
    if(Show_Parm_Mode == 0)
    {
        i++;
        if(i>4)
        {
            i = 0;
        }
        Read_Timer_Parm_Buf = Read_Timer_Parm_Buff[i];
    }
    else if(Show_Parm_Mode == 1)
    {
        Len_Parm_Buf += 10;
        if(Len_Parm_Buf > 80)
        {
            Len_Parm_Buf = 10;
        }
    }
}



