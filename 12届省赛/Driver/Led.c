#include "Led.h"



unsigned char code Led_Number[] = {
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90
};

unsigned char Led_Buff[8] = {
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

unsigned int temp = 0;
unsigned char parm = 25;

unsigned char Show_Mode = 0;

unsigned int DAC_Number = 0;

void SmgDisplay()
{
	static unsigned char i = 0;
	
	P0 = 0x00;
	HC138Y(6);
	P0 = 0x01 << i;	
	HC138Y(0);
	
	P0 = 0xFF;
	HC138Y(7);
	P0 = Led_Buff[i];
	HC138Y(0);
	
	i++;
	if(i > 7)
	{
		i = 0;
	}	
}

void LedMode()
{
	
	P0 = 0xFF;
	if(DAC_Mode == 0)
	{		
		LED0 = 0;
	}
	if(Show_Mode == 0)
	{
		LED1 = 0;		
	}
	else if(Show_Mode == 1)
	{
		LED2 = 0;
	}
	else if(Show_Mode == 2)
	{
		LED3 = 0;				
	}
	HC138Y(4);
	HC138Y(0);
}

void SmgShowMode()
{
	if(Show_Mode == 0)
	{
		SmgTemp();
	}
	else if(Show_Mode == 1)
	{
		SmgParm();
	}
	else if(Show_Mode == 2)
	{
		SmgDAC();
	}
	
}


void SmgTemp()
{
	Led_Buff[0] = 0xC6;
	
	Led_Buff[1] = 0xFF;
	Led_Buff[2] = 0xFF;
	Led_Buff[3] = 0xFF;
	
	Led_Buff[4] = Led_Number[(temp/1000)%10];
	Led_Buff[5] = Led_Number[(temp/100)%10] & 0x7F;
	Led_Buff[6] = Led_Number[(temp/10)%10];
	Led_Buff[7] = Led_Number[temp%10];
}

void SmgParm()
{
	Led_Buff[0] = 0x8C;
	
	Led_Buff[1] = 0xFF;
	Led_Buff[2] = 0xFF;
	Led_Buff[3] = 0xFF;	
	Led_Buff[4] = 0xFF;
	Led_Buff[5] = 0xFF;
	
	Led_Buff[6] = Led_Number[(parmbuf/10)%10];
	Led_Buff[7] = Led_Number[parmbuf%10];

}

void SmgDAC()
{
	Led_Buff[0] = 0x8C;
	
	Led_Buff[1] = 0xFF;
	Led_Buff[2] = 0xFF;
	Led_Buff[3] = 0xFF;	
	Led_Buff[4] = 0xFF;
	
	Led_Buff[5] = Led_Number[(DAC_Number/1000)%10] & 0x7F;
	Led_Buff[6] = Led_Number[(DAC_Number/100)%10];
	Led_Buff[7] = Led_Number[(DAC_Number/10)%10];
}










