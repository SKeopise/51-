#include "init.h"







void Timer1Init()		//1毫秒@12.000MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x20;		//设置定时初始值
	TH1 = 0xD1;		//设置定时初始值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	
	ET1 = 1;
	EA = 1;
}



void HC138(unsigned char Y)
{
	P2 &= 0X1F;
	P2 |= (Y & 0X07) << 5;
}

void LedBUZZInit()
{
	HC138(5);
	BUZZ = 0;
	RELAY = 0;
	HC138(0);
	
	P0 = 0xFF;
	HC138(4);
	HC138(0);
}




















