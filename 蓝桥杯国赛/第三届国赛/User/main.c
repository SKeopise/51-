#include <config.h>


unsigned char PassWord[6] = {6,5,4,3,2,1};  //实际密码存储


bit Door_Mod = 1;        //0为自动门状态，1为密码门状态
bit Door_Open = 0;
bit flag100ms = 0;       
bit flag200ms = 0;

void ReadData();
void DoorControl();
void DoorModControl();
void BuzzDoorOpenControl();

void main()
{
	LedBuzzInit();
	Timer0Init();
	Ds1302Init();
	AT24C02FirstRead();
	
	
	while(1)
	{
		DoorControl();
		ReadData();
		KeyDriver();
	}
}

void Timer0_Int() interrupt 1
{
	static unsigned int cnt = 0;
	
	cnt++;
	if((cnt % 100) == 0)
	{
		flag100ms = 1;
		BuzzDoorOpenControl();
	}
	if(cnt >= 140)
	{
		flag200ms = 1;
		cnt = 0;
	}
	
	DoorOpenAndWarring();
	KeyScan();
	SmgDisplay();
	LedDisplay();	

}

void BuzzDoorOpenControl()
{
	if(Buzz_Warring == 1)
	{
		Buzz_Time++;
		if(Buzz_Time >= 30)
		{
			Buzz_Time = 0;
			Buzz_Warring = 0;
		}
	}
	if(Door_Open == 1)
	{
		Door_Open_Time++;
		if(Door_Open_Time >= 50)
		{
			Door_Open_Time = 0;
			Door_Open = 0;
		}
	}
}

void ReadData()
{
	if(flag100ms == 1)
	{
		flag100ms = 0;
		Ds1302Read();
		DoorModControl();
	}
	if(flag200ms == 1)
	{
		flag200ms = 0;
		Sonic();
	}

}

void DoorControl()
{
	if(Door_Mod == 0)
	{
		SmgTimerShow();
	}
	else
	{
		SmgPassword();
	}
}

void DoorModControl()
{
	if((TimerData[2] >= 0x07) && (TimerData[2] <= 0x22))
	{
		Door_Mod = 0;
	}
	else
	{
		Door_Mod = 1;
	}
	
}













