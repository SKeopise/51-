
#include "led.h"


unsigned char code Led_Number[] = {                              //10为不显示
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF
};

unsigned char Led_Buff[8] = {
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};

unsigned char PassWordBuff[6] = {         //按键输入密码的显示缓存
	10,10,10,10,10,10
};



void LedDisplay()
{
	P0 = 0xFF;
	
	if(Door_Mod == 0)
	{
		LED0 = 0;
	}
	if(Password_Right == 1)
	{
		LED1 = 0;
	}
	if(Password_Over == 1)
	{
		LED2 = 0;
	}
	if(Buzz_Warring == 1)
	{
		LED3 = 0;
	}
	if(Door_Open == 1)
	{
		LED7 = 0;
	}
	if(Error_Cnt != 0)
	{
		LED6 = 0;
	}
	HC138Y(4);
	HC138Y(0);
}


void SmgTimerShow()
{
	Led_Buff[0] = Led_Number[TimerData[2]>>4];
	Led_Buff[1] = Led_Number[TimerData[2]&0x0F];
	Led_Buff[2] = 0xBF;
	Led_Buff[3] = Led_Number[TimerData[1]>>4];
	Led_Buff[4] = Led_Number[TimerData[1]&0x0F];
	Led_Buff[5] = 0xBF;
	Led_Buff[6] = Led_Number[TimerData[0]>>4];
	Led_Buff[7] = Led_Number[TimerData[0]&0x0F];
}

void SmgPassword()
{
	if(Password_Mode == 0)
	{
		Led_Buff[0] = 0xBF;
		Led_Buff[1] = 0xBF;		
	}
	else if(Password_Mode == 1)
	{
		Led_Buff[0] = 0xFF;
		Led_Buff[1] = 0xBF;		
	}
	else
	{
		Led_Buff[0] = 0xBF;
		Led_Buff[1] = 0xFF;		
	}
	Led_Buff[2] = Led_Number[PassWordBuff[0]];
	Led_Buff[3] = Led_Number[PassWordBuff[1]];
	Led_Buff[4] = Led_Number[PassWordBuff[2]];
	Led_Buff[5] = Led_Number[PassWordBuff[3]];
	Led_Buff[6] = Led_Number[PassWordBuff[4]];
	Led_Buff[7] = Led_Number[PassWordBuff[5]];	
	
}



void SmgDisplay()
{
	static unsigned char i = 0;

	P0 = 0x00;
	HC138Y(6);
	P0 = 0x01 << i;
	HC138Y(0);	
	P0 = 0xFF;
	HC138Y(7);
	P0 = Led_Buff[i];
	HC138Y(0);
	
	i++;
	if(i > 7)
	{
		i = 0;
	}	
}





