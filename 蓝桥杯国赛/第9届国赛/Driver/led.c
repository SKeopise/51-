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




void LedDisplay()
{
	P0 = 0xFF;
	HC138Set(4);
	
	if(MenuMode_Main == 0)
	{
		if(MenuMode_Data == 0)
		{
			LED1 = 0;
		}
		else if(MenuMode_Data == 1)
		{
			LED2 = 0;
		}
		else if(MenuMode_Data == 2)
		{
			LED3 = 0;
		}
	}
	
	LED8 = flag_Led8;
	
	HC138Set(0);
}


void SmgMenuMain()
{
	if(MenuMode_Main == 0)
	{
		if(MenuMode_Data == 0)
		{
			SmgMenuDataTemp();
		}
		else if(MenuMode_Data == 1)
		{
			SmgMenuDataADC();
		}
		else if(MenuMode_Data == 2)
		{
			SmgMenuDataFreq();
		}
	}
	else if(MenuMode_Main == 1)
	{
		SmgMenuBackupData();
	}
	else if(MenuMode_Main == 2)
	{
		SmgMenuParmSet();
	}
}

void SmgMenuParmSet()
{
	Led_Buff[0] = 0x8C;	
	Led_Buff[1] = Led_Number[10];	
	Led_Buff[2] = Led_Number[10];
	Led_Buff[3] = Led_Number[10];	
	Led_Buff[4] = Led_Number[10];
	Led_Buff[5] = Led_Number[10];

	Led_Buff[6] = Led_Number[(Parm_ADC_Buf/10)%10] & 0x7F;
	Led_Buff[7] = Led_Number[(Parm_ADC_Buf)%10];	
}

void SmgMenuBackupData()
{
	Led_Buff[0] = 0x89;
	
	if(MenuMode_Backup == 0)
	{
		Led_Buff[1] = 0xC6;	
		Led_Buff[2] = Led_Number[10];
		Led_Buff[3] = Led_Number[10];		
		if(Temp_Data_EEPROM >= 1000)
		{
			Led_Buff[4] = Led_Number[(Temp_Data_EEPROM/1000)%10];		
		}
		else
		{
			Led_Buff[4] = Led_Number[10];		
		}	
		Led_Buff[5] = Led_Number[(Temp_Data_EEPROM/100)%10] & 0x7F;
		Led_Buff[6] = Led_Number[(Temp_Data_EEPROM/10)%10];
		Led_Buff[7] = Led_Number[(Temp_Data_EEPROM)%10];		
	}
	else if(MenuMode_Backup == 1)
	{
		Led_Buff[1] = 0xC1;	
		Led_Buff[2] = Led_Number[10];
		Led_Buff[3] = Led_Number[10];	
		Led_Buff[4] = Led_Number[10];
		Led_Buff[5] = Led_Number[10];

		Led_Buff[6] = Led_Number[(ADC_Data_EEPROM/10)%10] & 0x7F;
		Led_Buff[7] = Led_Number[(ADC_Data_EEPROM)%10];		
	}
	else if(MenuMode_Backup == 2)
	{
		Led_Buff[1] = 0x8E;		
		if(Freq_Data_EEPROM >= 100000)
		{
			Led_Buff[2] = Led_Number[(Freq_Data_EEPROM/100000)%10];		
		}
		else
		{
			Led_Buff[2] = Led_Number[10];		
		}
		if(Freq_Data_EEPROM >= 10000)
		{
			Led_Buff[3] = Led_Number[(Freq_Data_EEPROM/10000)%10];		
		}
		else
		{
			Led_Buff[3] = Led_Number[10];		
		}
		if(Freq_Data_EEPROM >= 1000)
		{
			Led_Buff[4] = Led_Number[(Freq_Data_EEPROM/1000)%10];		
		}
		else
		{
			Led_Buff[4] = Led_Number[10];		
		}
		if(Freq_Data_EEPROM >= 100)
		{
			Led_Buff[5] = Led_Number[(Freq_Data_EEPROM/100)%10];		
		}
		else
		{
			Led_Buff[5] = Led_Number[10];		
		}
		if(Freq_Data_EEPROM >= 10)
		{
			Led_Buff[6] = Led_Number[(Freq_Data_EEPROM/10)%10];		
		}
		else
		{
			Led_Buff[6] = Led_Number[10];		
		}
		Led_Buff[7] = Led_Number[(Freq_Data_EEPROM)%10];			
	}
}

void SmgMenuDataADC()
{
	Led_Buff[0] = 0xC1;	
	Led_Buff[1] = Led_Number[10];
	Led_Buff[2] = Led_Number[10];
	Led_Buff[3] = Led_Number[10];	
	Led_Buff[4] = Led_Number[10];
	Led_Buff[5] = Led_Number[10];

	Led_Buff[6] = Led_Number[(ADC_Data/10)%10] & 0x7F;
	Led_Buff[7] = Led_Number[(ADC_Data)%10];
}

void SmgMenuDataTemp()
{
	Led_Buff[0] = 0xC6;	
	Led_Buff[1] = Led_Number[10];
	Led_Buff[2] = Led_Number[10];
	Led_Buff[3] = Led_Number[10];	
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

void SmgMenuDataFreq()
{
	Led_Buff[0] = 0x8E;	
	Led_Buff[1] = Led_Number[10];	
	
	if(Freq_Data >= 100000)
	{
		Led_Buff[2] = Led_Number[(Freq_Data/100000)%10];		
	}
	else
	{
		Led_Buff[2] = Led_Number[10];		
	}
	if(Freq_Data >= 10000)
	{
		Led_Buff[3] = Led_Number[(Freq_Data/10000)%10];		
	}
	else
	{
		Led_Buff[3] = Led_Number[10];		
	}
	if(Freq_Data >= 1000)
	{
		Led_Buff[4] = Led_Number[(Freq_Data/1000)%10];		
	}
	else
	{
		Led_Buff[4] = Led_Number[10];		
	}
	if(Freq_Data >= 100)
	{
		Led_Buff[5] = Led_Number[(Freq_Data/100)%10];		
	}
	else
	{
		Led_Buff[5] = Led_Number[10];		
	}
	if(Freq_Data >= 10)
	{
		Led_Buff[6] = Led_Number[(Freq_Data/10)%10];		
	}
	else
	{
		Led_Buff[6] = Led_Number[10];		
	}
	Led_Buff[7] = Led_Number[(Freq_Data)%10];		
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









