#include <config.h>



// 定义一个全局变量，用于计数
volatile unsigned int cnt = 0;
volatile unsigned int keyflag = 0;

bit flag100ms = 0;
bit flag500ms = 0;

unsigned int temp = 0;      //温度数据，用于显示与判断
unsigned int tempbuf = 0;   //温度数据缓存

bit workmode = 0;          //工作模式标志位
bit Relayflag = 0;         //继电器状态标志位
bit LED3flag = 1;          //L3小灯缓存，用于判断之前小灯状态

void ShowMode();
void Read_Data();
void Control_Relay();


void main()
{
	timer0_init();      //定时器0与中断初始化
	Ds1302_Config();    //DS1302初始化，设置初始时间
	LedBuzzInit();      //关闭蜂鸣器与LED小灯
	
	while(1)
	{		
		Key_Driver();  			 //按键动作判断
		Read_Data();	  		 //读取数据
		ShowMode();   	 		 //数码管显示模式切换
		Control_Relay();	     //继电器控制
	}
}


// 定时器中断服务函数
void timer0_ISR() interrupt 1
{
	TL0 = 0x20;	
	TH0 = 0xD1;
	
	cnt++;
	if((cnt % 100) == 0)   //每100ms计数到达传递标志位
	{
		flag100ms = 1;
	}
	if(cnt >= 555)         //500ms计数标志位
	{
		cnt =0;
		flag500ms = 1;
	}
	
	displayDigit();       //数码管显示刷新
	Key_Scan();		      //按键扫描
}


void Relay(unsigned char onoff)
{
	if(onoff == 1)			//继电器开启
	{
		selectOutput(5);
		P0 = 0x10;
		selectOutput(0);
		Relayflag = 1;
	}
	else                    //继电器关闭
	{
		selectOutput(5);
		P0 = 0x00;
		selectOutput(0);
		Relayflag = 0;		
	}
}

void Control_Relay()
{
	if(workmode == 0)             		//温度控制模式下，如果检测到温度超过参数，打开继电器，温度小于参数，关闭继电器
	{
		if((Tparm*10) >= temp)
		{
			Relay(0);
		}
		else
		{
			Relay(1);
		}
	}
	else                            //时间控制模式，秒分同时等于0时即为整点
	{
		if((Ds1302_Time[1] == 0) && (Ds1302_Time[0] == 0))
		{
			Relay(1);
		}
		if(Relayflag == 1)         //当时间控制模式下继电器处于吸合状态时，判断是否到达5秒，到达则关闭继电器
		{
			if(Ds1302_Time[0] == 0x05)
			{
				Relay(0);
			}
		}
	}
	
}


void ShowMode()
{
		if(keyflag == 0)
		{
			Led_Temp();
		}
		else if(keyflag == 1)
		{
			Led_Time();
		}
		else if(keyflag == 2)
		{
			Led_Parm();
		}
}

void Read_Data()
{
	if(flag500ms == 1)
	{
		flag500ms = 0;
		tempbuf = DS18B20_Read();
		
		if(tempbuf >= 400)       //防止DS18B20读取温度数据突变对继电器和数码管显示造成影响
		{
			temp = temp;
		}
		else
		{
			temp = tempbuf;
		}
	}
			
	if(flag100ms == 1)
	{		
		Ds1302_Read();
		Led_Ind();        //读取时间同时对Led指示灯进行操作，100ms控制一次L3达到闪烁效果
		flag100ms = 0;
	}

}




