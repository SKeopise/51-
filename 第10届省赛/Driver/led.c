#include "led.h"


unsigned char code Led_Number[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF};

unsigned char Led_Buff[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};




void SmgMode()
{
	if(Smg_Open == 1)
	{
		if(Show_Mode == 0)
		{
			SmgShowADC();
		}
		else
		{
			if(flag_500ms == 1)
			{
				SmgShowFreq();
			}
		}
	}
	else
	{
		SmgOff();
	}
	
}


void LedMode()
{
	P0 = 0xFF;
	HC138(4);
	
	if(Show_Mode == 0)
	{
		LED1 = 0;
		LED2 = 1;
	}   
	else
	{
		LED1 = 1;
		LED2 = 0;
	}
	
	if(AD_Show_Number < 150)
	{
		LED3 = 1;
	}
	else if((AD_Show_Number >= 150) && (AD_Show_Number < 250))
	{
		LED3 = 0;
	}
	else if((AD_Show_Number >= 250) && (AD_Show_Number < 350))
	{
		LED3 = 1;
	}
	else if(AD_Show_Number >= 350)
	{
		LED3 = 0;
	}
	
	if(NE555_Freq < 1000)
	{
		LED4 = 1;
	}
	else if((NE555_Freq >= 1000) && (NE555_Freq < 5000))
	{
		LED4 = 0;
	}
	else if((NE555_Freq >= 5000) && (NE555_Freq < 10000))
	{
		LED4 = 1;
	}
	else if(NE555_Freq >= 10000)
	{
		LED4 = 0;
	}	
	
	if(DAC_Mode == 0)
	{
		LED5 = 1;
	}
	else
	{
		LED5 = 0;
	}
	
	HC138(0);
}


void SmgDisplay()
{
	static unsigned char i = 0;
	
	P0 = 0x00;
	HC138(6);
	P0 = 0x01 << i;
	HC138(0);
	
	P0 = 0xFF;
	HC138(7);
	P0 = Led_Buff[i];
	HC138(0);
	
	i++;
	if(i >= 8)
	{
		i = 0;
	}
}

void SmgOff()
{
	Led_Buff[0] = Led_Number[10];	
	Led_Buff[1] = Led_Number[10];	
	Led_Buff[2] = Led_Number[10];
	Led_Buff[3] = Led_Number[10];
	Led_Buff[4] = Led_Number[10];
	Led_Buff[5] = Led_Number[10];	
	Led_Buff[6] = Led_Number[10];
	Led_Buff[7] = Led_Number[10];
	
}

void SmgShowADC()
{
	Led_Buff[0] = 0xC1;
	Led_Buff[1] = Led_Number[10];	
	Led_Buff[2] = Led_Number[10];
	Led_Buff[3] = Led_Number[10];
	Led_Buff[4] = Led_Number[10];
	
	Led_Buff[5] = Led_Number[(AD_Show_Number/100)%10] & 0x7F;
	Led_Buff[6] = Led_Number[(AD_Show_Number/10)%10];
	Led_Buff[7] = Led_Number[AD_Show_Number%10];		
}


void SmgShowFreq()
{
	Led_Buff[0] = 0x8E;
	Led_Buff[1] = Led_Number[10];
	
	if(NE555_Freq >= 100000)
	{
		Led_Buff[2] = Led_Number[(NE555_Freq/100000)%10];
	}
	else
	{
		Led_Buff[2] = Led_Number[10];		
	}
	if(NE555_Freq >= 10000)
	{
		Led_Buff[3] = Led_Number[(NE555_Freq/10000)%10];
	}
	else
	{
		Led_Buff[3] = Led_Number[10];		
	}
	if(NE555_Freq >= 1000)
	{
		Led_Buff[4] = Led_Number[(NE555_Freq/1000)%10];
	}
	else
	{
		Led_Buff[4] = Led_Number[10];		
	}
	if(NE555_Freq >= 100)
	{
		Led_Buff[5] = Led_Number[(NE555_Freq/100)%10];
	}
	else
	{
		Led_Buff[5] = Led_Number[10];		
	}
	if(NE555_Freq >= 10)
	{
		Led_Buff[6] = Led_Number[(NE555_Freq/10)%10];
	}
	else
	{
		Led_Buff[6] = Led_Number[10];		
	}
	
	Led_Buff[7] = Led_Number[NE555_Freq%10];
}





















