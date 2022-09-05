#include <init.h>



typedef struct _TASK_COMPONENTS
{
	char run;          		//程序运行标志位;0不运行，1运行;
	char Time;         		//计时器
	char itvTime;      		//任务运行间隔
	void (*TaskHook)();    //要执行的任务函数
	
}TASK_COMPONENTS;


static TASK_COMPONENTS TaskComps[] =
{
	{0,50,50,Led_18B20Buff},
  {0,250,250,Led_DS1302Buff},
	{0,30,50,DS18B20_Read},
	{0,150,150,Key_Driver},
	{0,200,250,DS1302_Read}
};

typedef enum _TASK_LIST    //任务清单
{
  TASK_LED_DS18B20,
  TASK_LED_DS1302,
	TASK_DS18B20,	
	TASK_KEY_SCAN,
	TASK_DS1302,
	
	TASK_MAX
	
}TASK_LIST;


void TaskRemarks()              //中断服务函数，根据设定时间片进行任务轮询
{
  static unsigned char i;
	
	for(i = 0; i < TASK_MAX ;i++)
	{
		if(TaskComps[i].Time != 0)
		{
			TaskComps[i].Time--;
			if(TaskComps[i].Time == 0)
			{
				TaskComps[i].Time = TaskComps[i].itvTime;
				TaskComps[i].run = 1;		
			}
		}
	}
	
}

void TaskProcess()
{
	unsigned char i;
	
	for(i=0;i<TASK_MAX;i++)
	{
		if(TaskComps[i].run != 0)
		{
			TaskComps[i].TaskHook();
			TaskComps[i].run = 0;
		}
	}
}




void Timer0init()
{
	AUXR |= 0x80;		
	TMOD &= 0xF0;	
	TL0 = 0xCD;	
	TH0 = 0xD4;		
	TF0 = 0;	
	TR0 = 1;	
	ET0 = 1;
	EA = 1;	
}

void Timer1init()
{
	AUXR |= 0x40;		
	TMOD &= 0x0F;	
	TL1 = 0xFF;	
	TH1 = 0xFE;		
	TF1 = 0;	
	TR1 = 1;	
	ET1 = 1;
	EA = 1;	
}


void HC138(unsigned char Y)
{
	switch(Y)
	{
		case 0:P2 = (P2 & 0x1f) | 0x00; break;
		case 1:P2 = (P2 & 0x1f) | 0x20; break;
		case 2:P2 = (P2 & 0x1f) | 0x40; break;
		case 3:P2 = (P2 & 0x1f) | 0x60; break;
		case 4:P2 = (P2 & 0x1f) | 0x80; break;
		case 5:P2 = (P2 & 0x1f) | 0xA0; break;
		case 6:P2 = (P2 & 0x1f) | 0xC0; break;
		case 7:P2 = (P2 & 0x1f) | 0xE0; break;
		default: break;
	}
}

void ALL_INIT()
{
	HC138(4);
	P0 = 0xFF;
	HC138(5);
	P0 = 0x00;
	HC138(0);

}

//void delay(unsigned int t)
//{
//	while(t--);

//}





