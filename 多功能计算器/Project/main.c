

#include <main.h>





void main()
{
	
	Led_Display_init();   //数码管初始化                      
	interrupt_init();     //中断初始化
	Led_Display_show_0(); //上电默认显示0
	
	ConfigTimer0(1);	//初始化定时器T0，定时1ms
	
	while(1)
	{
		if(SnakeGame == 0)   //常态默认模式
		{
			
			if(StopwatchRefresh)   //秒表开关
			{
				StopwatchRefresh = 0;
				StopwatchDisplay();
			}		

				KeyDriver();     //按键驱动
		}
		else//调用贪吃蛇游戏程序
		{	
		  Snake_while();
		}
		
		
	}
	
}


void Time0() interrupt 1
{
	static unsigned char cnt = 0;
	static unsigned char tmr10ms = 0;
	
		TH0 = T0RH;
		TL0 = T0RL;	
	
		cnt++;
	
		if(Led_ONF == 0)     //默认与按下数字键1时，显示数码管与键盘模式灯
		{
			Led_Display();
		}
		else if(Led_ONF == 1)   //按下数字键2时，关闭数码管，仅显示键盘模式灯
		{
			Led_Mode();
		}
		else if(Led_ONF == 2)    //数字键3全部显示
		{
			if(cnt%2 == 0)       //交替显示数码管与点阵以达到动态刷新的目的
				{
					Led_Display();
				}
				else
				{
					Led_Lattice();
				}	
		}

	KeyScan();              //按键扫描
		
		tmr10ms++;
		if(tmr10ms >= 10)    //秒表计时
		{
			tmr10ms = 0;
			StopwatchCount();
		}
	
}







void Time1() interrupt 3
{
	PT1 = 1; //设置定时器T1中断为高优先级，防止蜂鸣器频率降低波形紊乱导致异响
		
		TH1 = T1RH;
		TL1 = T1RL;
		BUZZ = ~BUZZ;
	
}


































