

#include "init.h"

bit Buzz_Warring = 0;
unsigned char Buzz_Time = 0;
unsigned char Door_Open_Time = 0;




void DoorOpenAndWarring()
{
	P0 = 0x00;
	
	if(Door_Open == 1)
	{
		RELAY = 1;
	}
	else
	{
		RELAY = 0;
	}
	
	if(Error_Cnt > 2)
	{
		Error_Cnt = 0;
		Buzz_Warring = 1;
		Password_Mode = 0;
	}
	if(Buzz_Time > 0)
	{
		BUZZ = 1;
	}
	else
	{
		BUZZ = 0;
	}
	
	HC138Y(5);
	HC138Y(0);
}

void PasswordOver()
{
	unsigned char i;
	
	for(i=0;i<6;i++)
	{
		if(PassWordBuff[i] != 10)
		{
			
		}
		else
		{
			Password_Over = 0;
			PasswordBuffReset();			
			break;
		}
		if(i == 5)
		{
			Password_Over = 1;
		}
	}
}


void PasswordSet()
{
	unsigned char i = 0;
	
	for(i=0;i<6;i++)
	{
		PassWord[i] = PassWordBuff[i];
	}
	AT24C02PasswordWrite();
	PasswordBuffReset();
}


void PasswordCmd()
{
	unsigned char i = 0;
	for(i=0;i<6;i++)
	{
		if(PassWord[i] == PassWordBuff[i])
		{
			
		}
		else
		{
			Error_Cnt++;
			Password_Right = 0;
			PasswordBuffReset();
			break;
		}
		if(i == 5)
		{
			Password_Right = 1;
			Error_Cnt = 0;
			break;
		}
	}		
}

void PasswordReset()
{
	PassWord[0] = 6;
	PassWord[1] = 5;
	PassWord[2] = 4;
	PassWord[3] = 3;
	PassWord[4] = 2;
	PassWord[5] = 1;
	
	AT24C02PasswordWrite();
	Password_Right = 0;
}

void PasswordBuffReset()
{
	PassWordBuff[0] = 10;
	PassWordBuff[1] = 10;
	PassWordBuff[2] = 10;
	PassWordBuff[3] = 10;
	PassWordBuff[4] = 10;
	PassWordBuff[5] = 10;
	
	Password_Right = 0;
	Number_Code = 0;
	Password_Over = 0;
}

void HC138Y(unsigned char Y)
{
	P2 &= 0x1F;
	P2 |= (Y & 0x07) << 5;
}

void LedBuzzInit()
{
	P0 = 0xFF;
	HC138Y(4);
	P0 = 0xFF;
	HC138Y(5);
	P0 = 0x00;
	HC138Y(0);
}


void Timer0Init(void)		//1毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初始值
	TH0 = 0xD4;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
	EA = 1;
}






