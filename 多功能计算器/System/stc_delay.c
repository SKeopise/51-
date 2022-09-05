
#include <stc_delay.h>



  bit StopwatchRunning = 0;
  bit StopwatchRefresh = 1;
	unsigned char DecimalPart = 0;
	unsigned char IntegerPart = 0;
	unsigned char minute = 0;




void delay_01(unsigned int num) //延时函数
{
	 unsigned int i;
	 while(num--)
	 for(i=0; i<628; i++);
		
}


void StopwatchAction()    //秒表开关，当秒表开启时按下关闭，反之开启
{
	if (StopwatchRunning)
	{
		StopwatchRunning = 0;
	}
	else
	{
		StopwatchRunning = 1;
	}

}

void StopwatchReset()     //秒表复位函数
{
	StopwatchRunning = 0;
	DecimalPart = 0;
	IntegerPart = 0;
	minute = 0;
	StopwatchRefresh = 1;

}


void StopwatchCount()    //秒表数字转换，小数与整数分别显示
{
	if (StopwatchRunning)
	{
		DecimalPart++;
		if (DecimalPart >= 100)
		{
			DecimalPart = 0;
			IntegerPart++;
			if (IntegerPart >= 60)
			{
				IntegerPart = 0;
				minute++;
				if(minute >= 60)
				{
					minute = 0;
				}
			}
		}
		StopwatchRefresh = 1;
		
	}
	

}











