#include "key.h"


unsigned char code Key_Map[4][4] = {
	{'0','0','0','0'},
	{'0','0','0','0'},
	{'5','9','0','0'},
	{'4','8','0','0'},
};

unsigned char Key_Sta[4][4] = {
	{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
};


unsigned char Parm_Buff = 0;
unsigned char Timer_Parm_Buff = 17;
unsigned int Temp_Parm_Buff = 25;
unsigned char Led_Parm_Buff = 4;

bit Parm_Change = 0;



void KeyActionShort0(unsigned char keycode)
{
	if(keycode == '4')
	{
		if(Smg_Show_Mode == 0)
		{
			Smg_Show_Mode = 1;
			Smg_Parm_Mode = 0;
			
			Timer_Parm_Buff = Timer_Parm;
			Temp_Parm_Buff = Temp_Parm;
			Led_Parm_Buff = Led_Parm;
			Parm_Buff = Timer_Parm_Buff;
		}
		else
		{
			Smg_Show_Mode = 0;
			Smg_Data_Mode = 0;
			Timer_Parm = Timer_Parm_Buff;
			Temp_Parm = Temp_Parm_Buff;
			Led_Parm = Led_Parm_Buff;
		}
	}
	else if(keycode == '5')
	{
		if(Smg_Show_Mode == 0)
		{
			
			Smg_Data_Mode++;
			if(Smg_Data_Mode >= 3)
			{
				Smg_Data_Mode = 0;
			}
			
		}
		else
		{
			if(Smg_Parm_Mode == 0)
			{
				if(Parm_Change == 1)
				{
					Timer_Parm_Buff = Parm_Buff;
					Parm_Change = 0;
					Parm_Buff = Temp_Parm_Buff;
				}
				else
				{
					Parm_Buff = Temp_Parm_Buff;
				}
			}
			else if(Smg_Parm_Mode == 1)
			{
				if(Parm_Change == 1)
				{
					Temp_Parm_Buff = Parm_Buff;
					Parm_Change = 0;
					Parm_Buff = Led_Parm_Buff;
				}
				else
				{
					Parm_Buff = Led_Parm_Buff;
				}				
			}
			else if(Smg_Parm_Mode == 2)
			{
				if(Parm_Change == 1)
				{
					Led_Parm_Buff = Parm_Buff;
					Parm_Change = 0;
					Parm_Buff = Timer_Parm_Buff;
				}
				else
				{
					Parm_Buff = Timer_Parm_Buff;
				}				
			}			
			Smg_Parm_Mode++;
			if(Smg_Parm_Mode >= 3)
			{
				Smg_Parm_Mode = 0;
			}
		}
	}
	else if(keycode == '8')
	{
		if(Smg_Show_Mode == 1)
		{
			Parm_Change = 1;
			if(Smg_Parm_Mode == 0)
			{
				if(Parm_Buff > 0)
				{
					Parm_Buff--;
					Timer_Parm_Buff = Parm_Buff;
				}
			}
			else if(Smg_Parm_Mode == 1)
			{
				if(Parm_Buff > 0)
				{
					Parm_Buff--;
					Temp_Parm_Buff = Parm_Buff;
				}
			}
			else if(Smg_Parm_Mode == 2)
			{
				if(Parm_Buff > 4)
				{
					Parm_Buff--;
					Led_Parm_Buff = Parm_Buff;
				}
			}
			
		}
	}
	else if(keycode == '9')
	{
		if(Smg_Show_Mode == 1)
		{
			Parm_Change = 1;
			if(Smg_Parm_Mode == 0)
			{
				if(Parm_Buff < 23)
				{
					Parm_Buff++;
					Timer_Parm_Buff = Parm_Buff;
				}
			}
			else if(Smg_Parm_Mode == 1)
			{
				if(Parm_Buff < 99)
				{
					Parm_Buff++;
					Temp_Parm_Buff = Parm_Buff;
				}				
			}
			else
			{
				if(Parm_Buff < 8)
				{
					Parm_Buff++;
					Led_Parm_Buff = Parm_Buff;
				}					
			}
		}	
	}
	

}


void KeyDriver()
{
	unsigned char i,j;
	static unsigned char Key_Backup[4][4] = {
		{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
	}; 

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(Key_Backup[i][j] != Key_Sta[i][j])     //有动作
			{
				if(Key_Backup[i][j] == 1)      //按下
				{
					KeyActionShort0(Key_Map[i][j]);
				}
				else                           //抬起
				{
					
				}
				Key_Backup[i][j] = Key_Sta[i][j];
			}
			else        //无动作
			{
				if(Key_Backup[i][j] == 0)     //长按
				{
					
				}
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
		if((Key_Buff[Key_Out][i] & 0x0F) == 0X00)
		{
			Key_Sta[Key_Out][i] = 0;
		}
		else if((Key_Buff[Key_Out][i] & 0x0F) == 0X0F)
		{
			Key_Sta[Key_Out][i] = 1;
		}
	}
	
	Key_Out++;
	if(Key_Out > 3)
	{
		Key_Out = 0;
	}
	
	switch(Key_Out)
	{
		case 0: KEY_OUT_0 = 0; KEY_OUT_3 = 1; break;
		case 1: KEY_OUT_1 = 0; KEY_OUT_0 = 1; break;
		case 2: KEY_OUT_2 = 0; KEY_OUT_1 = 1; break;
		case 3: KEY_OUT_3 = 0; KEY_OUT_2 = 1; break;
		default: break;
	}	
}













