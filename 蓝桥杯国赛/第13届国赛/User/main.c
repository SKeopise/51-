
#include <config.h>





bit flag50ms = 0;

bit flag100ms = 0;

bit flag500ms = 0;

bit flag_Led_Flash = 0;

bit flag_Relay = 0;

bit flag_EEPROM_Write = 0;

unsigned char RH_Data;

unsigned char Relay_Cnt = 0;
bit flag_Clear_RelayCnt = 0;

unsigned char pwm_cnt = 0;

bit flag_pwm = 0;


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
		}
		if(flag_EEPROM_Write == 1)
		{
			flag_EEPROM_Write = 0;
			DataWriteEEPROM(0x00,Relay_Cnt);
		}
		if(flag_pwm == 1)
		{
			flag_pwm = 0;
			RelayMotorControl();
		}
		DataRead();
		
	}
}

void Timer1Int() interrupt 3
{	
	pwm_cnt++;
	
	flag_pwm = 1;
	if(pwm_cnt >= 5)
	{
		pwm_cnt = 0;
		SmgDisplay();
		LedDisplay();
	}
}

void Timer2Int() interrupt 12
{
	static unsigned int cnt = 0;
	static unsigned char Long_Set_Time = 0;
	
	cnt++;
	if((cnt % 44) == 0)
	{
		flag50ms = 1;		
	}
	if((cnt % 101) == 0)
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
	if(cnt >= 499)
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
	if(flag100ms == 1)
	{
		flag100ms = 0;
		SonicDataRead();		
		ADC_Data_Read_AIN3(&RH_Data);
		DataMath();	
		SmgMenuMain();
	}
	if(flag500ms == 1)
	{
		flag500ms = 0;
		NE555FreqReadData(&NE555_Freq);
	}	
}

void DataMath()
{
	float RH_Data_Buf = 0;
	float DAC_Data_Buf = 0;
	unsigned char DAC_Data = 0;
	
	RH_Data_Buf = RH_Data;
	RH_Data_Buf /= 51;
	RH_Data_Buf *= 20;
	RH_Data = RH_Data_Buf;
	if(RH_Data >= 99)
	{
		RH_Data = 99;
	}
	
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
	P0 = 0x00;
	if(flag_Relay == 1)
	{		
		RELAY = 1;
	}
	else
	{
		RELAY = 0;		
	}
	
	HC138Set(5);
	if(flag_Pwm_Output == 1)
	{
		if(pwm_cnt < 4)
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
		if(pwm_cnt < 4)
		{
			Motor = 0;
		}
		else
		{
			Motor = 1;
		}		
	}
	
	if(flag100ms == 1)
	{
		if(Sonic_Data_Distence > Parm_Distence)
		{
			if(flag_Relay == 0)
			{
				flag_Relay = 1;
	//			RELAY = 1;
				Relay_Cnt++;
				flag_EEPROM_Write = 1;
			}
		}
		else
		{
			if(flag_Relay == 1)
			{
				flag_Relay = 0;
	//			RELAY = 0;
			}
		}	
	}
	
	HC138Set(0);	
}


