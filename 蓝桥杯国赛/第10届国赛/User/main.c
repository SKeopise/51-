
#include <config.h>




unsigned int Key_SetTime = 0;

unsigned int Temp_Data = 0;



bit flag10ms = 0;
bit flag50ms = 0;
bit flag100ms = 0;
bit flag200ms = 0;

bit DAC_Mode = 0;


void DataRead();
void DAC_Driver();

void main()
{
	LedBuzzInit();
	Timer0Init();
	PCA_Init();
	Ds18b20ReadConfig();
	FirstRead_EEPROM();	
	UartInit();
	
	while(1)
	{
		if(flag10ms == 1)
		{
			flag10ms = 0;
			SmgMenuMain();	
			UartDriver();			
		}

		DataRead();
	}

}

void Timer0Int() interrupt 1
{
	static unsigned int cnt = 0;

	
	cnt++;
	if((cnt % 13) == 0)
	{
		flag10ms = 1;
	}	
	if((cnt % 42) == 0)
	{
		flag50ms = 1;
	}
	if((cnt % 101) == 1)
	{
		flag100ms = 1;
	}
	if((cnt % 188) == 0)
	{
		flag200ms = 1;
	}
	if(cnt >= 1000)
	{
		cnt = 0;
	}
	
	if(flag_Key_Set == 1)
	{
		if(Key_SetTime < 1000)
		{
			Key_SetTime++;
		}
	}
	
	
	LedDisplay();
	SmgDisplay();
	KeyScan();
	UartReadTimerMonitor(1);
}

void DataRead()
{
	if(flag50ms == 1)
	{
		flag50ms = 0;
		KeyDriver();		
	}
	if(flag100ms == 1)
	{
		flag100ms = 0;
		Sonic_DataRead();
		DAC_Driver();
	}
	if(flag200ms == 1)
	{
		flag200ms = 0;
		Temp_Data = Ds18b20_ReadData();
		Ds18b20ReadConfig();
	}
}

void DAC_Driver()
{
	if(DAC_Mode == 0)
	{
		if(Sonic_Distence <= ParmData_Distence)
		{
			DAC_Output(104);
		}
		else
		{
			DAC_Output(208);
		}
	}
	else
	{
		DAC_Output(22);
	}
}





