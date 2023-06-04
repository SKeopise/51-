#include "key.h"



unsigned char Key_Map[4] = {'7','6','5','4'};

unsigned char Key_Sta[4] = {1,1,1,1};


unsigned char MenuMode_Data = 0;
unsigned char MenuMode_Backup = 0;

unsigned char MenuMode_Main = 0;

bit flag_StartKey6 = 0;
unsigned int Key6_SetTime = 0;


unsigned char ADC_Data_EEPROM = 0;
unsigned int Temp_Data_EEPROM = 0;
unsigned int Freq_Data_EEPROM = 0;

unsigned char Parm_ADC = 10;
unsigned char Parm_ADC_Buf = 10;


void KeyAction0(unsigned char keycode)
{
	if(keycode == '7')
	{
		MenuParmSetS7();
	}
	else if(keycode == '6')
	{
		MenuBackupDataS6();
	}
	else if(keycode == '5')
	{
		SaveDataS5();
	}
	else if(keycode == '4')
	{
		MenuModeSelectS4();
	}	
}

void KeyAction1(unsigned char keycode)
{
	if(keycode == '6')
	{
		if(flag_StartKey6 == 1)
		{
			flag_StartKey6 = 0;
			if(Key6_SetTime < 800)
			{
				if(Parm_ADC_Buf < 50)
				{
					Parm_ADC_Buf++;
				}
				else
				{
					Parm_ADC_Buf = 10;
				}
			}
			Key6_SetTime = 0;
		}
	}
}


void SaveDataS5()
{
	ADC_Data_EEPROM = ADC_Data;
	Temp_Data_EEPROM = Temp_Data;
	Freq_Data_EEPROM = Freq_Data;
	EEPROM_WriteData(ADC_DATA_ADDR,ADC_Data_EEPROM);
	EEPROM_WriteDataUint(TEMP_DATA_ADDR_HIGH,TEMP_DATA_ADDR_LOW,Temp_Data_EEPROM);
	EEPROM_WriteDataUint(FREQ_DATA_ADDR_HIGH,FREQ_DATA_ADDR_LOW,Freq_Data_EEPROM);	
}

void MenuParmSetS7()
{
	if(MenuMode_Main != 2)
	{
		MenuMode_Main = 2;
		MenuMode_Data = 0;
		MenuMode_Backup = 0;
	}
	else
	{
		MenuMode_Main = 0;
		Parm_ADC = Parm_ADC_Buf;
	}
}


void MenuBackupDataS6()
{
	if(MenuMode_Main == 0)
	{
		MenuMode_Main = 1;
		MenuMode_Data = 0;
		MenuMode_Backup = 0;		
	}
	else if(MenuMode_Main == 1)
	{
		MenuMode_Main = 0;
	}
	else
	{
		flag_StartKey6 = 1;
	}
}

void MenuModeSelectS4()
{
	if(MenuMode_Main == 0)
	{
		MenuMode_Data++;
		if(MenuMode_Data > 2)
		{
			MenuMode_Data = 0;
		}
	}
	else if(MenuMode_Main == 1)
	{
		MenuMode_Backup++;
		if(MenuMode_Backup > 2)
		{
			MenuMode_Backup = 0;
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










