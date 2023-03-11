#include "led.h"



unsigned char code Led_Number[] = {
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF
};

unsigned char Led_Buff[] = {
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

bit Smg_Show_Mode = 0;              			//显示模式切换
unsigned char Smg_Data_Mode = 0;    		 	//数据显示模式下，显示数据切换
unsigned char Smg_Parm_Mode = 0;             //参数显示模式下，参数类型显示切换

unsigned char Timer_Parm = 17;
unsigned int Temp_Parm = 25;
unsigned char Led_Parm = 4;


void LedDisplay()
{
	P0 = 0xFF;
	
	if(flagLed1 == 1)
	{
		LED0 = 0;
	}
	if(TempData < (Temp_Parm*10))
	{
		LED1 = 0;
	}
	if(Light_Dark == 1)
	{
		if(flag3S >= 30)
		{
			LED2 = 0;
		}
		switch(Led_Parm)
		{
			case 4: LED3 = 0;break;
			case 5: LED4 = 0;break;
			case 6: LED5 = 0;break;
			case 7: LED6 = 0;break;
			case 8: LED7 = 0;break;
			default: break;
		}
	}
	HC138(4);
	HC138(0);	
}

void SmgShowDriver()
{
	if(Smg_Show_Mode == 0)
	{
		SmgDataSelect();
	}
	else
	{
		SmgParmSelect();
	}
}

void SmgDataSelect()
{
	if(Smg_Data_Mode == 0)
	{
		SmgDs1302Time();
	}
	else if(Smg_Data_Mode == 1)
	{
		SmgDS18B20Temp();
	}
	else if(Smg_Data_Mode == 2)
	{
		SmgLightDark();
	}
}

void SmgParmSelect()
{
	if(Smg_Parm_Mode == 0)
	{
		SmgTimerParm();
	}
	else if(Smg_Parm_Mode == 1)
	{
		SmgTempParm();
	}
	else if(Smg_Parm_Mode == 2)
	{
		SmgLedParm();
	}	
}


void SmgDs1302Time()
{
	Led_Buff[0] = Led_Number[TimerData[2]>>4];
	Led_Buff[1] = Led_Number[TimerData[2]&0x0F];
	
	Led_Buff[2] = 0xBF;
	
	Led_Buff[3] = Led_Number[TimerData[1]>>4];
	Led_Buff[4] = Led_Number[TimerData[1]&0x0F];
	
	Led_Buff[5] = 0xBF;
	
	Led_Buff[6] = Led_Number[TimerData[0]>>4];
	Led_Buff[7] = Led_Number[TimerData[0]&0x0F];	
}

void SmgDS18B20Temp()
{
	Led_Buff[0] = 0xC6;
	
	Led_Buff[1] = Led_Number[10];	
	Led_Buff[2] = Led_Number[10];	
	Led_Buff[3] = Led_Number[10];
	Led_Buff[4] = Led_Number[10];
	
	Led_Buff[5] = Led_Number[(TempData/100)%10];	
	Led_Buff[6] = Led_Number[(TempData/10)%10] & 0x7F;
	Led_Buff[7] = Led_Number[TempData%10];	
}

void SmgLightDark()
{
	Led_Buff[0] = 0x86;
	
	Led_Buff[1] = Led_Number[10];
	
	Led_Buff[2] = Led_Number[(RD1_Vin/100)%10] & 0x7F;	
	Led_Buff[3] = Led_Number[(RD1_Vin/10)%10];
	Led_Buff[4] = Led_Number[RD1_Vin%10];
	
	Led_Buff[5] = Led_Number[10];	
	Led_Buff[6] = Led_Number[10];
	
	if(Light_Dark == 0)
	{
		Led_Buff[7] = Led_Number[0];	
	}
	else
	{
		Led_Buff[7] = Led_Number[1];
	}
}


void SmgTimerParm()
{
	Led_Buff[0] = 0x8C;
	Led_Buff[1] = Led_Number[1];
	
	Led_Buff[2] = Led_Number[10];	
	Led_Buff[3] = Led_Number[10];	
	Led_Buff[4] = Led_Number[10];
	Led_Buff[5] = Led_Number[10];
	
	if(Smg_Show_Mode == 0)
	{
		Led_Buff[6] = Led_Number[(Timer_Parm/10)%10];
		Led_Buff[7] = Led_Number[Timer_Parm%10];
	}
	else
	{
		Led_Buff[6] = Led_Number[(Parm_Buff/10)%10];
		Led_Buff[7] = Led_Number[Parm_Buff%10];		
	}	
}

void SmgTempParm()
{
	Led_Buff[0] = 0x8C;
	Led_Buff[1] = Led_Number[2];
	
	Led_Buff[2] = Led_Number[10];	
	Led_Buff[3] = Led_Number[10];	
	Led_Buff[4] = Led_Number[10];
	Led_Buff[5] = Led_Number[10];
	
	if(Smg_Show_Mode == 0)
	{
		Led_Buff[6] = Led_Number[(Temp_Parm/10)%10];
		Led_Buff[7] = Led_Number[Temp_Parm%10];		
	}
	else
	{
		Led_Buff[6] = Led_Number[(Parm_Buff/10)%10];
		Led_Buff[7] = Led_Number[Parm_Buff%10];			
	}
}

void SmgLedParm()
{
	Led_Buff[0] = 0x8C;
	Led_Buff[1] = Led_Number[3];
	
	Led_Buff[2] = Led_Number[10];	
	Led_Buff[3] = Led_Number[10];	
	Led_Buff[4] = Led_Number[10];
	Led_Buff[5] = Led_Number[10];
	Led_Buff[6] = Led_Number[10];
	
	if(Smg_Show_Mode == 0)
	{
		Led_Buff[7] = Led_Number[Led_Parm%10];		
	}
	else
	{
		Led_Buff[7] = Led_Number[Parm_Buff%10];
	}
}


void SmgDisplay()
{
	static unsigned char i = 0;
	
	P0 = 0xFF;
	HC138(7);
	P0 = Led_Buff[i];
	HC138(0);
	
	P0 = 0x00;
	HC138(6);
	P0 = 0x01 << i;
	HC138(0);
	
	i++;
	if(i > 7)
	{
		i = 0;
	}	
}






















