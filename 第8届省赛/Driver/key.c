
#include "key.h"



unsigned char code Key_Map[4][4] = {
	{'7','0','0','0'},
	{'6','0','0','0'},
	{'5','0','0','0'},
	{'4','0','0','0'},	
};

unsigned char Key_Sta[4][4] = {
	{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
};




unsigned char Clock_Data_Set = 0;
unsigned char Clock_Warring_Time_Set = 0;

unsigned char Timer_Warring[3] = {0,0,0};

bit Temp_Show = 0;







void KeyAction0(unsigned char keycode)
{
	if(keycode == '7')
	{
		DataSetSwitch();
	}
	else if(keycode == '6')
	{
		WarringTimeSetSwitch();
	}
	else if(keycode == '5')
	{
		DataChange(0);
	}
	else if(keycode == '4')
	{
		DataChange(1);
		if((Clock_Data_Set == 0) && (Clock_Warring_Time_Set == 0)) //显示温度
		{
			Temp_Show = 1;
		}
	}	
	if(Flag_Warring_Clock == 1)
	{
		Flag_Warring_Clock = 0;
	}
}

void KeyAction1(unsigned char keycode)
{
	if(keycode == '4')
	{
		Temp_Show = 0;
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
			if(Key_Backup[i][j] != Key_Sta[i][j])
			{
				if(Key_Backup[i][j] != 0)
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
	unsigned char i =0;
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




void TimerWarringTimeChange(unsigned char i,unsigned char j)
{
	if(j == 0)
	{
		Timer_Warring[i]++;
	}
	else if(j == 1)
	{
		if(Timer_Warring[i] > 0)
		{
			Timer_Warring[i]--;
		}
		else
		{
			if(i == 2)
			{
				Timer_Warring[i] = 23;
			}
			else 
			{
				Timer_Warring[i] = 59;
			}
		}
	}
	if(i == 2)
	{
		if(Timer_Warring[i] > 23)
		{
			Timer_Warring[i] = 0;
		}
	}
	else
	{
		if(Timer_Warring[i] > 59)
		{
			Timer_Warring[i] = 0;
		}		
	}
}





void TimerDataChange(unsigned char i,unsigned char j)
{
	TimerData[i] = (TimerData[i]>>4)*10+(TimerData[i]&0x0F);
	if(j == 0)
	{
		TimerData[i]++;
	}
	else
	{
		if(TimerData[i] > 0)
		{
			TimerData[i]--;
		}
		else
		{
			if(i == 2)
			{
				TimerData[i] = 23;
			}
			else 
			{
				TimerData[i] = 59;
			}
		}
	}
	if(i == 2)
	{
		if(TimerData[i] > 23)
		{
			TimerData[i] = 0;
		}
	}
	else
	{
		if(TimerData[i] > 59)
		{
			TimerData[i] = 0;
		}		
	}
	TimerData[i] = (((TimerData[i]/10)%10)<<4) | ((TimerData[i]%10)&0x0F);	
	Write_Ds1302_Byte(DS1302_Write_Addr[2],TimerData[2]);
	Write_Ds1302_Byte(DS1302_Write_Addr[1],TimerData[1]);
	Write_Ds1302_Byte(DS1302_Write_Addr[0],TimerData[0]);
}	



void DataChange(bit i)
{
	switch(Clock_Data_Set)
	{
		case 1: TimerDataChange(2,i); break;
		case 2: TimerDataChange(1,i); break;
		case 3: TimerDataChange(0,i); break;	
		default: break;
	}
	switch(Clock_Warring_Time_Set)
	{
		case 1: TimerWarringTimeChange(2,i); break;
		case 2: TimerWarringTimeChange(1,i); break;
		case 3: TimerWarringTimeChange(0,i); break;
		default: break;
	}	
}


void DataSetSwitch()
{
	if(Clock_Warring_Time_Set == 0)
	{
		if(Clock_Data_Set == 0)
		{
			DS1302Stop();
		}
		Clock_Data_Set++;
		if(Clock_Data_Set > 3)
		{
			Clock_Data_Set = 0;
			DS1302Start();
		}
	}	
}

void WarringTimeSetSwitch()
{
	if(Clock_Data_Set == 0)
	{
		if(Clock_Warring_Time_Set == 0)
		{
			DS1302Stop();
		}
		Clock_Warring_Time_Set++;
		if(Clock_Warring_Time_Set > 3)
		{
			Clock_Warring_Time_Set = 0;
			DS1302Start();
		}
	}
}



