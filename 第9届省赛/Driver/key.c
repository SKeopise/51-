#include "key.h"



unsigned char code Key_Map[4] = {'7','6','5','4'};

unsigned char Key_Sta[4] = {1,1,1,1};

unsigned int Led_Timer_Buff = 400;

unsigned int Led_Timer_Buff_Mode[4] = {400,400,400,400};

unsigned char Led_Running_Mode_Buff = 1;

bit Led_Running_Open = 1;

bit Pwm_Mode_Show = 0;



void KeyAction0(unsigned char keycode)
{

	if(keycode == '7')
	{
		if(Led_Running_Open == 1)
		{
			Led_Running_Open = 0;
		}
		else 
		{
			Led_Running_Open = 1;
		}
	}
	else if(keycode == '6')
	{
		Smg_Mode++;
		if(Smg_Mode >= 3)
		{
			Smg_Mode = 0;
			switch(Led_Running_Mode_Buff)
			{
				case 1: Led_Timer_Buff_Mode[0] = Led_Timer_Buff; LedTimerDataWrite(1); break;
				case 2: Led_Timer_Buff_Mode[1] = Led_Timer_Buff; LedTimerDataWrite(2); break;
				case 3: Led_Timer_Buff_Mode[2] = Led_Timer_Buff; LedTimerDataWrite(3); break;
				case 4: Led_Timer_Buff_Mode[3] = Led_Timer_Buff; LedTimerDataWrite(4); break;
				default: break;
			}
			Led_Running_Mode_Buff = 1;
		}
		if(Smg_Mode == 1)
		{
			Led_Timer_Buff = Led_Timer_Buff_Mode[0];
			Led_Running_Mode_Buff = 1;
		}
		switch(Led_Running_Mode_Buff)
		{
			case 1: Led_Timer_Buff = Led_Timer_Buff_Mode[0]; break;
			case 2: Led_Timer_Buff = Led_Timer_Buff_Mode[1]; break;
			case 3: Led_Timer_Buff = Led_Timer_Buff_Mode[2]; break;
			case 4: Led_Timer_Buff = Led_Timer_Buff_Mode[3]; break;
			default: break;		
		}		
	}
	else if(keycode == '5')
	{
		if(Smg_Mode == 1)
		{
			Led_Running_Mode_Buff++;
			if(Led_Running_Mode_Buff > 4)
			{
				Led_Running_Mode_Buff = 1;
			}
			switch(Led_Running_Mode_Buff)
			{
				case 1: Led_Timer_Buff = Led_Timer_Buff_Mode[0]; break;
				case 2: Led_Timer_Buff = Led_Timer_Buff_Mode[1]; break;
				case 3: Led_Timer_Buff = Led_Timer_Buff_Mode[2]; break;
				case 4: Led_Timer_Buff = Led_Timer_Buff_Mode[3]; break;
				default: break;		
			}				
		}
		else if(Smg_Mode == 2)
		{
			Led_Timer_Buff += 100;
			if(Led_Timer_Buff > 1200)
			{
				Led_Timer_Buff = 1200;
			}
		}
	}
	else if(keycode == '4')
	{
		if(Smg_Mode == 1)
		{
			Led_Running_Mode_Buff--;
			if(Led_Running_Mode_Buff < 1)
			{
				Led_Running_Mode_Buff = 4;
			}
			switch(Led_Running_Mode_Buff)
			{
				case 1: Led_Timer_Buff = Led_Timer_Buff_Mode[0]; break;
				case 2: Led_Timer_Buff = Led_Timer_Buff_Mode[1]; break;
				case 3: Led_Timer_Buff = Led_Timer_Buff_Mode[2]; break;
				case 4: Led_Timer_Buff = Led_Timer_Buff_Mode[3]; break;
				default: break;		
			}				
		}
		else if(Smg_Mode == 2)
		{
			Led_Timer_Buff -= 100;
			if(Led_Timer_Buff < 400)
			{
				Led_Timer_Buff = 400;
			}			
		}
		else
		{
			if(Pwm_Mode_Show == 0)
			{
				Pwm_Mode_Show = 1;
			}
			else
			{
				Pwm_Mode_Show = 0;
			}
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
			if(Key_Backup[i] != 0)
			{
				KeyAction0(Key_Map[i]);
			}
			else
			{
			
			}
			Key_Backup[i] = Key_Sta[i];
		}
	}
}

void KeyScan()
{
	static unsigned char Key_Out = 0;
	static unsigned char Key_Buff[] = {0xFF,0xFF,0xFF,0xFF};
	
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
	if(Key_Out > 3)
	{
		Key_Out = 0;
	}
}













