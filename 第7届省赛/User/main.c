#include <config.h>





unsigned char pdata Mode = 1;

unsigned char Temp = 0;


bit flag_750ms = 0;
bit flag_1s = 0;

void PwmOutP34();
void ReadData();

void main()
{
	
	LedBuzzInit();
	Timer0Init();
	Timer1Init();
	Ds18b20ReadInit();
	ReadDs18b20Temp();
	
	while(1)
	{
		SmgShowPwmMode(Mode);
		KeyDriver();
		ReadData();
	}
}

void Timer0Int() interrupt 1
{
	static unsigned int cnt = 0;
	static unsigned char cnt_Time = 0;
	
	cnt++;
	if((cnt%100) == 0)
	{
		cnt_Time++;
		if(cnt_Time>=10)
		{
			cnt_Time = 0;
			flag_1s = 1;
		}
	}
	if(cnt >= 750)
	{
		cnt = 0;
		flag_750ms = 1;
	}


	
	LedDisplay();
	SmgDisplay();
	KeyScan();

}

void Timer1Int() interrupt 3
{
	PwmOutP34();

}


void ReadData()
{
	if(flag_750ms == 1)
	{
		flag_750ms = 0;
		Temp = ReadDs18b20Temp();
		Ds18b20ReadInit();
	}
	if(flag_1s == 1)
	{
		flag_1s = 0;
		if(Stop == 0)
		{
			if(TimeLast > 0)
			{
				TimeLast--;
			}
		}
	}
	
	if(Stop == 1)
	{
		TimeLast = 0;
	}	
}

void PwmOutP34()
{
	if(TimeLast != 0)
	{
		if(Mode == 1)
		{
			PWM_OUT = PwmOutput(200);
		}
		else if(Mode == 2)
		{
			PWM_OUT = PwmOutput(300);
		}
		else if(Mode == 3)
		{
			PWM_OUT = PwmOutput(700);
		}
		else
		{
			if(Mode_Buf == 1)
			{
				PWM_OUT = PwmOutput(200);
			}
			else if(Mode_Buf == 2)
			{
				PWM_OUT = PwmOutput(300);
			}
			else if(Mode_Buf == 3)
			{
				PWM_OUT = PwmOutput(700);
			}			
		}
	}
	else
	{
		PWM_OUT = 0;	
	}
}



