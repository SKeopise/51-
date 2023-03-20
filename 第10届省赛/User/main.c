#include <config.h>



unsigned int cnt = 0;

float AD_Data = 0;
unsigned int AD_Show_Number = 0;

bit flag_500ms = 0;
bit flag_100ms = 0;








void ReadData();


void main()
{
	LedBUZZInit();
	Timer1Init();
	NE555Timer0Init();
	
	
	while(1)
	{
		KeyDriver();
		SmgMode();
		
		if(flag_100ms == 1)
		{
			flag_100ms = 0;
			ReadData();
		}
		
	}
}


void Timer1Int() interrupt 3
{
	cnt++;
	
	if((cnt%260) == 0)
	{
		flag_100ms = 1;
	}
	
	if(cnt>=550)
	{
		NE555_Freq = NE555_Timer_Cnt;
		NE555_Timer_Cnt = 0;
		cnt = 0;
		flag_500ms = 1;
	}
	
	KeyScan();
	SmgDisplay();
	if(Led_Open == 1)
	{
		LedMode();
	}
	else
	{
		P0 = 0xFF;
		HC138(4);
		HC138(0);
	}
	
}


void ReadData()
{
	AD_Data = PCF8591_ADC();
	if(DAC_Mode == 0)
	{
		PCF8591DAC(106);
	}
	else
	{
		PCF8591DAC(AD_Data);
	}	
	AD_Data = AD_Data/53.125;
	AD_Data *= 100;
	AD_Show_Number = AD_Data; 	

}





