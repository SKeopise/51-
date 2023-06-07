#include "key.h"




unsigned char code Key_Map[4] = {'7','6','5','4'};


unsigned char Key_Sta[4] = {1,1,1,1};


unsigned char Distence_Cnt = 0;

unsigned char Menu_Mode = 0;

bit flag_DataShowMode = 0;
unsigned char DataBackup_Cnt = 1;

unsigned char Parm_Distence = 20;
unsigned char Parm_Distence_Buf = 20;

unsigned int Distence_LastIncNow = 0;



void KeyAction0(unsigned char keycode)
{
	if(keycode == '4')
	{
		DistenceRead_Start();
		flag_Led1 = 1;
		flag_LedFlash = 0;
		Led_FlashCnt = 0;
	}
	else if(keycode == '5')
	{
		if(Menu_Mode == 0)
		{
			Menu_Mode = 1;
			flag_DataShowMode = 0;
		}
		else if(Menu_Mode == 1)
		{
			Menu_Mode = 0;
			DataBackup_Cnt = 1;
		}
	}
	else if(keycode == '6')
	{
		if(Menu_Mode != 2)
		{
			Menu_Mode = 2;
			DataBackup_Cnt = 1;	
			flag_DataShowMode = 0;	
			Parm_Distence_Buf = Parm_Distence;
		}
		else
		{
			Menu_Mode = 0;
			Parm_Distence = Parm_Distence_Buf;
			EEPROM_WriteByte(PARM_ADDR,Parm_Distence);
		}
	}
	else if(keycode == '7')
	{
		if(Menu_Mode == 0)
		{
			flag_DataShowMode = ~flag_DataShowMode;
		}
		else if(Menu_Mode == 1)
		{
			DataBackup_Cnt++;
			if(DataBackup_Cnt > 10)
			{
				DataBackup_Cnt = 1;
			}
		}
		else if(Menu_Mode == 2)
		{
			Parm_Distence_Buf += 10;
			if(Parm_Distence_Buf > 90)
			{
				Parm_Distence_Buf = 0;
			}
		}
	}

}

void KeyAction1(unsigned char keycode)
{
	if(keycode == '4')
	{
		ClearEEPROM();
		ReadHistoryData();
	}

}


void DistenceRead_Start()
{	
//	unsigned char Addr_Buf = 0;
	
	Sonic_DistenceRead();
	Sonic_HistoryData[Distence_Cnt] = Sonic_Distence;		
	
	if(Distence_Cnt != 0)
	{
		Distence_LastIncNow = Sonic_Distence + Sonic_HistoryData[Distence_Cnt - 1];
	}
	else
	{
		Distence_LastIncNow = Sonic_Distence + Sonic_HistoryData[9];
	}
	
	Distence_Cnt++;
	if(Distence_Cnt >= 10)
	{
		Distence_Cnt = 0;
	}
	EEPROM_WriteByte(DISTENCE_CNT_ADDR,Distence_Cnt);
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











