#include "led.h"


code unsigned char Led_Number[] =
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

unsigned char Led_Buff[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};









void SmgMenuMain()
{
	if(Menu_Mode == 0)
	{
		if(Menu_Data == 0)
		{
			SmgMenuDataTemp();
		}
		else if(Menu_Data == 1)
		{
			SmgMenuDataDistence();
		}
		else
		{
			SmgMenuDataParmCnt();
		}
	}
	else
	{
		SmgMenuParm();
	}
}

void LedDisplay()
{
	P0 = 0xFF;
	HC138Set(4);
	
	if(Temp_Data > ParmData_Temp)
	{
		LED1 = 0;
	}
	
	if(Sonic_Distence < ParmData_Distence)
	{
		LED2 = 0;
	}
	
	if(DAC_Mode == 0)
	{
		LED3 = 0;
	}
	
	HC138Set(0);
}

void SmgMenuParm()
{
	Led_Buff[0] = 0x92;		
	Led_Buff[1] = Led_Number[10];
	Led_Buff[2] = Led_Number[10];	
	Led_Buff[4] = Led_Number[10];
	Led_Buff[5] = Led_Number[10];		
	if(Menu_Parm == 0)
	{
		Led_Buff[3] = Led_Number[4];	
		if(ParmData_Temp_Buf >= 1000)
		{
			Led_Buff[6] = Led_Number[(ParmData_Temp_Buf/1000)%10];			
		}
		else
		{
			Led_Buff[6] = Led_Number[10];			
		}
		Led_Buff[7] = Led_Number[(ParmData_Temp_Buf/100)%10];
	}
	else
	{
		Led_Buff[3] = Led_Number[5];	
		if(ParmData_Distence_Buf >= 10)
		{
			Led_Buff[6] = Led_Number[(ParmData_Distence_Buf/10)%10];
		}
		else
		{
			Led_Buff[6] = Led_Number[10];
		}
		Led_Buff[7] = Led_Number[(ParmData_Distence_Buf)%10];
	}
}


void SmgMenuDataParmCnt()
{
	Led_Buff[0] = 0x98;	
	Led_Buff[1] = Led_Number[10];
	Led_Buff[2] = Led_Number[10];	
	
	if(Parm_ChangCnt >= 10000)
	{
		Led_Buff[3] = Led_Number[(Parm_ChangCnt/10000)%10];		
	}
	else
	{
		Led_Buff[3] = Led_Number[10];		
	}
	if(Parm_ChangCnt >= 1000)
	{
		Led_Buff[4] = Led_Number[(Parm_ChangCnt/1000)%10];		
	}            
	else         
	{            
		Led_Buff[4] = Led_Number[10];		
	}	
	if(Parm_ChangCnt >= 100)
	{
		Led_Buff[5] = Led_Number[(Parm_ChangCnt/100)%10];		
	}
	else
	{
		Led_Buff[5] = Led_Number[10];		
	}	
	if(Parm_ChangCnt >= 10)
	{
		Led_Buff[6] = Led_Number[(Parm_ChangCnt/10)%10];		
	}
	else
	{
		Led_Buff[6] = Led_Number[10];		
	}	
	Led_Buff[7] = Led_Number[(Parm_ChangCnt)%10];
}

void SmgMenuDataDistence()
{
	Led_Buff[0] = 0xC7;	
	Led_Buff[1] = Led_Number[10];
	Led_Buff[2] = Led_Number[10];
	Led_Buff[3] = Led_Number[10];
	Led_Buff[4] = Led_Number[10];
	Led_Buff[5] = Led_Number[10];
	
	if(Sonic_Distence >= 10)
	{
		Led_Buff[6] = Led_Number[(Sonic_Distence/10)%10];		
	}
	else
	{
		Led_Buff[6] = Led_Number[10];		
	}
	Led_Buff[7] = Led_Number[(Sonic_Distence)%10];	
}


void SmgMenuDataTemp()
{
	Led_Buff[0] = 0x8e;	
	Led_Buff[1] = Led_Number[10];
	Led_Buff[2] = Led_Number[10];
	
	if(flag_TempMinus == 1)
	{
		Led_Buff[3] = 0xBF;		
	}
	else
	{
		Led_Buff[3] = Led_Number[10];		
	}
	
	if(Temp_Data >= 1000)
	{	
		Led_Buff[4] = Led_Number[(Temp_Data/1000)%10];			
	}
	else
	{
		Led_Buff[4] = Led_Number[10];
	}
	Led_Buff[5] = Led_Number[(Temp_Data/100)%10] & 0x7F;
	Led_Buff[6] = Led_Number[(Temp_Data/10)%10];
	Led_Buff[7] = Led_Number[(Temp_Data)%10];		
	
}



void SmgDisplay()
{
	static unsigned char i = 0;
	
	HC138Set(7);
	P0 = 0xFF;
	HC138Set(6);
	P0 = 0x01 << i;
	HC138Set(7);
	P0 = 0xFF;
	P0 = Led_Buff[i];	
	HC138Set(0);
	
	i++;
	i &= 0x07;
}







