#include <config.h>


unsigned int cnt = 0;

float DAC = 0;

bit flag750ms = 0;



void ReadData();

void main()
{
	LedBuzzInit();
	Timer0Init();
	Init_PCF8591();
	InitDs18b20();
	TempRead();
	
	while(1)
	{
		KeyDriver();
		
		ReadData();
		
		SmgShowMode();
		
		DAC_PCF8591(DAC);
	}

}


void Timer0_int() interrupt 1
{
	cnt++;
	if(cnt >= 750)
	{
		cnt = 0;
		flag750ms = 1;
	}
	
	SmgDisplay();
	LedMode();	
	KeyScan();
}

void ReadData()
{
	if(flag750ms == 1)
	{
		flag750ms = 0;
		temp = TempRead();
		InitDs18b20();
	}
	
	if(DAC_Mode == 0)
	{
		if(temp >= (parm*100))
		{
			DAC = 255;
		}
		else
		{
			DAC = 0;
		}
		DAC_Number = (DAC/51)*100;
	}
	else
	{
		if(temp <= 2000)
		{
			DAC = 53.125;
		}
		else if(temp >= 4000)
		{
			DAC = 212.5;
		}
		else
		{
			DAC = (((temp/100)*0.15) - 2)*53.125;
		}
		DAC_Number = (DAC/53.125)*100;		
	}
}








