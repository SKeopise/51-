#include "init.h"






// 定时器初始化函数
void timer0_init()
{
	AUXR |= 0x80;	
	TMOD &= 0xF0;		
	TL0 = 0x20;		
	TH0 = 0xD1;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
}


void selectOutput(int outputNumber)     //138译码器控制函数
{
  P2 &= 0x1f;  // 清空 P2.5、P2.6 和 P2.7
  P2 |= ((outputNumber & 0x7) << 5);  // 设置 P2.5、P2.6 和 P2.7
}

void LedBuzzInit()       //关LED灯和蜂鸣器
{
	selectOutput(4);
	P0 = ~0x00;	
	selectOutput(5);
	P0 = 0x00;
	selectOutput(0);
}

void delay_us(unsigned int us)
{
    while(us--);
}















