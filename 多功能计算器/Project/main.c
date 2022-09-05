

#include <main.h>





void main()
{
	
	Led_Display_init();   //����ܳ�ʼ��                      
	interrupt_init();     //�жϳ�ʼ��
	Led_Display_show_0(); //�ϵ�Ĭ����ʾ0
	
	ConfigTimer0(1);	//��ʼ����ʱ��T0����ʱ1ms
	
	while(1)
	{
		if(SnakeGame == 0)   //��̬Ĭ��ģʽ
		{
			
			if(StopwatchRefresh)   //�����
			{
				StopwatchRefresh = 0;
				StopwatchDisplay();
			}		

				KeyDriver();     //��������
		}
		else//����̰������Ϸ����
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
	
		if(Led_ONF == 0)     //Ĭ���밴�����ּ�1ʱ����ʾ����������ģʽ��
		{
			Led_Display();
		}
		else if(Led_ONF == 1)   //�������ּ�2ʱ���ر�����ܣ�����ʾ����ģʽ��
		{
			Led_Mode();
		}
		else if(Led_ONF == 2)    //���ּ�3ȫ����ʾ
		{
			if(cnt%2 == 0)       //������ʾ�����������Դﵽ��̬ˢ�µ�Ŀ��
				{
					Led_Display();
				}
				else
				{
					Led_Lattice();
				}	
		}

	KeyScan();              //����ɨ��
		
		tmr10ms++;
		if(tmr10ms >= 10)    //����ʱ
		{
			tmr10ms = 0;
			StopwatchCount();
		}
	
}







void Time1() interrupt 3
{
	PT1 = 1; //���ö�ʱ��T1�ж�Ϊ�����ȼ�����ֹ������Ƶ�ʽ��Ͳ������ҵ�������
		
		TH1 = T1RH;
		TL1 = T1RL;
		BUZZ = ~BUZZ;
	
}


































