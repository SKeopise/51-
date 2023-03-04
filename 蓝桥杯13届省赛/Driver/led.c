#include "led.h"


unsigned char code LedNumber[] = {                          //真值表
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90
};

unsigned char LedBuff[] = {                   //数码管缓存区
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};

unsigned char Tparm = 23;     //温度参数
bit TimeMod = 0;              //时间控制模式，为0时显示小时与分钟，为1时显示分和秒


void Led_Ind()                //led指示灯操作函数
{
	static unsigned char Timeflag = 0;
	
	P0 = 0xFF;
	selectOutput(4);
	if((Ds1302_Time[1] == 0) && (Ds1302_Time[0] == 0))
	{
		LED1 = 0;
		if(Timeflag == 0)
		{
			Timeflag = 1;
		}
	}
	if(Timeflag == 1)
	{
		if(Ds1302_Time[0] == 0x05)
		{
			LED1 = 1;
			Timeflag = 0;
		}
		else
		{
			LED1 = 0;
		}
	}
	
	if(workmode == 0)
	{
		LED2 = 0;
	}
	else
	{
		LED2 = 1;
	}
	
	if(Relayflag == 1)
	{
		LED3 = ~LED3flag;
		LED3flag = LED3;
	}
	else
	{
		LED3 = 1;
		LED3flag = LED3;
	}
	
	selectOutput(0);
}


// 显示指定编号的数码管
void displayDigit()
{
	static unsigned char i=0;
		
	selectOutput(6);
	P0 = 0X00;	
	selectOutput(0);	
	
    // 显示该数码管
	P0 = 0xFF;
    selectOutput(7);
    P0 = LedBuff[i];
	selectOutput(0);
	
	selectOutput(6);
	P0 = 0X01 << i;	
	selectOutput(0);

	i++;
	if(i > 7)
	{
		i=0;
	}
	
}


void Led_Temp()         //温度界面，U1
{
	LedBuff[0] = 0xC1;
	LedBuff[1] = LedNumber[1];
	
	LedBuff[2] = 0xFF;
	LedBuff[3] = 0xFF;
	LedBuff[4] = 0xFF;
	
	LedBuff[5] = LedNumber[(temp/100)%10];
	LedBuff[6] = LedNumber[(temp/10)%10]&0x7F;
	LedBuff[7] = LedNumber[temp%10];	
}

void Led_Time()                    //时间界面，U2
{
	LedBuff[0] = 0xC1;
	LedBuff[1] = LedNumber[2];
	
	LedBuff[2] = 0xFF;
	if(TimeMod == 0)
	{
		LedBuff[3] = LedNumber[Ds1302_Time[2]>>4];
		LedBuff[4] = LedNumber[Ds1302_Time[2]&0x0F];
		
		LedBuff[5] = 0xBF;
		LedBuff[6] = LedNumber[Ds1302_Time[1]>>4];
		LedBuff[7] = LedNumber[Ds1302_Time[1]&0x0F];
	}
	else
	{
		LedBuff[3] = LedNumber[Ds1302_Time[1]>>4];
		LedBuff[4] = LedNumber[Ds1302_Time[1]&0x0F];
		
		LedBuff[5] = 0xBF;
		LedBuff[6] = LedNumber[Ds1302_Time[0]>>4];
		LedBuff[7] = LedNumber[Ds1302_Time[0]&0x0F];		
	}
}

void Led_Parm()                    //参数设置界面，U3
{
	LedBuff[0] = 0xC1;
	LedBuff[1] = LedNumber[3];
	
	LedBuff[2] = 0xFF;
	LedBuff[3] = 0xFF;
	LedBuff[4] = 0xFF;
	LedBuff[5] = 0xFF;
	
	LedBuff[6] = LedNumber[(Tparm/10)%10];
	LedBuff[7] = LedNumber[Tparm%10];
}






