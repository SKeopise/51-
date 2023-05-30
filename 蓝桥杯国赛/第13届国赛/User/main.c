
#include <config.h>





bit flag50ms = 0;

bit flag100ms = 0;

bit flag500ms = 0;

bit flag_Led_Flash = 0;

bit flag_Relay = 0;

unsigned char RH_Data;

unsigned char Relay_Cnt = 0;
bit flag_Clear_RelayCnt = 0;



void DataRead();
void DataMath();
void RelayControl(bit RelayOn);

void main()
{
	LedBuzzInit();
	Timer2Init();
	NE555Init();
	FirstReadEEPROM();
	
	while(1)
	{		
		if(flag50ms == 1)
		{
			flag50ms = 0;
			KeyDriver();			
		}
		DataRead();
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
	

	LedDisplay();
	SmgDisplay();
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
	
	if(Sonic_Data_Distence > Parm_Distence)
	{
		if(flag_Relay == 0)
		{
			flag_Relay = 1;
			RelayControl(1);
			Relay_Cnt++;
			DataWriteEEPROM(0x00,Relay_Cnt);
		}
	}
	else
	{
		if(flag_Relay == 1)
		{
			flag_Relay = 0;
			RelayControl(0);
		}
	}
}

void RelayControl(bit RelayOn)
{
	P0 = 0xFF;
	HC138Set(5);
	
	RELAY = RelayOn;
	
	HC138Set(0);
}




