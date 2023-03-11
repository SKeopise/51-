#include "led.h"


unsigned char Led_Running_Code = 0;

unsigned char Led_Running_Mode = 1;

unsigned char code Led_Running_Type[] = {0x7E,0xBD,0xDB,0xE7};

unsigned char code Led_Number[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF};

unsigned char Led_Buff[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

unsigned char Smg_Mode = 0;

unsigned char flag08s = 0;

bit flag08s_change = 0;

bit Led_Open = 0;





void SmgControl()
{
	if(Smg_Mode == 0)
	{
		SmgMode0();
	}
	else if(Smg_Mode == 1)
	{
		SmgMode1();
	}
	else if(Smg_Mode == 2)
	{
		SmgMode2();
	}
	
}


void LedControl()
{
	if(Led_Running_Mode == 1)
	{
		LedMode1();
		Led_Timer = Led_Timer_Buff_Mode[0];
	}
	else if(Led_Running_Mode == 2)
	{
		LedMode2();
		Led_Timer = Led_Timer_Buff_Mode[1];
	}
	else if(Led_Running_Mode == 3)
	{
		LedMode3();
		Led_Timer = Led_Timer_Buff_Mode[2];
	}
	else if(Led_Running_Mode == 4)
	{
		LedMode4();
		Led_Timer = Led_Timer_Buff_Mode[3];
	}
	
	if(Led_Running_Open == 1)
	{	
		if(Led_Change == 1)
		{
			Led_Change = 0;
			
			if((Led_Running_Mode == 1) || (Led_Running_Mode == 2))
			{
				Led_Running_Code++;
				if(Led_Running_Code > 7)
				{
					Led_Running_Code = 0;
					Led_Running_Mode++;
				}
			}
			else if(Led_Running_Mode == 3)
			{
				Led_Running_Code++;
				if(Led_Running_Code > 3)
				{
					Led_Running_Code = 3;
					Led_Running_Mode++;
				}				
			}
			else if(Led_Running_Mode == 4)
			{
				if(Led_Running_Code > 0)
				{
					Led_Running_Code--;
				}
				else
				{
					Led_Running_Code = 0;
					Led_Running_Mode = 1;
				}
			}
		}
	}
}



void SmgMode0()
{
	Led_Buff[0] = Led_Number[10];
	Led_Buff[1] = Led_Number[10];
	Led_Buff[2] = Led_Number[10];
	Led_Buff[3] = Led_Number[10];
	Led_Buff[4] = Led_Number[10];
	Led_Buff[5] = Led_Number[10];
	
	if(Pwm_Mode_Show == 0)
	{
		Led_Buff[6] = Led_Number[10];
		Led_Buff[7] = Led_Number[10];	
	}
	else
	{
		Led_Buff[6] = 0xBF;
		Led_Buff[7] = Led_Number[(Pwm_Mode/25)%10];		
	}
}


void SmgMode1()
{
	if(flag08s_change == 0)
	{
		Led_Buff[0] = 0xBF;
		Led_Buff[1] = Led_Number[Led_Running_Mode_Buff];
		Led_Buff[2] = 0xBF;
	}
	else
	{
		Led_Buff[0] = Led_Number[10];
		Led_Buff[1] = Led_Number[10];
		Led_Buff[2] = Led_Number[10];		
	}
	
	Led_Buff[3] = Led_Number[10];
	
	if(Led_Timer_Buff >= 1000)
	{
		Led_Buff[4] = Led_Number[(Led_Timer_Buff/1000)%10];
	}
	else
	{
		Led_Buff[4] = Led_Number[10];
	}
	
	Led_Buff[5] = Led_Number[(Led_Timer_Buff/100)%10];
	Led_Buff[6] = Led_Number[(Led_Timer_Buff/10)%10];
	Led_Buff[7] = Led_Number[Led_Timer_Buff%10];	
}

void SmgMode2()
{
	Led_Buff[0] = 0xBF;
	Led_Buff[1] = Led_Number[Led_Running_Mode_Buff];
	Led_Buff[2] = 0xBF;
	
	Led_Buff[3] = Led_Number[10];
	
	if(flag08s_change == 0)
	{
		if(Led_Timer_Buff >= 1000)
		{
			Led_Buff[4] = Led_Number[(Led_Timer_Buff/1000)%10];
		}
		else
		{
			Led_Buff[4] = Led_Number[10];
		}
		
		Led_Buff[5] = Led_Number[(Led_Timer_Buff/100)%10];
		Led_Buff[6] = Led_Number[(Led_Timer_Buff/10)%10];
		Led_Buff[7] = Led_Number[Led_Timer_Buff%10];	
	}
	else
	{
		Led_Buff[4] = Led_Number[10];
		Led_Buff[5] = Led_Number[10];
		Led_Buff[6] = Led_Number[10];
		Led_Buff[7] = Led_Number[10];		
	}
}

void SmgDisplay()
{
	static unsigned char i = 0;
	
	P0 = 0x00;
	HC138(6);
	P0 = 0x01<<i;
	HC138(0);
	P0 = 0xFF;
	HC138(7);
	P0 = Led_Buff[i];
	HC138(0);

	i++;
	if(i > 7)
	{
		i = 0;
	}
}




void LedMode1()
{
	P0 = 0xFF;
	HC138(4);
	if(Led_Open == 1)
	{
		P0 = ~(0x01 << Led_Running_Code);	
	}		
	HC138(0);
}

void LedMode2()
{
	P0 = 0xFF;
	HC138(4);
	if(Led_Open == 1)
	{
		P0 = ~(0x80 >> Led_Running_Code);	
	}		
	HC138(0);
}

void LedMode3()
{
	if(Led_Running_Code > 3)
	{
		Led_Running_Code = 0;
	}		
	P0 = 0xFF;
	HC138(4);
	if(Led_Open == 1)
	{
		P0 = Led_Running_Type[Led_Running_Code];
	}
	HC138(0);		
}

void LedMode4()
{
	if(Led_Running_Code > 3)
	{
		Led_Running_Code = 3;
	}		
	P0 = 0xFF;
	HC138(4);
	if(Led_Open == 1)
	{
		P0 = Led_Running_Type[Led_Running_Code];
	}
	HC138(0);		
}


















