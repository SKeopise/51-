#include "NE555.h"





void Timer0Init()	//定时器0初始化,用于NE555频率测量
{
	TH0 = 0x00;	//定时器0高8位
	TL0 = 0x00;	//定时器0低8位
	TMOD |= 0x05;	//定时器0工作在计数模式,16位定时器
	TR0 = 1;	//启动定时器0
	TF0 = 0;	//清除定时器0溢出标志
	ET0 = 0;	//禁止定时器0中断
}


void ReadFreqNe555(unsigned int* freq)	//读取NE555频率,保存指针freq指向的变量中
{
	*freq = TH0;	//读取定时器0高8位
	*freq = (*freq<<8)|TL0;	//读取定时器0低8位
	TH0 = 0x00;	//清除定时器0高8位
	TL0 = 0x00;	//清除定时器0低8位
}
















