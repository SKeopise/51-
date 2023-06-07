#include <config.h>








bit flag10ms = 0;

bit flag50ms = 0;

bit flag100ms = 0;


void DataRead();

void main()
{
	FirstReadData();
	LedBuzzInit();
	Timer0Init();
	PCA_Init();
	
	
	while(1)
	{
		DataRead();
	}

}

void Timer0Int() interrupt 1
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
	if((cnt % 100) == 0)
	{
		flag100ms = 1;
	}
	if(cnt >= 1000)
	{
		cnt = 0;
	}
	

	
	LedDisplay();
	SmgDisplay();
	KeyScan();
}


void DataRead()
{
	unsigned char DAC_Buf = 0;
	float Data_Buf = 0;
	
	if(flag10ms == 1)
	{
		flag10ms = 0;
		SmgMenuMain();		
	}
	if(flag50ms == 1)
	{
		flag50ms = 0;
		KeyDriver();		
	}
	if(flag100ms == 1)
	{
		flag100ms = 0;
		if(Sonic_Distence <= Parm_Distence)
		{
			DAC_Output(0);
		}
		else
		{
			Data_Buf = Sonic_Distence - Parm_Distence;
			Data_Buf *= 0.02;
			Data_Buf *= 53.125;
			if(Data_Buf > 255)
			{
				DAC_Buf = 255;
			}
			else
			{
				DAC_Buf = Data_Buf;
			}
			DAC_Output(DAC_Buf);
		}
	}
}





