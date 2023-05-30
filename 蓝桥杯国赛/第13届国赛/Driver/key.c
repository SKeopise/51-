
#include "key.h"




unsigned char Key_Map[4] = {'7','6','5','4'};


unsigned char Key_Sta[4] = {1,1,1,1};


unsigned char Menu_Mode = 0;
unsigned char Menu_Parm = 0;

unsigned int Parm_Freq = 9000;
unsigned int Parm_Freq_Buf = 9000;

unsigned char Parm_RH = 40;
unsigned char Parm_RH_Buf = 40;

unsigned char Parm_Distence = 60;
unsigned char Parm_Distence_Buf = 60;

bit freq_mode = 0;
bit distence_mode = 0;

bit flag_S7_LongSet = 0;

void KeyAction0(unsigned char keycode)
{
	if(keycode == '4')
	{
		MenuSelectModeS4();
	}
	else if(keycode == '5')
	{
		ParmSelectModeS5();
	}
	else if(keycode == '6')
	{
		ParmDataIncS6();
	}
	else if(keycode == '7')
	{
		ParmDataDecS7();
		if(Menu_Mode == 1)
		{
			flag_S7_LongSet = 1;
		}
	}
}

void KeyAction1(unsigned char keycode)
{
	if(keycode == '7')
	{
		if(flag_S7_LongSet == 1)
		{
			flag_S7_LongSet = 0;
			if(flag_Clear_RelayCnt == 1)
			{
				flag_Clear_RelayCnt = 0;
				Relay_Cnt = 0;
				DataWriteEEPROM(0x00,Relay_Cnt);
			}
		}
	}
}

void ParmDataDecS7()
{
	if(Menu_Mode == 3)
	{
		if(Menu_Parm == 0)
		{
			Parm_Freq_Buf -= 500;
			if(Parm_Freq_Buf < 1000)
			{
				Parm_Freq_Buf = 12000;
			}
		}
		else if(Menu_Parm == 1)
		{
			Parm_RH_Buf -= 10;
			if(Parm_RH_Buf < 10)
			{
				Parm_RH_Buf = 60;
			}		
		}
		else if(Menu_Parm == 2)
		{
			Parm_Distence_Buf -= 10;
			if(Parm_Distence_Buf < 10)
			{
				Parm_Distence_Buf = 120;
			}
		}
	}
	else if(Menu_Mode == 0)
	{
		freq_mode = ~freq_mode;
	}
}

void ParmDataIncS6()
{
	if(Menu_Mode == 3)
	{
		if(Menu_Parm == 0)
		{
			Parm_Freq_Buf += 500;
			if(Parm_Freq_Buf > 12000)
			{
				Parm_Freq_Buf = 1000;
			}
		}
		else if(Menu_Parm == 1)
		{
			Parm_RH_Buf += 10;
			if(Parm_RH_Buf > 60)
			{
				Parm_RH_Buf = 10;
			}
		}
		else if(Menu_Parm == 2)
		{
			Parm_Distence_Buf += 10;
			if(Parm_Distence_Buf > 120)
			{
				Parm_Distence_Buf = 10;
			}
		}
	}
	else if(Menu_Mode == 2)
	{
		distence_mode = ~distence_mode;
	}
}

void ParmSelectModeS5()
{
	if(Menu_Mode == 3)
	{
		Menu_Parm++;
		if(Menu_Parm > 2)
		{
			Menu_Parm = 0;
		}
	}
}

void MenuSelectModeS4()
{
	Menu_Mode++;
	if(Menu_Mode > 3)
	{
		Menu_Mode = 0;
		Menu_Parm = 0;
		Parm_Freq = Parm_Freq_Buf;
		Parm_RH = Parm_RH_Buf;
		Parm_Distence = Parm_Distence_Buf;
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













