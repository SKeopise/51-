

#include "stc_key.h"
#include <stc_led.h>
#include <stc_BUZZ.h>
#include <stc_delay.h>


extern unsigned int code NoteFrequ[];

extern unsigned char currentKeyVal;

bit music = 0;

 unsigned char Led_ONF = 0;



unsigned char KeySta[4][4] = {
	{1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}
};


const unsigned char code KeyCodeMap[4][4] = {
	{0x31,0x32,0x33,0x26},
	{0x34,0x35,0x36,0x25},
	{0x37,0x38,0x39,0x28},
	{0x30,0x1B,0x0D,0x27}
};



 unsigned char Key_Mod = 0;  //键盘切换标志位

 extern unsigned char number_showlat;

extern unsigned char code LedChar[];


 bit SnakeGame = 0;     //贪吃蛇游戏开关控制标志位





void KeyAction(unsigned char keycode)     //按键动作函数，keycode为按键键码
{
	static double result = 0;
	static double addend = 0;
	unsigned int show_addend;
	
	if((keycode >= 0x30) && (keycode <= 0x39))
	{
		OpenBuzz(NoteFrequ[keycode-0x30]);
		delay_01(10);
		StopBuzz();
		
		addend = (addend*10)+(keycode-0x30);
		
		show_addend = addend;
		number_showlat = show_addend%10;

		if(Led_ONF == 2)
		{
			show_addend = 0;
		}
		
    ShowNumber(addend * 10);  //乘以10将小数点后一位转换为整数
	}
	else if(keycode == 0x26)    //按上键加法
	{
		OpenBuzz(2768);
		delay_01(10);
		StopBuzz();
		
		number_showlat = 10;
		
		result += addend;
		addend = 0;
		if(result >= -9999 && result <= 99999)
		{
		ShowNumber(result * 10);
		}
		else
		{
			show_error();
		}
	}
	else if(keycode == 0x28)    //按下键减法
	{
		OpenBuzz(1865);
		delay_01(10);
		StopBuzz();
		
		number_showlat = 11;	
		
		result -= addend;
		addend = 0;
		if(result >= -9999 && result <= 99999)
		{
		ShowNumber(result * 10);
		}
		else
		{
			show_error();
		}
	}
	else if(keycode == 0x25)    //按左键乘法
	{
		OpenBuzz(1760);
		delay_01(10);
		StopBuzz();
		
		number_showlat = 12;		
		
		result *= addend;
		addend = 0;
		if(result >= -9999 && result <= 99999)
		{
		ShowNumber(result * 10);
		}
		else
		{
			show_error();
		}
	}
	else if(keycode == 0x27)    //按右键除法
	{
		OpenBuzz(2093);
		delay_01(10);
		StopBuzz();
		
		number_showlat = 13;	
		
		result /= addend;
		addend = 0;
		if(result >= -9999 && result <= 99999)
		{
		ShowNumber(result * 10);
		}
		else
		{
			show_error();
		}
	}
	else if(keycode == 0x0D)    //回车键 切换键盘模式
	{
		OpenBuzz(2768);
		delay_01(10);
		StopBuzz();		
		
		Key_Mod = 1;
		
	}
	else if(keycode == 0x1B)    //Esc键清零
	{
		OpenBuzz(2349);
		delay_01(10);
		StopBuzz();		
		
		addend = 0;
		result = 0;
		ShowNumber(addend);
		
	  StopwatchReset();
	}
}



