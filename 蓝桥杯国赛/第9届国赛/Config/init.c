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




void LedBuzzInit()
{
	HC138Set(4);
	P0 = 0xFF;
	HC138Set(5);
	P0 = 0x00;
	HC138Set(0);
}


void HC138Set(unsigned char Y)
{
	P2 &= 0x1F;
	P2 |= (Y & 0x07) << 5;
}














