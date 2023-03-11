
#include <config.h>



unsigned int RD1_Vin = 0;
float RD1_Buff = 0;
bit Light_Dark = 0;


bit flag100ms = 0;
bit flag200ms = 0;
bit flag750ms = 0;

unsigned char flag3S = 0;
bit flagLed1 = 0;

void ReadData();
void TimeParmCmp();

void main()
{
	Timer0Init();
	BuzzLedInit();
	
	DS1302Init();
	DS1302TimerRead();
	DS18B20Init();
	ReadTempData();
	PCF8951Init();
	ReadAIN1();
	
	
	while(1)
	{
		KeyDriver();
		SmgShowDriver();
		ReadData();
		TimeParmCmp();
	}
}

void Timer0Interrupt() interrupt 1
{
	static unsigned int cnt = 0;
	
	cnt++;
	if((cnt%100) == 0)
	{
		flag100ms = 1;
	}
	else if((cnt%230) == 0)
	{
		flag200ms = 1;
	}
	if(cnt>=750)
	{
		cnt = 0;
		flag750ms = 1;
	}
	
	SmgDisplay();
	LedDisplay();
	KeyScan();

}

void ReadData()
{
	if(flag750ms == 1)
	{
		flag750ms = 0;
		ReadTempData();
		DS18B20Init();
	}
	if(flag200ms == 1)
	{
		DS1302TimerRead();
		TimeParmCmp();
		flag200ms = 0;
	}
	if(flag100ms == 1)
	{
		RD1_Buff = ReadAIN1()*(4.9/255);
		RD1_Vin = RD1_Buff * 100;
		if(RD1_Vin < 100)
		{
			Light_Dark = 1;
		}
		else
		{
			Light_Dark = 0;
		}
		
		if(Light_Dark == 1)
		{
			if(flag3S < 30)
			{
				flag3S++;
			}
		}
		else
		{
			flag3S = 0;
		}
		
		flag100ms = 0;
	}
	
}


void TimeParmCmp()
{
	unsigned char hour;
	
	hour = TimerData[2]>>4;
	hour = hour*10;
	hour += TimerData[2]&0x0F;
	
	if(Timer_Parm < 8)
	{
		if((hour >= Timer_Parm) && (hour < 8))
		{
			flagLed1 = 1;
		}
		else
		{
			flagLed1 = 0;
		}
	}
	else
	{
		if((hour >= Timer_Parm) || (hour < 8))
		{
			flagLed1 = 1;
		}
		else
		{
			flagLed1 = 0;
		}
	}
	
	
}







