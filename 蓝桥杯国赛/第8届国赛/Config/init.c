#include "init.h"








void Timer0Init()		//1毫秒@12.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x20;		//设置定时初始值
	TH0 = 0xD1;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	
	ET0 = 1;
	EA = 1;
}






void LedBuzzInit()
{
	P0 = 0xFF;
	HC138Set(4);
	HC138Set(0);
	P0 = 0x00;
	HC138Set(5);
	HC138Set(0);	
}



void HC138Set(unsigned char Y)
{
	P2 &= 0x1F;
	P2 |= (Y & 0x07) << 5;	
}








