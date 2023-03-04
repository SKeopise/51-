#include "key.h"
#include "led.h"


unsigned char code Key_Map[4][4] = {        //按键扫描键码表
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'*','0','#','D'}
};

unsigned char Key_Sta[4][4] = {                //按键状态
	{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},
};

extern unsigned int keyflag;


void Key_Action_bkp1(unsigned char keycode)   //当按键按下时执行动作
{
	if(keycode == '#')
	{
		keyflag++;
		if(keyflag >= 3)
		{
			keyflag = 0;
		}
	}
	else if(keycode == '9')
	{
		if(workmode == 0)
		{
			Relay(0);
			workmode = 1;
		}
		else
		{
			workmode = 0;
		}
	}
	else if(keycode == 'D')
	{
		if(keyflag == 2)
		{
			Tparm++;
		}
	}
	else if(keycode == 'C')
	{
		if(keyflag == 2)
		{
			Tparm--;
		}
		else if(keyflag == 1)
		{
			TimeMod = 1;
		}
		
	}
	
}

void Key_Action_bkp2(unsigned char keycode)     //当按键抬起时执行动作
{
	if(keycode == 'C')
	{
		if(keyflag == 1)
		{
			TimeMod = 0;
		}
		
	}	
}


void Key_Driver()                    
{
	static unsigned char i,j;
	static unsigned char backup[4][4] = {          //前一次按键状态的缓存
		{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},
	};
	
	for(i = 0;i < 4;i++)
	{
		for(j = 0;j < 4;j++)
		{
			if(backup[i][j] != Key_Sta[i][j])
			{	//如果按键状态与之前缓存区不同，则说明发生了动作
				if(backup[i][j] != 0)
				{	//按键按下执行
					Key_Action_bkp1(Key_Map[i][j]);
				}
				else
				{	//按键松开执行
					Key_Action_bkp2(Key_Map[i][j]);
				}
				backup[i][j] = Key_Sta[i][j];
			}
		}
	}

}

void Key_Scan()
{
	unsigned char i;
	static unsigned char keyout = 0;
	static unsigned char Key_Buf[4][4] = {
		{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
		{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
	}; 
	
	Key_Buf[keyout][0] = (Key_Buf[keyout][0] << 1) | KEY_IN_0;
	Key_Buf[keyout][1] = (Key_Buf[keyout][1] << 1) | KEY_IN_1;
	Key_Buf[keyout][2] = (Key_Buf[keyout][2] << 1) | KEY_IN_2;
	Key_Buf[keyout][3] = (Key_Buf[keyout][3] << 1) | KEY_IN_3;
	
	for(i=0;i<4;i++)
	{
		if((Key_Buf[keyout][i] & 0x0F) == 0x00)
		{
			Key_Sta[keyout][i] = 0;
		}
		else if((Key_Buf[keyout][i] & 0x0F) == 0x0F)
		{
			Key_Sta[keyout][i] = 1;
		}
	}
	
	keyout++;
	keyout = keyout & 0x03;
	switch(keyout)
	{
		case 0: KEY_OUT_3 = 1; KEY_OUT_0 = 0;break;
		case 1: KEY_OUT_0 = 1; KEY_OUT_1 = 0;break;
		case 2: KEY_OUT_1 = 1; KEY_OUT_2 = 0;break;
		case 3: KEY_OUT_2 = 1; KEY_OUT_3 = 0;break;
		default: break;
	}
	
	
}














