

#include <main.h>

unsigned char state,EnterCnt; 					     //状态指示变量，Mod1为设置密码，mod0为输入密码
																						//state,0为输入跳转，1为设置跳转，2为确认密码，3为解锁状态，4为锁定状态
                                            //Enter记录输入密码次数

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
	LcdWriteCmd(0x01); //清屏
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
	PT1 = 1; //设置定时器T1中断为高优先级，防止蜂鸣器频率降低波形紊乱导致异响
		
		TH1 = T1RH;
		TL1 = T1RL;
		BUZZ = ~BUZZ;
	
}






















