
#include "key.h"


unsigned char code Key_Map[4][4] = {
	{'0','1','2','3'},
	{'4','5','6','7'},
	{'8','9','S','R'},
	{'#','*','Y','B'}
};

unsigned char Key_Sta[4][4] = {
	{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
};

unsigned char Number_Code = 0; 		//输入密码时的位数缓存
unsigned char Password_Mode = 0;   //当前输入密码的状态，0为输入密码解锁，1为设置界面的输入旧密码，2为输入新密码
unsigned char Error_Cnt = 0;       //密码输入错误的次数
bit Password_Right = 0;        	  //判断密码是否正确
bit Password_Over = 0;             //判断当前密码输入是否完成


void KeyAction0(unsigned char keycode)
{	
	if(keycode == 'Y')
	{
		if(Door_Mod == 1)
		{
			PasswordKeyMode();
		}
	}
	else if(keycode == 'S')
	{
		if(Door_Mod == 1)
		{
			if(Password_Mode == 0)
			{
				Password_Right = 0;
				Password_Mode = 1;
				PasswordBuffReset();
			}
		}
	}
	else if(keycode == 'R')
	{
		PasswordReset();
	}
	else if(keycode == 'B')
	{
		if(Door_Mod == 1)
		{
			Password_Mode = 0;
			PasswordBuffReset();
		}		
	}
	else
	{
		if(Door_Mod == 1)
		{
			if(Number_Code <= 5)
			{
				PassWordBuff[Number_Code++] = keycode - 0x30;
			}
			else
			{
				Password_Over = 1;
			}			
		}
	}	
}

void KeyAction1(unsigned char keycode)
{
	if(keycode == '1')
	{
		
	}
	
}

void PasswordKeyMode()
{
	PasswordOver();
	if(Password_Mode == 0)
	{
		PasswordCmd();
		if(Password_Right == 1)
		{
			Door_Open = 1;
			PasswordBuffReset();
		}
	}
	else if(Password_Mode == 1)
	{
		PasswordCmd();
		if(Password_Right == 1)
		{
			Password_Mode = 2;
			PasswordBuffReset();
			Password_Right = 1;
		}
	}
	else if(Password_Mode == 2)
	{
		if(Password_Over == 1)
		{
			PasswordSet();
			Password_Mode = 0;
		}
	}	
}

void KeyDriver()
{
	unsigned char i,j;
	static unsigned char backup[4][4] = {
		{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
	};
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(backup[i][j] != Key_Sta[i][j])
			{
				if(backup[i][j] != 0)
				{
					KeyAction0(Key_Map[i][j]);
				}
				else
				{
					KeyAction1(Key_Map[i][j]);
				}
				backup[i][j] = Key_Sta[i][j];
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
	
	Key_Buff[Key_Out][0] = Key_Buff[Key_Out][0] << 1 | KEY_IN_0;
	Key_Buff[Key_Out][1] = Key_Buff[Key_Out][1] << 1 | KEY_IN_1;
	Key_Buff[Key_Out][2] = Key_Buff[Key_Out][2] << 1 | KEY_IN_2;
	Key_Buff[Key_Out][3] = Key_Buff[Key_Out][3] << 1 | KEY_IN_3;
	
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
	if(Key_Out >= 4)
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

	








