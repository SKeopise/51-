#include <config.h>









unsigned int cnt = 0;

bit flag_100ms = 0;
bit flag_750ms = 0;

bit Flag_Warring_Clock = 0;

void TimerWarring();
void ReadData();

void main()
{

	Timer0Init();
	LedBUZZInit();
	Ds1302Init();
	Ds18B20ReadInit();
	Ds18B20ReadTempData();
	
	while(1)
	{
		SmgShow();
		ReadData();
		KeyDriver();
	}
}


void Timer0Int() interrupt 1
{
	static unsigned char Cnt_Time =0;
	cnt++;
	
	if((cnt%100) == 0)
	{
		flag_100ms = 1;
		Cnt_Time++;
		if(Flag_Warring_Clock == 1)
		{	
			flag_5s++;
			if((Cnt_Time%2)==0)
			{
				if(flag_200ms == 1)
				{
					flag_200ms = 0;
				}
				else
				{
					flag_200ms = 1;
				}
			}
		}
		if(Cnt_Time >= 10)
		{
			Cnt_Time = 0;
			if(flag_1s == 1)
			{
				flag_1s = 0;
			}
			else
			{
				flag_1s = 1;
			}	
		}	
	}
	if(cnt >= 750)
	{
		flag_750ms = 1;
		cnt = 0;
	}

	

	SmgDisplay();
	LedShow();
	KeyScan();
}


void ReadData()
{
	if(flag_100ms == 1)
	{
		flag_100ms = 0;
		if(Clock_Data_Set == 0)
		{
			Ds1302TimerRead();
			TimerWarring();
		}
	}
	if(flag_750ms == 1)
	{
		flag_750ms = 0;
		Ds18B20ReadTempData();
		Ds18B20ReadInit();
	}
}



//比较TimerData和Timer_Warring的函数
void TimerWarring()
{
	//定义一个缓存数组，用于存放TimerData的数据
	unsigned char Timer_Data_Buff[3];
	//将TimerData的数据由bcd码转为10进制数后再转存到Timer_Data_Buff数组中
	Timer_Data_Buff[2] = (TimerData[2]>>4)*10+(TimerData[2]&0x0F);
	Timer_Data_Buff[1] = (TimerData[1]>>4)*10+(TimerData[1]&0x0F);
	Timer_Data_Buff[0] = (TimerData[0]>>4)*10+(TimerData[0]&0x0F);

	//比较缓存数组和Timer_Warring数组的数据，如果相等则将Timer_Warring_Time_Set置1，用于显示闹钟时间
	if(Timer_Data_Buff[2] == Timer_Warring[2] && Timer_Data_Buff[1] == Timer_Warring[1] && Timer_Data_Buff[0] == Timer_Warring[0])
	{
		Flag_Warring_Clock = 1;
	}
}





