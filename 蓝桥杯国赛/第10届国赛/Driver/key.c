
#include "key.h"



unsigned char code Key_Map[2][2] = {
	{'3','7'},
	{'2','6'}
};


unsigned char Key_Sta[2][2] = {
	{1,1},{1,1}
};


bit Menu_Mode = 0;

unsigned char Menu_Data = 0;

bit Menu_Parm = 0;


bit flag_Key_Set = 0;

unsigned int Parm_ChangCnt = 0;

unsigned int ParmData_Temp = 3000;
unsigned int ParmData_Temp_Buf = 3000;

unsigned char ParmData_Distence = 35;
unsigned char ParmData_Distence_Buf = 35;



void KeyAction0(unsigned char keycode)
{
	if(keycode == '3')
	{
		flag_Key_Set = 1;
	}
	else if(keycode == '2')
	{
		flag_Key_Set = 1;		
	}
	else if(keycode == '6')
	{
		if(Menu_Mode == 1)
		{
			if(Menu_Parm == 0)
			{
				if(ParmData_Temp_Buf > 200)
				{
					ParmData_Temp_Buf -= 200;
				}
				else
				{
					ParmData_Temp_Buf = 0;
				}
			}
			else
			{
				if(ParmData_Distence_Buf > 5)
				{
					ParmData_Distence_Buf -= 5;
				}
				else
				{
					ParmData_Distence_Buf = 0;
				}
			}
		}
	}
	else if(keycode == '7')
	{
		if(Menu_Mode == 1)
		{
			if(Menu_Parm == 0)
			{
				ParmData_Temp_Buf += 200;
				if(ParmData_Temp_Buf > 9900)
				{
					ParmData_Temp_Buf = 9900;
				}
			}
			else
			{
				ParmData_Distence_Buf += 5;
				if(ParmData_Distence_Buf > 99)
				{
					ParmData_Distence_Buf = 99;
				}
			}
		}				
	}	
}


void KeyAction1(unsigned char keycode)
{
	if(keycode == '3')
	{
		flag_Key_Set = 0;
		if(Key_SetTime < 1000)
		{
			if(Menu_Mode == 1)
			{
				if((ParmData_Temp_Buf != ParmData_Temp) || (ParmData_Distence_Buf != ParmData_Distence))
				{
					Parm_ChangCnt++;
					EEPROM_WriteUnsignedInt(PARM_CNT_ADDR_HIGH,PARM_CNT_ADDR_LOW,&Parm_ChangCnt);					
				}
				ParmData_Temp = ParmData_Temp_Buf;
				ParmData_Distence = ParmData_Distence_Buf;
			}
			Menu_Mode = ~Menu_Mode;
			Menu_Data = 0;
			Menu_Parm = 0;
		}
		else
		{
			DAC_Mode = ~DAC_Mode;
		}
		Key_SetTime = 0;
	}
	else if(keycode == '2')
	{
		flag_Key_Set = 0;
		if(Key_SetTime < 1000)
		{
			if(Menu_Mode == 0)
			{
				Menu_Data++;
				if(Menu_Data > 2)
				{
					Menu_Data = 0;
				}
			}
			else
			{
				Menu_Parm = ~Menu_Parm;
			}
		}
		else
		{
			Parm_ChangCnt = 0;
			EEPROM_WriteUnsignedInt(PARM_CNT_ADDR_HIGH,PARM_CNT_ADDR_LOW,&Parm_ChangCnt);					
		}
		Key_SetTime = 0;		
	}

	
}

void KeyDriver()
{
	unsigned char i,j;
	static unsigned char Key_Backup[2][2] = {
		{1,1},{1,1}
	};
	
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			if(Key_Backup[i][j] != Key_Sta[i][j])
			{
				if(Key_Backup[i][j] == 1)
				{
					KeyAction0(Key_Map[i][j]);
				}
				else
				{
					KeyAction1(Key_Map[i][j]);
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
	static unsigned char Key_Buff[2][2] = {
		{0xFF,0xFF},{0xFF,0xFF}
	};
	
	Key_Buff[Key_Out][0] = (Key_Buff[Key_Out][0] << 1) | KEY_IN_2;
	Key_Buff[Key_Out][1] = (Key_Buff[Key_Out][1] << 1) | KEY_IN_3;

	for(i=0;i<2;i++)
	{
		if(Key_Buff[Key_Out][i] == 0x00)
		{
			Key_Sta[Key_Out][i] = 0;
		}
		else if(Key_Buff[Key_Out][i] == 0xFF)
		{
			Key_Sta[Key_Out][i] = 1;
		}
	}
	
	Key_Out++;
	Key_Out &= 0x01;
	
	switch(Key_Out)
	{
		case 0: KEY_OUT_2 = 0; KEY_OUT_3 = 1; break;
		case 1: KEY_OUT_3 = 0; KEY_OUT_2 = 1; break;
		default: break;
	}
	
}



