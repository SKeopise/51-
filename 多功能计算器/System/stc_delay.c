
#include <stc_delay.h>



  bit StopwatchRunning = 0;
  bit StopwatchRefresh = 1;
	unsigned char DecimalPart = 0;
	unsigned char IntegerPart = 0;
	unsigned char minute = 0;




void delay_01(unsigned int num) //��ʱ����
{
	 unsigned int i;
	 while(num--)
	 for(i=0; i<628; i++);
		
}


void StopwatchAction()    //����أ��������ʱ���¹رգ���֮����
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

void StopwatchReset()     //���λ����
{
	StopwatchRunning = 0;
	DecimalPart = 0;
	IntegerPart = 0;
	minute = 0;
	StopwatchRefresh = 1;

}


void StopwatchCount()    //�������ת����С���������ֱ���ʾ
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











