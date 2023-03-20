#include "key.h"



unsigned char code Key_Map[4] = {'7','6','5','4'};

unsigned char Key_Sta[4] = {1,1,1,1};



bit DAC_Mode = 0;
bit Show_Mode = 0;
bit Smg_Open = 1;
bit Led_Open = 1;

void KeyAction0(unsigned char keycode)
{
	if(keycode == '4')
	{
		if(Show_Mode == 0)
		{
			Show_Mode = 1;
		}
		else
		{
			Show_Mode = 0;
		}
	}
	else if(keycode == '5')
	{
		if(DAC_Mode == 0)
		{
			DAC_Mode = 1;
		}
		else
		{
			DAC_Mode = 0;
		}	
	}
	else if(keycode == '6')
	{
		if(Led_Open == 0)
		{
			Led_Open = 1;
		}
		else
		{
			Led_Open = 0;
		}		
	}
	else if(keycode == '7')
	{
		if(Smg_Open == 0)
		{
			Smg_Open = 1;
		}
		else
		{
			Smg_Open = 0;
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
	unsigned char i = 0;
	static unsigned char Key_Out = 0;
	static unsigned char Key_Buf[4] = {0xFF,0xFF,0xFF,0xFF};
	
	switch(Key_Out)
	{
		case 0: Key_Buf[0] = (Key_Buf[0] << 1) | KEY_OUT_0; break;
		case 1: Key_Buf[1] = (Key_Buf[1] << 1) | KEY_OUT_1; break;
		case 2: Key_Buf[2] = (Key_Buf[2] << 1) | KEY_OUT_2; break;
		case 3: Key_Buf[3] = (Key_Buf[3] << 1) | KEY_OUT_3; break;
		default: break;
	}
	
	for(i=0;i<4;i++)
	{
		if((Key_Buf[i]&0x0F) == 0x00)
		{
			Key_Sta[i] = 0;
		}
		else if((Key_Buf[i]&0x0F) == 0x0F)
		{
			Key_Sta[i] = 1;
		}
	}
	
	Key_Out++;
	if(Key_Out > 3)
	{
		Key_Out = 0;
	}
}














