#include <config.h>




unsigned char ADC_Data = 0;


bit flag10ms = 0;
bit flag50ms = 0;
bit flag100ms = 0;
bit flag200ms = 0;
bit flag500ms = 0;

bit flag_Led8 = 0;



void RedaData();

void main()
{
	EEPROM_FirstRead();
	LedBuzzInit();
	Timer0Init();
	Timer1Init();
	
	
	
	while(1)
	{
		if(flag10ms == 1)
		{
			flag10ms = 0;	
			KeyDriver();
			SmgMenuMain();			
		}		

		RedaData();
	}
}


void Timer1Int() interrupt 3
{
	static unsigned int cnt = 0;
	
	cnt++;
	if((cnt % 10) == 0)
	{
		flag10ms = 1;
	}
	if((cnt % 50) == 0)
	{
		flag50ms = 1;
	}
	if((cnt % 104) == 0)
	{
		flag100ms = 1;
	}
	if((cnt % 189) == 0)
	{
		flag200ms = 1;
	}
	if(cnt >= 500)
	{
		cnt = 0;
		flag500ms = 1;
	}
	
	if(flag_StartKey6 == 1)
	{
		if(Key6_SetTime < 800)
		{
			Key6_SetTime++;
		}
	}
	
	
	LedDisplay();
	SmgDisplay();
	KeyScan();
}


void RedaData()
{
	float Data_Buf = 0;
	
	if(flag50ms == 1)
	{
		flag50ms = 0;
		ADC_ReadAIN3Data(&ADC_Data);
		Data_Buf = ADC_Data;
		Data_Buf /= 5.1;
		ADC_Data = Data_Buf; 			
	}
	if(flag100ms == 1)
	{
		flag100ms = 0;
		if(Key6_SetTime >= 800)
		{
			if(Parm_ADC_Buf < 50)
			{
				Parm_ADC_Buf++;
			}
			else
			{
				Parm_ADC_Buf = 10;
			}			
		}
	}
	if(flag200ms == 1)
	{
		flag200ms = 0;
		Ds18b20ReadData();
		Ds18b20ReadConfig();
		if(ADC_Data > Parm_ADC)
		{
			flag_Led8 = ~flag_Led8;
		}
		else
		{
			flag_Led8 = 1;
		}
	}
	if(flag500ms == 1)
	{
		flag500ms = 0;
		NE555ReadFreqData(&Freq_Data);
	}

}





