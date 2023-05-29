
#include <config.h>





bit flag50ms = 0;

bit flag100ms = 0;

bit flag500ms = 0;



void main()
{
	LedBuzzInit();
	Timer2Init();
	NE555Init();
	
	while(1)
	{		
		if(flag50ms == 1)
		{
			flag50ms = 0;
			KeyDriver();
			SmgMenuMain();
		}
		if(flag100ms == 1)
		{
			flag100ms = 0;
		}
		if(flag500ms == 1)
		{
			flag500ms = 0;
			NE555FreqReadData(&NE555_Freq);
		}
	}
}

void Timer2Int() interrupt 12
{
	static unsigned int cnt = 0;
	
	cnt++;
	if((cnt % 50) == 0)
	{
		flag50ms = 1;		
	}
	if((cnt % 100) == 0)
	{
		flag100ms = 1;
	}
	if(cnt >= 500)
	{
		cnt = 0;
		flag500ms = 1;
	}
	

	
	SmgDisplay();
	KeyScan();
}











