#include "init.h"



void Delay5ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 59;
	j = 90;
	do
	{
		while (--j);
	} while (--i);
}


void LedTimerRead()
{
	unsigned char ReadBuf = 0;
	
	ReadBuf = EEPROM_Read(0xF8);
	
	if(ReadBuf != 78)
	{
		LedTimerDataWrite(1);
		LedTimerDataWrite(2);
		LedTimerDataWrite(3);
		LedTimerDataWrite(4);
		EEPROM_Write(0xF8,78);
	}
	else
	{
		
	}
	LedTimerDataRead();
}


void LedTimerDataRead()
{
	unsigned int Timer_Data_Buff = 0;
	
	Timer_Data_Buff = EEPROM_Read(0x10);
	Timer_Data_Buff = Timer_Data_Buff << 8;
	Timer_Data_Buff = Timer_Data_Buff | EEPROM_Read(0x11);
	Led_Timer_Buff_Mode[0] = Timer_Data_Buff;
	Timer_Data_Buff = 0;
	
	Timer_Data_Buff = EEPROM_Read(0x20);
	Timer_Data_Buff = Timer_Data_Buff << 8;
	Timer_Data_Buff = Timer_Data_Buff | EEPROM_Read(0x21);
	Led_Timer_Buff_Mode[1] = Timer_Data_Buff;
	Timer_Data_Buff = 0;

	Timer_Data_Buff = EEPROM_Read(0x30);
	Timer_Data_Buff = Timer_Data_Buff << 8;
	Timer_Data_Buff = Timer_Data_Buff | EEPROM_Read(0x31);
	Led_Timer_Buff_Mode[2] = Timer_Data_Buff;
	Timer_Data_Buff = 0;

	Timer_Data_Buff = EEPROM_Read(0x40);
	Timer_Data_Buff = Timer_Data_Buff << 8;
	Timer_Data_Buff = Timer_Data_Buff | EEPROM_Read(0x41);
	Led_Timer_Buff_Mode[3] = Timer_Data_Buff;
	Timer_Data_Buff = 0;	
}

void LedTimerDataWrite(unsigned char DataCode)
{
	unsigned char Data_Buff = 0;
	switch(DataCode)
	{
		case 1: 
			Data_Buff = (unsigned char)(Led_Timer_Buff_Mode[0]>>8);
			EEPROM_Write(0x10,Data_Buff);
			Delay5ms();
			Data_Buff = 0;
			Data_Buff = (unsigned char)(Led_Timer_Buff_Mode[0]&0x00FF);
			EEPROM_Write(0x11,Data_Buff);
			Delay5ms();
			break;
		case 2: 
			Data_Buff = (unsigned char)(Led_Timer_Buff_Mode[1]>>8);
			EEPROM_Write(0x20,Data_Buff);
			Delay5ms();
			Data_Buff = 0;
			Data_Buff = (unsigned char)(Led_Timer_Buff_Mode[1]&0x00FF);
			EEPROM_Write(0x21,Data_Buff);
			Delay5ms();
			break;
		case 3: 
			Data_Buff = (unsigned char)(Led_Timer_Buff_Mode[2]>>8);
			EEPROM_Write(0x30,Data_Buff);
			Delay5ms();
			Data_Buff = 0;
			Data_Buff = (unsigned char)(Led_Timer_Buff_Mode[2]&0x00FF);
			EEPROM_Write(0x31,Data_Buff);
			Delay5ms();
			break;
		case 4: 
			Data_Buff = (unsigned char)(Led_Timer_Buff_Mode[3]>>8);
			EEPROM_Write(0x40,Data_Buff);
			Delay5ms();
			Data_Buff = 0;
			Data_Buff = (unsigned char)(Led_Timer_Buff_Mode[3]&0x00FF);
			EEPROM_Write(0x41,Data_Buff);
			Delay5ms();
			break;
		default: break;
	}

}



bit LedPwm(unsigned char pwm)
{
	static unsigned char Pwm_Side = 0;
	unsigned char Pwm_Buff = 0; 
	
	Pwm_Buff = 100 - pwm;
	
	if(Pwm_Side < pwm)
	{
		Pwm_Side += Pwm_Buff;
		return 1;
	}
	else
	{
		Pwm_Side -= pwm;
		return 0;
	}

}



void Timer0Init(void)		//1毫秒@12.000MHz
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


void BuzzLedInit()
{	
	P0 = 0xFF;
	HC138(4);
	HC138(7);
	HC138(0);
	BUZZ = 0;
	RELAY = 0;
	HC138(5);
	HC138(0);	

}



void HC138(unsigned char Y)
{
	P2 &= 0x1F;
	P2 |= (Y & 0x07) << 5;
}



















