
#include "key.h"




unsigned char Key_Map[4] = {'7','6','5','4'};


unsigned char Key_Sta[4] = {1,1,1,1};




void KeyAction0(unsigned char keycode)
{
	if(keycode == '4')
	{

	}
}

void KeyAction1(unsigned char keycode)
{
	if(keycode == '4')
	{
		
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
			else
			{
				KeyAction1(Key_Map[i]);
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
	
	if((Key_Buff[Key_Out] & 0x0F) == 0x00)
	{
		Key_Sta[Key_Out] = 0;
	}
	else if((Key_Buff[Key_Out] & 0x0F) == 0x0F)
	{
		Key_Sta[Key_Out] = 1;
	}
	
	Key_Out++;
	Key_Out &= 0x03;
}













