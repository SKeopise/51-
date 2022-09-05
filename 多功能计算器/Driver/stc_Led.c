

#include <stc_Led.h>
#include <stc_delay.h>




unsigned char LedBuff[] = {                                  //数码管显示缓冲
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};

unsigned char code Led_Mod[] = {
	0xFE,0xFD
};

unsigned char code LedChar[] = {
		0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,          //数码管显示真值表数组
		0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};

unsigned char code LedChar_Flowing[] = {                     //流水灯数组
	0XFE,0XFD,0XFB,0XF7,0XEF,0XDF,0XBF,0X7F,
	0XBF,0XDF,0XEF,0XF7,0XFB,0XFD
};



unsigned char code number8[14][8]= {
	{0xC7,0xBB,0x7D,0x5D,0x6D,0x75,0xBB,0xC7}, //0
	{0xF7,0xF3,0xF7,0xF7,0xF7,0xF7,0xF7,0xE3}, //1
	{0xE3,0xDD,0xDD,0xEF,0xF7,0xFB,0xFD,0xC2}, //2
	{0xC7,0xBB,0xBF,0xCF,0xBF,0xBB,0xC7,0xFF}, //3
	{0xFF,0xDF,0xCF,0xD7,0xDB,0x83,0xDF,0xDF}, //4
	{0x83,0xFB,0xC3,0xBF,0xBF,0xBB,0xC7,0xFF}, //5
	{0xC7,0xBB,0xFB,0xC3,0xBB,0xBB,0xC7,0xFF}, //6
	{0x83,0xBF,0xDF,0xEF,0xEF,0xEF,0xEF,0xFF}, //7
	{0xE3,0xDD,0xDD,0xE3,0xDD,0xDD,0xE3,0xFF}, //8
	{0xE3,0xDD,0xDD,0xC3,0xDF,0xDD,0xE3,0xFF}, //9
	{0xF7,0xEB,0xD5,0xB6,0xF7,0xF7,0xF7,0xF7}, //上箭头
	{0xEF,0xEF,0xEF,0xEF,0x6D,0xAB,0xD7,0xEF}, //下箭头
	{0xFF,0xBD,0xDB,0xE7,0xE7,0xDB,0xBD,0xFF}, //乘号
	{0xFF,0xEF,0xFF,0x81,0xFF,0xF7,0xFF,0xFF}  //除号
	
};




  extern unsigned char DecimalPart;
	extern unsigned char IntegerPart;
	extern unsigned char minute;

	extern unsigned char dztBuff[];
	extern unsigned char smgBuff[];
	extern bit SnakeGame;

  unsigned char LedBuff_01;


  unsigned char number_showlat;








void Led_Display()                            //数码管动态扫描函数
{
	extern unsigned char Key_Mod;
	static unsigned char i = 0;
	
	  P0 = 0xFF;
		ADDR3 =1;
		P1 = (P1 & 0xF8) | i;
		if(i <= 5)
		{
			if(SnakeGame == 0)
			{
				P0 = 0xFF;
				P0 = LedBuff[i];
			}
			else
			{
				P0 = 0xFF;
				P0 = smgBuff[i];
			}
		}
		if(i == 6)
		{
			if(SnakeGame == 0)
			{
				P0 = 0xFF;
				P0 = Led_Mod[Key_Mod];
			}
			else
			{
				P0 = 0xFF;
				P0 = LedBuff_01;
			}
		}
		if(i <= 5)
		{
			i++;
		}
		else
		{
			i = 0;
		}
		
}

void Led_Lattice()                 //LED点阵动态扫描
{
	static unsigned char i = 0;

	P0 = 0xFF;
	ADDR3 = 0;
	P1 = (P1 & 0xF8) | i;
	if(SnakeGame == 0)
	{
		P0 = 0xFF;
		P0 = number8[number_showlat][i];
	}
	else
	{
		P0 = 0xFF;
	  P0 = ~dztBuff[i];
	}
	
	if(i <= 6)
	{
		i++;
	}
	else
	{
		i = 0;
	}


}
	




void Led_Mode()       //模式灯切换函数
{
	  P0 = 0xFF;
		ADDR3 = 1;
		P1 = (P1 & 0xF8) | 6;
		P0 = Led_Mod[Key_Mod];	

}



	

void Led_Display_show_0()
{
	LedBuff[0] = LedChar[0];
}



void ShowNumber(long num)  //long将double强制转换为整形并保留小数点后一位
{
	char i;
	char buf[6];
	long a;
	if(num >= 0)
	{
		a = num;
	}
	else
	{
		a = -num;
	}
	
	for(i=0;i<6;i++)
	{
		buf[i] = a%10;
		a = a/10;
	}
	for(i=5;i>=1;i--)
	{
		if(buf[i] == 0)
			LedBuff[i] = 0xFF;
		else
			break;
	}
	for( ;i>=0;i--)
	{
		LedBuff[i] = LedChar[buf[i]];
		LedBuff[1] = LedChar[buf[1]] & 0x7F; //将第二个数码管小数点点亮且不影响其他段显示
		
		if(num < 0 && num >= -9)       //根据位数在负数后一位显示-号  
		{
			LedBuff[1] = 0x40; 
			LedBuff[2] = ~0x40;
		}
		if(num < -9 && num >= -99)                           
		{
			LedBuff[2] = ~0x40;
		}               
		if(num < -99 && num >= -999)
		{
			LedBuff[3] = ~0x40;
		}
		if(num < -999 && num >= -9999)
		{
			LedBuff[4] = ~0x40;
		}                                 
		if(num < -9999 && num >= -99999)
		{
			LedBuff[5] = ~0x40;
		}				
	}
}

void show_error()
{
		LedBuff[5] = 0xFF;
		LedBuff[4] = ~0x79;
		LedBuff[3] = ~0x50;
		LedBuff[2] = ~0x50;
		LedBuff[1] = ~0x5C;
		LedBuff[0] = ~0x50;
}
	


void StopwatchDisplay()           //分秒表显示转换函数
{
	signed char i;
	unsigned char buf[4];

	LedBuff[0] = LedChar[DecimalPart % 10];
	LedBuff[1] = LedChar[DecimalPart / 10];

	buf[0] = IntegerPart % 10;
	buf[1] = (IntegerPart / 10) % 10;
	
	buf[2] = minute % 10;
	buf[3] = (minute / 10) % 10;
	for (i = 3; i >= 1; i--)
	{
		if (buf[i] == 0)
		{
			LedBuff[i + 2] = 0xFF;
		}
		else
		{
			break;
		}
	}
	for ( ; i >= 0; i--)
	{
		LedBuff[i + 2] = LedChar[buf[i]] ;
	}
	LedBuff[2] &= 0x7F;
}

















