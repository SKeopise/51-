

#include <main.h>

unsigned char state,EnterCnt; 					     //״ָ̬ʾ������Mod1Ϊ�������룬mod0Ϊ��������
																						//state,0Ϊ������ת��1Ϊ������ת��2Ϊȷ�����룬3Ϊ����״̬��4Ϊ����״̬
                                            //Enter��¼�����������

void main()
{
  EA = 1;
	ConfigTimer0(1);
	InitLcd1602();
	
	if(Read_Password())
	{
		state = 0;
	}
	else
	{
		state = 1;
	}
	Enter_Init();
	Fill_Number(PasswordBuf,'\0',MAX_LEN);
	Fill_Number(Password_dat1,'\0',MAX_LEN);
	cntBuf = 0;


	while(1)
	{
		KeyDriver();
	}
}

void Enter_Init()
{
	LcdWriteCmd(0x01); //����
	if(state == 0)
	{		
		LcdShowStr(0,0,"Enter Password ");
		LcdShowStr(0,1,"                 ");	
	}
	else if(state == 1)
	{
		LcdShowStr(0,0,"Set Password   ");
		LcdShowStr(0,1,"                 ");		
	}
	else if(state == 2)
	{
			LcdShowStr(0,0,"Enter again     ");
			LcdShowStr(0,1,"                ");	
	}
	else if(state == 3)
	{
			LcdShowStr(0,0,"Press Enter  ");
			LcdShowStr(0,1,"Reset Password  ");		
	}
	else if(state == 4)
	{
			LcdShowStr(0,0,"WARRING        ");
			LcdShowStr(0,1,"Enter too much ");		
	}
}

void InterruptTimer0() interrupt 1
{
	TH0 = T0RH;
	TL0 = T0RL;

	KeyScan();
}


void Time1() interrupt 3
{
	PT1 = 1; //���ö�ʱ��T1�ж�Ϊ�����ȼ�����ֹ������Ƶ�ʽ��Ͳ������ҵ�������
		
		TH1 = T1RH;
		TL1 = T1RL;
		BUZZ = ~BUZZ;
	
}






















