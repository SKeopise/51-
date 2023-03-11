
#include <config.h>


unsigned int Led_Timer = 400;

unsigned char Pwm_Mode = 25;

unsigned char ADC = 0;

bit Led_Change = 0;

bit flag100ms = 0;




void ReadData();

void main()
{
	BuzzLedInit();
	Timer0Init();
	LedTimerRead();
	
	while(1)
	{
		ReadData();
		
		SmgControl();
		KeyDriver();
	}

}

void Timer0Int() interrupt 1
{
	static unsigned int cnt = 0;
	
	cnt++;
	if((cnt % 100) == 0)
	{
		flag100ms = 1;
		flag08s++;
		if(flag08s >= 8)
		{
			flag08s = 0;
			if(flag08s_change == 0)
			{
				flag08s_change = 1;
			}
			else 
			{
				flag08s_change = 0;
			}
		}
	}
	if(cnt >= Led_Timer)
	{
		cnt = 0;
		if(Led_Running_Open == 1)
		{
			Led_Change = 1;
		}
	}

	
	Led_Open = LedPwm(Pwm_Mode);
	KeyScan();
	SmgDisplay();
	LedControl();
}


void ReadData()
{
	if(flag100ms == 1)
	{
		flag100ms = 0;
		ADC = AD_RB2_AIN3();
		if(ADC <= 64)
		{
			Pwm_Mode = 25;
		}
		else if(ADC > 64 && ADC <= 128)
		{
			Pwm_Mode = 50;
		}
		else if(ADC > 128 && ADC <= 192)
		{
			Pwm_Mode = 75;
		}
		else if(ADC > 192 && ADC <= 255)
		{
			Pwm_Mode = 100;
		}		
	}
	LedTimerDataRead();
}









