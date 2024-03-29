
#include <config.h>



bit flag10ms = 0;

bit flag50ms = 0;

bit flag100ms = 0;

bit flag500ms = 0;

bit flag_Led_Flash = 0;

bit flag_Relay = 0;

bit flag_EEPROM_Write = 0;

unsigned char RH_Data;

unsigned char Relay_Cnt = 0;
bit flag_Clear_RelayCnt = 0;





void DataRead();
void DataMath();
void RelayMotorControl();

void main()
{
	LedBuzzInit();
	Timer1Init();
	Timer2Init();
	NE555Init();
	FirstReadEEPROM();
	InitPCA();
	
	while(1)
	{	
		if(flag50ms == 1)
		{
			flag50ms = 0;
			KeyDriver();
			if(Sonic_Data_Distence > Parm_Distence)
			{
				if(flag_Relay == 0)
				{
					flag_Relay = 1;
					Relay_Cnt++;
					flag_EEPROM_Write = 1;
				}
			}
			else
			{
				if(flag_Relay == 1)
				{
					flag_Relay = 0;
				}
			}				
		}
		if(flag_EEPROM_Write == 1)
		{
			flag_EEPROM_Write = 0;
			DataWriteEEPROM(0x00,Relay_Cnt);
		}

		DataRead();
		
	}
}

void Timer1Int() interrupt 3
{	
	RelayMotorControl();	
	SmgDisplay();	
}

void Timer2Int() interrupt 12
{
	static unsigned int cnt = 0;
	static unsigned char Long_Set_Time = 0;
	
	cnt++;
	if((cnt % 13) == 0)
	{
		flag10ms = 1;
		LedDisplay();		
	}
	if((cnt % 47) == 0)
	{
		flag50ms = 1;		
	}
	if((cnt % 102) == 0)
	{
		flag100ms = 1;
		flag_Led_Flash = ~flag_Led_Flash;
		if(flag_S7_LongSet == 1)
		{
			if(Long_Set_Time < 10)
			{
				Long_Set_Time++;
			}
			else
			{
				flag_Clear_RelayCnt = 1;
			}
		}
		else
		{
			Long_Set_Time = 0;
		}
	}
	if(cnt >= 482)
	{
		cnt = 0;
		flag500ms = 1;
	}
	

//	LedDisplay();
//	SmgDisplay();
	KeyScan();
}


void DataRead()
{
	float RH_Data_Buf = 0;
	
	if(flag10ms == 1)
	{
		flag10ms = 0;
		ADC_Data_Read_AIN3(&RH_Data);
		RH_Data_Buf = RH_Data;
		RH_Data_Buf /= 51;
		RH_Data_Buf *= 20;
		RH_Data = RH_Data_Buf;
		if(RH_Data >= 99)
		{
			RH_Data = 99;
		}
		SmgMenuMain();		
	}
	if(flag100ms == 1)
	{
		flag100ms = 0;
		SonicDataRead();	
		DataMath();			
	}
	if(flag500ms == 1)
	{
		flag500ms = 0;
		NE555FreqReadData(&NE555_Freq);
	}	
}

void DataMath()
{
	float DAC_Data_Buf = 0;
	unsigned char DAC_Data = 0;
	
	if(RH_Data < Parm_RH)
	{
		DAC_Output(53);
	}
	else if(RH_Data > 80)
	{
		DAC_Output(255);
	}
	else
	{
		DAC_Data_Buf = RH_Data;
		DAC_Data_Buf -= Parm_RH;
		DAC_Data_Buf *= 4;
		DAC_Data_Buf /= (80 - Parm_RH);
		DAC_Data_Buf += 1;
		DAC_Data_Buf *= 53.125;
		DAC_Data = DAC_Data_Buf;
		DAC_Output(DAC_Data);
	}
}


void RelayMotorControl()
{	
	static unsigned char pwm_cnt = 0;

	pwm_cnt++;
	
	if(pwm_cnt >= 10)
	{
		pwm_cnt = 0;
	}	
	
	P0 = 0x00;
	if(flag_Pwm_Output == 1)
	{
		if(pwm_cnt < 8)
		{
			Motor = 1;
		}
		else
		{
			Motor = 0;
		}
	}
	else
	{
		if(pwm_cnt < 8)
		{
			Motor = 0;
		}
		else
		{
			Motor = 1;
		}		
	}	
	if(flag_Relay == 1)
	{		
		RELAY = 1;
	}
	else
	{
		RELAY = 0;		
	}
	
	HC138Set(5);	
	HC138Set(0);	
}