void KeyAction_01(unsigned char keycode01)       //切换键盘按键动作检测，按Esc复位回到计算器键盘
{
	if(keycode01 == 0x1B)    //Esc键清零
	{
		OpenBuzz(2349);
		delay_01(10);
		StopBuzz();		
		
		Key_Mod = 0;
		
	}
	else if(keycode01 == 0x30)    //数字0键 启停秒表
	{
		OpenBuzz(1026);
		delay_01(10);
		StopBuzz();		
		
    StopwatchAction();
		
	}
	else if(keycode01 == 0x31)     //数字键1，启动数码管显示
	{
		OpenBuzz(1145);
		delay_01(10);
		StopBuzz();	

		Led_ONF = 0;
	}
	else if(keycode01 == 0x32)       //数字键2，关闭数码管显示
	{
		OpenBuzz(1298);
		delay_01(10);
		StopBuzz();	

		Led_ONF = 1;
	}
	else if(keycode01 == 0x33)       //数字键3，启动点阵数码管同时显示
	{
		OpenBuzz(1387);
		delay_01(10);
		StopBuzz();	

		Led_ONF = 2;
	}
	else if(keycode01 == 0x34)       //按下数字键4,启动贪吃蛇游戏
	{
		OpenBuzz(1568);
		delay_01(10);
		StopBuzz();

		SnakeGame = 1;
	}
	else if(keycode01 == 0x35)       //按下数字键5,关闭贪吃蛇游戏
	{
		OpenBuzz(1760);
		delay_01(10);
		StopBuzz();

		SnakeGame = 0;
	}
	else if(keycode01 == 0x36)       //按下数字键6,开始贪吃蛇游戏
	{
		OpenBuzz(1976);
		delay_01(10);
		StopBuzz();

		currentKeyVal = 0x36;
	}	
	else if(keycode01 == 0x37)       //按下数字键7,退出贪吃蛇游戏
	{
		OpenBuzz(2093);
		delay_01(10);
		StopBuzz();

		currentKeyVal = 0x37;
	}	
	else if(keycode01 == 0x26)       //按下上方向键,贪吃蛇向上
	{
		OpenBuzz(2768);
		delay_01(10);
		StopBuzz();

		currentKeyVal = 0x26;
	}
	else if(keycode01 == 0x28)       //按下下方向键,贪吃蛇向下
	{
		OpenBuzz(1865);
		delay_01(10);
		StopBuzz();

		currentKeyVal = 0x28;
	}
	else if(keycode01 == 0x25)       //按下左方向键,贪吃蛇向左
	{
		OpenBuzz(1760);
		delay_01(10);
		StopBuzz();

		currentKeyVal = 0x25;
	}
	else if(keycode01 == 0x27)       //按下右方向键,贪吃蛇向右
	{
		OpenBuzz(2093);
		delay_01(10);
		StopBuzz();

		currentKeyVal = 0x27;
	}	
	else if(keycode01 == 0x38)    //数字8键 启动音乐播放
	{
		OpenBuzz(2349);
		delay_01(10);
		StopBuzz();		
		
		music = 1;
		
	}	
	else if(keycode01 == 0x39)    //数字9键 停止音乐播放
	{
		OpenBuzz(2637);
		delay_01(10);
		StopBuzz();	
		
		music = 0;
		
	}		
	
}





void KeyDriver() //按键驱动函数，检测按键动作
{
	static unsigned char i,j;
	static unsigned char backup[4][4] = {
		{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
	};
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(backup[i][j] != KeySta[i][j])
			{
				if(backup[i][j] != 0)
				{
					if(Key_Mod == 0)
					{
						KeyAction(KeyCodeMap[i][j]);
					}
					if(Key_Mod == 1)
					{
						KeyAction_01(KeyCodeMap[i][j]);
					}
				}
				backup[i][j] = KeySta[i][j];
			}
		}
	}
}
				



	
void KeyScan()                //按键扫描与消抖
{
	unsigned char i;
	static unsigned char keyout = 0;
	static unsigned char keybuf[4][4] = {
		{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
		{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF}
	};
	
	keybuf[keyout][0] = (keybuf[keyout][0]<<1) | KEY_IN_1;
	keybuf[keyout][1] = (keybuf[keyout][1]<<1) | KEY_IN_2;
	keybuf[keyout][2] = (keybuf[keyout][2]<<1) | KEY_IN_3;
	keybuf[keyout][3] = (keybuf[keyout][3]<<1) | KEY_IN_4;
	
	for(i=0;i<4;i++)
	{
		if((keybuf[keyout][i] & 0x0F) == 0x00)
		{
			KeySta[keyout][i] = 0;
		}
		else if((keybuf[keyout][i] & 0x0F) == 0x0F)
		{
			KeySta[keyout][i] = 1;
		}
	}
	
	keyout++;
	keyout = keyout & 0x03;
	switch(keyout)
	{
		case 0:KEY_OUT_4 = 1; KEY_OUT_1 = 0;break;
		case 1:KEY_OUT_1 = 1; KEY_OUT_2 = 0;break;
	  case 2:KEY_OUT_2 = 1; KEY_OUT_3 = 0;break;
	  case 3:KEY_OUT_3 = 1; KEY_OUT_4 = 0;break;
		default:break;
	}
}


















