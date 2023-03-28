
#include "led.h"

//数码管真值表
unsigned char code Led_Number[] =
{
	0xc0, //0
	0xf9, //1
	0xa4, //2
	0xb0, //3
	0x99, //4
	0x92, //5
	0x82, //6
	0xf8, //7
	0x80, //8
	0x90, //9
	0xFF
};

unsigned char Led_Buff[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};



bit flag_1s = 0;

bit flag_200ms = 0;
unsigned char flag_5s = 0;

//LED指示灯显示，如果Flag_Warring_Clock为1，则LED1以0.2秒为间隔闪烁，持续5秒钟
void LedShow()
{
	P0 = 0xFF;
	if(Flag_Warring_Clock == 1)
	{
		if(flag_5s < 50)
		{
			if(flag_200ms == 0)
			{
				LED1 = 0;
			}
			else
			{
				LED1 = 1;
			}
		}
		else
		{
			flag_5s = 0;
			Flag_Warring_Clock = 0;
		}
	}
	HC138Set(4);
	HC138Set(0);
}


void SmgShow()
{
	if((Temp_Show == 1)&&(Clock_Warring_Time_Set == 0)&&(Clock_Data_Set == 0))
	{
		SmgShowTemp();
	}
	else if(Clock_Warring_Time_Set != 0)
	{
		SmgShowTimeWarring();
	}
	else
	{
		SmgShowTime();
	}
}

void SmgShowTimeWarring()
{
	if(Clock_Warring_Time_Set == 1)
	{
		if(flag_1s == 0)
		{
			Led_Buff[0] = Led_Number[(Timer_Warring[2]/10)%10];
			Led_Buff[1] = Led_Number[Timer_Warring[2]%10];
		}
		else
		{
			Led_Buff[0] = Led_Number[10];
			Led_Buff[1] = Led_Number[10];			
		}
	}
	else
	{
		Led_Buff[0] = Led_Number[(Timer_Warring[2]/10)%10];
		Led_Buff[1] = Led_Number[Timer_Warring[2]%10];		
	}
	
	Led_Buff[2] = 0xBF;
	
	if(Clock_Warring_Time_Set == 2)
	{
		if(flag_1s == 0)
		{
			Led_Buff[3] = Led_Number[(Timer_Warring[1]/10)%10];
			Led_Buff[4] = Led_Number[Timer_Warring[1]%10];
		}
		else
		{
			Led_Buff[3] = Led_Number[10];
			Led_Buff[4] = Led_Number[10];			
		}
	}
	else
	{
		Led_Buff[3] = Led_Number[(Timer_Warring[1]/10)%10];
		Led_Buff[4] = Led_Number[Timer_Warring[1]%10];		
	}
	
	Led_Buff[5] = 0xBF;
	
	if(Clock_Warring_Time_Set == 3)
	{
		if(flag_1s == 0)
		{
			Led_Buff[6] = Led_Number[(Timer_Warring[0]/10)%10];
			Led_Buff[7] = Led_Number[Timer_Warring[0]%10];
		}
		else
		{
			Led_Buff[6] = Led_Number[10];
			Led_Buff[7] = Led_Number[10];			
		}
	}
	else
	{
		Led_Buff[6] = Led_Number[(Timer_Warring[0]/10)%10];
		Led_Buff[7] = Led_Number[Timer_Warring[0]%10];	
	}	
}

void SmgShowTemp()
{
	Led_Buff[0] = Led_Number[10];
	Led_Buff[1] = Led_Number[10];
	Led_Buff[2] = Led_Number[10];
	Led_Buff[3] = Led_Number[10];
	Led_Buff[4] = Led_Number[10];

	Led_Buff[5] = Led_Number[(Temp_Data/10)%10];
	Led_Buff[6] = Led_Number[Temp_Data%10];
	Led_Buff[7] = 0xC6;	
}

void SmgShowTime()
{
	if(Clock_Data_Set == 1)
	{
		if(flag_1s == 0)
		{
			Led_Buff[0] = Led_Number[TimerData[2]>>4];
			Led_Buff[1] = Led_Number[TimerData[2]&0x0F];
		}
		else
		{
			Led_Buff[0] = Led_Number[10];
			Led_Buff[1] = Led_Number[10];			
		}
	}
	else
	{
		Led_Buff[0] = Led_Number[TimerData[2]>>4];
		Led_Buff[1] = Led_Number[TimerData[2]&0x0F];
	}
	
	Led_Buff[2] = 0xBF;
	
	if(Clock_Data_Set == 2)
	{
		if(flag_1s == 0)
		{
			Led_Buff[3] = Led_Number[TimerData[1]>>4];
			Led_Buff[4] = Led_Number[TimerData[1]&0x0F];
		}
		else
		{
			Led_Buff[3] = Led_Number[10];
			Led_Buff[4] = Led_Number[10];			
		}
	}
	else
	{
		Led_Buff[3] = Led_Number[TimerData[1]>>4];
		Led_Buff[4] = Led_Number[TimerData[1]&0x0F];	
	}
	
	Led_Buff[5] = 0xBF;
	
	if(Clock_Data_Set == 3)
	{
		if(flag_1s == 0)
		{
			Led_Buff[6] = Led_Number[TimerData[0]>>4];
			Led_Buff[7] = Led_Number[TimerData[0]&0x0F];
		}
		else
		{
			Led_Buff[6] = Led_Number[10];
			Led_Buff[7] = Led_Number[10];			
		}
	}
	else
	{
		Led_Buff[6] = Led_Number[TimerData[0]>>4];
		Led_Buff[7] = Led_Number[TimerData[0]&0x0F];	
	}
}


void SmgDisplay()
{
	static unsigned char i = 0;
	
	P0 = 0x00;
	HC138Set(6);
	P0 = 0x01 << i;
	HC138Set(0);
	
	P0 = 0xFF;
	HC138Set(7);
	P0 = Led_Buff[i];
	HC138Set(0);
	
	i++;
	if(i>7)
	{
		i = 0;
	}
}














