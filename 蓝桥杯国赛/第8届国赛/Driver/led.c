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

unsigned char Led_FlashCnt = 0;

bit flag_Led1 = 0;
bit flag_LedFlash = 1;


void LedDisplay()
{
	static unsigned char Led_Cnt = 0;
	
	if(flag_Led1 == 1)
	{
		Led_Cnt++;
		if(Led_Cnt >= 200)
		{
			Led_Cnt = 0;
			flag_LedFlash = ~flag_LedFlash;
			Led_FlashCnt++;
			if(Led_FlashCnt >= 20)
			{
				Led_FlashCnt = 0;
				flag_Led1 = 0;
				flag_LedFlash = 1;
			}			
		}
	}	
	
	P0 = 0xFF;	
	if(flag_Led1 == 1)
	{
		LED1 = flag_LedFlash;
	}
	
	if(Menu_Mode == 1)
	{
		LED8 = 0;
	}
	else if(Menu_Mode == 2)
	{
		LED7 = 0;
	}
	
	HC138Set(4);
	HC138Set(0);
}

void SmgMenuMain()
{
	if(Menu_Mode == 0)
	{
		SmgMenuDistence();
	}
	else if(Menu_Mode == 1)
	{
		SmgMenuBackup();
	}
	else
	{
		SmgMenuParm();
	}
	
}

void SmgMenuParm()
{
	Led_Buff[0] = 0x8E;	
	Led_Buff[1] = Led_Number[10];
	Led_Buff[2] = Led_Number[10];	
	Led_Buff[3] = Led_Number[10];
	Led_Buff[4] = Led_Number[10];
	
	if(Parm_Distence_Buf >= 100)
	{
		Led_Buff[5] = Led_Number[(Parm_Distence_Buf/100)%10];
	}
	else
	{
		Led_Buff[5] = Led_Number[10];
	}
	if(Parm_Distence_Buf >= 10)
	{
		Led_Buff[6] = Led_Number[(Parm_Distence_Buf/10)%10];
	}
	else
	{
		Led_Buff[6] = Led_Number[10];
	}
	Led_Buff[7] = Led_Number[(Parm_Distence_Buf)%10];			
}

void SmgMenuBackup()
{
	Led_Buff[0] = Led_Number[(DataBackup_Cnt/10)%10];
	Led_Buff[1] = Led_Number[(DataBackup_Cnt)%10];	
	Led_Buff[2] = Led_Number[10];	
	Led_Buff[3] = Led_Number[10];
	Led_Buff[4] = Led_Number[10];

	if(Sonic_HistoryData[DataBackup_Cnt-1] >= 100)
	{
		Led_Buff[5] = Led_Number[(Sonic_HistoryData[DataBackup_Cnt-1]/100)%10];
	}
	else
	{
		Led_Buff[5] = Led_Number[10];
	}
	if(Sonic_HistoryData[DataBackup_Cnt-1] >= 10)
	{
		Led_Buff[6] = Led_Number[(Sonic_HistoryData[DataBackup_Cnt-1]/10)%10];
	}
	else
	{
		Led_Buff[6] = Led_Number[10];
	}
	Led_Buff[7] = Led_Number[(Sonic_HistoryData[DataBackup_Cnt-1])%10];
}

void SmgMenuDistence()
{
	Led_Buff[1] = Led_Number[10];
	
	if(flag_DataShowMode == 0)
	{
		Led_Buff[0] = Led_Number[0];
		
		if(Distence_Cnt >= 2)
		{
			if(Sonic_HistoryData[Distence_Cnt - 2] >= 100)
			{
				Led_Buff[2] = Led_Number[(Sonic_HistoryData[Distence_Cnt - 2]/100)%10];
			}
			else
			{
				Led_Buff[2] = Led_Number[10];
			}
			if(Sonic_HistoryData[Distence_Cnt - 2] >= 10)
			{
				Led_Buff[3] = Led_Number[(Sonic_HistoryData[Distence_Cnt - 2]/10)%10];
			}
			else
			{
				Led_Buff[3] = Led_Number[10];
			}
			Led_Buff[4] = Led_Number[(Sonic_HistoryData[Distence_Cnt - 2])%10];
		}
		else
		{
			if(Sonic_HistoryData[8 + Distence_Cnt] >= 100)
			{
				Led_Buff[2] = Led_Number[(Sonic_HistoryData[8 + Distence_Cnt]/100)%10];
			}
			else
			{
				Led_Buff[2] = Led_Number[10];
			}
			if(Sonic_HistoryData[8 + Distence_Cnt] >= 10)
			{
				Led_Buff[3] = Led_Number[(Sonic_HistoryData[8 + Distence_Cnt]/10)%10];
			}	
			else
			{
				Led_Buff[3] = Led_Number[10];
			}
			Led_Buff[4] = Led_Number[(Sonic_HistoryData[8 + Distence_Cnt])%10];			
		}
	}
	else
	{
		Led_Buff[0] = Led_Number[1];

		if(Distence_LastIncNow >= 100)
		{
			Led_Buff[2] = Led_Number[(Distence_LastIncNow/100)%10];
		}
		else
		{
			Led_Buff[2] = Led_Number[10];
		}
		if(Distence_LastIncNow >= 10)
		{
			Led_Buff[3] = Led_Number[(Distence_LastIncNow/10)%10];
		}
		else
		{
			Led_Buff[3] = Led_Number[10];
		}
		Led_Buff[4] = Led_Number[(Distence_LastIncNow)%10];		
	}

	
	if(Sonic_Distence >= 100)
	{
		Led_Buff[5] = Led_Number[(Sonic_Distence/100)%10];
	}
	else
	{
		Led_Buff[5] = Led_Number[10];
	}
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



void SmgDisplay()
{
	static unsigned char i = 0;
	
	P0 = 0xFF;
	HC138Set(7);
	HC138Set(0);
	
	P0 = 0x01 << i;
	HC138Set(6);
	HC138Set(0);	
	
	P0 = Led_Buff[i];
	HC138Set(7);
	HC138Set(0);	
	
	i++;
	i &= 0x07;
}








