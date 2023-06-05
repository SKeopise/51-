
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



bit flag_Pwm_Output = 0;






void SmgMenuMain()
{
	if(Menu_Mode == 0)
	{
		SmgMenuFreq();
	}
	else if(Menu_Mode == 1)
	{
		SmgMenuRH();
	}
	else if(Menu_Mode == 2)
	{
		SmgMenuDistence();
	}
	else if(Menu_Mode == 3)
	{
		SmgMenuParm();
	}
}

void LedDisplay()
{
	P0 = 0xFF;	
	if(Menu_Mode == 0)
	{
		LED1 = 0;
	}
	else if(Menu_Mode == 1)
	{
		LED2 = 0;
	}
	else if(Menu_Mode == 2)
	{
		LED3 = 0;
	}
	else if(Menu_Mode == 3)
	{
		if(Menu_Parm == 0)
		{
			LED1 = flag_Led_Flash;
		}
		else if(Menu_Parm == 1)
		{
			LED2 = flag_Led_Flash;
		}
		else if(Menu_Parm == 2)
		{
			LED3 = flag_Led_Flash;
		}		
	}
	
	if(NE555_Freq > Parm_Freq)
	{
		LED4 = 0;
		flag_Pwm_Output = 1;
	}
	else
	{
		flag_Pwm_Output = 0;
	}
	if(RH_Data > Parm_RH)
	{
		LED5 = 0;
	}
	if(Sonic_Data_Distence > Parm_Distence)
	{
		LED6 = 0;
	}
	
	if(flag_Clear_RelayCnt == 1)
	{
		LED8 = 0;
	}
	
	HC138Set(4);	
	HC138Set(0);
}

void SmgMenuParm()
{
	SmgClear();
	Led_Buff[0] = 0x8C;
	if(Menu_Parm == 0)
	{
		Led_Buff[1] = Led_Number[1]; 
		
		if(Parm_Freq_Buf >= 10000)
		{
			Led_Buff[5] = Led_Number[(Parm_Freq_Buf/10000)%10];
		}
		Led_Buff[6] = Led_Number[(Parm_Freq_Buf/1000)%10] & 0x7F;
		Led_Buff[7] = Led_Number[(Parm_Freq_Buf/100)%10];
	}
	else if(Menu_Parm == 1)
	{
		Led_Buff[1] = Led_Number[2];
		Led_Buff[6] = Led_Number[(Parm_RH_Buf/10)%10];
		Led_Buff[7] = Led_Number[(Parm_RH_Buf)%10];		
	}
	else if(Menu_Parm == 2)
	{
		Led_Buff[1] = Led_Number[3];
		Led_Buff[6] = Led_Number[(Parm_Distence_Buf/100)%10] & 0x7F;
		Led_Buff[7] = Led_Number[(Parm_Distence_Buf/10)%10];			
	}	
}

void SmgMenuDistence()
{
	SmgClear();
	Led_Buff[0] = 0x88;	
	
	if(distence_mode == 0)
	{
		if(Sonic_Data_Distence >= 100)
		{
			Led_Buff[5] = Led_Number[(Sonic_Data_Distence/100)%10];			
		}
		if(Sonic_Data_Distence >= 10)
		{
			Led_Buff[6] = Led_Number[(Sonic_Data_Distence/10)%10];			
		}
		Led_Buff[7] = Led_Number[(Sonic_Data_Distence)%10];		
	}
	else
	{
		Led_Buff[5] = Led_Number[(Sonic_Data_Distence/100)%10] & 0x7F;
		Led_Buff[6] = Led_Number[(Sonic_Data_Distence/10)%10];
		Led_Buff[7] = Led_Number[(Sonic_Data_Distence)%10];	
	}
}


void SmgMenuRH()
{
	Led_Buff[0] = 0x89;
	Led_Buff[1] = 0xFF;
	Led_Buff[2] = 0xFF;
	Led_Buff[3] = 0xFF;
	Led_Buff[4] = 0xFF;
	Led_Buff[5] = 0xFF;
	
	Led_Buff[6] = Led_Number[(RH_Data/10)%10];
	Led_Buff[7] = Led_Number[(RH_Data)%10];	
}

void SmgMenuFreq()
{
	SmgClear();
	Led_Buff[0] = 0x8E;
	
	if(freq_mode == 0)
	{
		if(NE555_Freq >= 100000)
		{
			Led_Buff[2] = Led_Number[(NE555_Freq/100000)%10];			
		}
		if(NE555_Freq >= 10000)
		{
			Led_Buff[3] = Led_Number[(NE555_Freq/10000)%10];			
		}
		if(NE555_Freq >= 1000)
		{
			Led_Buff[4] = Led_Number[(NE555_Freq/1000)%10];			
		}	
		if(NE555_Freq >= 100)
		{
			Led_Buff[5] = Led_Number[(NE555_Freq/100)%10];			
		}	
		if(NE555_Freq >= 10)
		{
			Led_Buff[6] = Led_Number[(NE555_Freq/10)%10];			
		}	
		Led_Buff[7] = Led_Number[(NE555_Freq)%10];				
	}
	else
	{
		if(NE555_Freq >= 100000)
		{
			Led_Buff[4] = Led_Number[(NE555_Freq/100000)%10];			
		}
		if(NE555_Freq >= 10000)
		{
			Led_Buff[5] = Led_Number[(NE555_Freq/10000)%10];			
		}
		Led_Buff[6] = Led_Number[(NE555_Freq/1000)%10] & 0x7F;			
		Led_Buff[7] = Led_Number[(NE555_Freq/100)%10];				
	}
}


void SmgClear()
{
	Led_Buff[0] = 0xFF;
	Led_Buff[1] = 0xFF;
	Led_Buff[2] = 0xFF;
	Led_Buff[3] = 0xFF;
	Led_Buff[4] = 0xFF;
	Led_Buff[5] = 0xFF;
	Led_Buff[6] = 0xFF;	
	Led_Buff[7] = 0xFF;	
}


void SmgDisplay()
{
	static unsigned char i = 0;

	P0 = 0xFF;	
	HC138Set(7);
	HC138Set(0);
	
	P0 = 0x00;
	P0 = 0x01 << i;
	HC138Set(6);
	HC138Set(0);
	
	P0 = 0xFF;
	P0 = Led_Buff[i];	
	HC138Set(7);
	HC138Set(0);
	
	i++;
	i &= 0x07;	
}















