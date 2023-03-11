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
	
	ReadBuf = EEPROM_Read(0xF5);
	
	if(ReadBuf != 78)
	{
		LedTimerDataWrite(1);
		LedTimerDataWrite(2);
		LedTimerDataWrite(3);
		LedTimerDataWrite(4);
		EEPROM_Write(0xF5,78);
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
	Timer_Data_Buff = Timer_Data_Buff * 10;
	Timer_Data_Buff = Timer_Data_Buff + EEPROM_Read(0x11);
	Timer_Data_Buff = Timer_Data_Buff * 10;
	Timer_Data_Buff = Timer_Data_Buff + EEPROM_Read(0x12);
	Timer_Data_Buff = Timer_Data_Buff * 10;	
	Timer_Data_Buff = Timer_Data_Buff + EEPROM_Read(0x13);	
	Led_Timer_Buff_Mode[0] = Timer_Data_Buff;
	Timer_Data_Buff = 0;
	
	Timer_Data_Buff = EEPROM_Read(0x15);
	Timer_Data_Buff = Timer_Data_Buff * 10;
	Timer_Data_Buff = Timer_Data_Buff + EEPROM_Read(0x16);
	Timer_Data_Buff = Timer_Data_Buff * 10;
	Timer_Data_Buff = Timer_Data_Buff + EEPROM_Read(0x17);
	Timer_Data_Buff = Timer_Data_Buff * 10;	
	Timer_Data_Buff = Timer_Data_Buff + EEPROM_Read(0x18);	
	Led_Timer_Buff_Mode[1] = Timer_Data_Buff;
	Timer_Data_Buff = 0;

	Timer_Data_Buff = EEPROM_Read(0x20);
	Timer_Data_Buff = Timer_Data_Buff * 10;
	Timer_Data_Buff = Timer_Data_Buff + EEPROM_Read(0x21);
	Timer_Data_Buff = Timer_Data_Buff * 10;
	Timer_Data_Buff = Timer_Data_Buff + EEPROM_Read(0x22);
	Timer_Data_Buff = Timer_Data_Buff * 10;	
	Timer_Data_Buff = Timer_Data_Buff + EEPROM_Read(0x23);	
	Led_Timer_Buff_Mode[2] = Timer_Data_Buff;
	Timer_Data_Buff = 0;

	Timer_Data_Buff = EEPROM_Read(0x25);
	Timer_Data_Buff = Timer_Data_Buff * 10;
	Timer_Data_Buff = Timer_Data_Buff + EEPROM_Read(0x26);
	Timer_Data_Buff = Timer_Data_Buff * 10;
	Timer_Data_Buff = Timer_Data_Buff + EEPROM_Read(0x27);
	Timer_Data_Buff = Timer_Data_Buff * 10;	
	Timer_Data_Buff = Timer_Data_Buff + EEPROM_Read(0x28);	
	Led_Timer_Buff_Mode[3] = Timer_Data_Buff;	
}

void LedTimerDataWrite(unsigned char DataCode)
{
	unsigned char Data_Buff = 0;
	switch(DataCode)
	{
		case 1: 
			Data_Buff = (Led_Timer_Buff_Mode[0]/1000)%10;
			EEPROM_Write(0x10,Data_Buff);
			Delay5ms();
			Data_Buff = 0;
			Data_Buff = (Led_Timer_Buff_Mode[0]/100)%10;
			EEPROM_Write(0x11,Data_Buff);
			Delay5ms();
			Data_Buff = 0;
			Data_Buff = (Led_Timer_Buff_Mode[0]/10)%10;
			EEPROM_Write(0x12,Data_Buff);
			Delay5ms();	
			Data_Buff = 0;
			Data_Buff = (Led_Timer_Buff_Mode[0])%10;
			EEPROM_Write(0x13,Data_Buff);
			Delay5ms();	
			break;
		case 2: 
			Data_Buff = (Led_Timer_Buff_Mode[1]/1000)%10;
			EEPROM_Write(0x15,Data_Buff);
			Delay5ms();
			Data_Buff = 0;
			Data_Buff = (Led_Timer_Buff_Mode[1]/100)%10;
			EEPROM_Write(0x16,Data_Buff);
			Delay5ms();
			Data_Buff = 0;
			Data_Buff = (Led_Timer_Buff_Mode[1]/10)%10;
			EEPROM_Write(0x17,Data_Buff);
			Delay5ms();	
			Data_Buff = 0;
			Data_Buff = (Led_Timer_Buff_Mode[1])%10;
			EEPROM_Write(0x18,Data_Buff);
			Delay5ms();	
			break;
		case 3: 
			Data_Buff = (Led_Timer_Buff_Mode[2]/1000)%10;
			EEPROM_Write(0x20,Data_Buff);
			Delay5ms();
			Data_Buff = 0;
			Data_Buff = (Led_Timer_Buff_Mode[2]/100)%10;
			EEPROM_Write(0x21,Data_Buff);
			Delay5ms();
			Data_Buff = 0;
			Data_Buff = (Led_Timer_Buff_Mode[2]/10)%10;
			EEPROM_Write(0x22,Data_Buff);
			Delay5ms();	
			Data_Buff = 0;
			Data_Buff = (Led_Timer_Buff_Mode[2])%10;
			EEPROM_Write(0x23,Data_Buff);
			Delay5ms();	
			break;
		case 4: 
			Data_Buff = (Led_Timer_Buff_Mode[3]/1000)%10;
			EEPROM_Write(0x25,Data_Buff);
			Delay5ms();
			Data_Buff = 0;
			Data_Buff = (Led_Timer_Buff_Mode[3]/100)%10;
			EEPROM_Write(0x26,Data_Buff);
			Delay5ms();
			Data_Buff = 0;
			Data_Buff = (Led_Timer_Buff_Mode[3]/10)%10;
			EEPROM_Write(0x27,Data_Buff);
			Delay5ms();	
			Data_Buff = 0;
			Data_Buff = (Led_Timer_Buff_Mode[3])%10;
			EEPROM_Write(0x28,Data_Buff);
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



















