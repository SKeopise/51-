
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

unsigned char Led_Buff[8] = {0xFF,0XFF,0xFF,0XFF,0xFF,0XFF,0xFF,0XFF};




unsigned char TimeLast = 50;





void LedDisplay()
{
	P0 = 0xFF;
	
	if((Stop == 0)||(TimeLast != 0))
	{
		if(Mode == 1)
		{
			LED1 = 0;
		}
		else if(Mode == 2)
		{
			LED2 = 0;
		}
		else if(Mode == 3)
		{
			LED3 = 0;
		}
		else
		{
			if(Mode_Buf == 1)
			{
				LED1 = 0;
			}
			else if(Mode_Buf == 2)
			{
				LED2 = 0;
			}
			else if(Mode_Buf == 3)
			{
				LED3 = 0;
			}			
		}
	}
	
	HC138Set(4);
	HC138Set(0);
	
}


void SmgShowPwmMode(unsigned char mod)
{
	Led_Buff[0] = 0xBF;
	Led_Buff[1] = Led_Number[mod];
	Led_Buff[2] = 0xBF;
	
	Led_Buff[3] = Led_Number[10];
	
	if(mod == 4)
	{
		Led_Buff[4] = Led_Number[10];
		Led_Buff[5] = Led_Number[(Temp/10)%10];
		Led_Buff[6] = Led_Number[Temp%10];
		Led_Buff[7] = 0xC6;			
	}
	else
	{
		Led_Buff[4] = Led_Number[(TimeLast/1000)%10];
		Led_Buff[5] = Led_Number[(TimeLast/100)%10];
		Led_Buff[6] = Led_Number[(TimeLast/10)%10];
		Led_Buff[7] = Led_Number[TimeLast%10];	
	}
}


void SmgDisplay()
{
	static unsigned char i = 0;
	
	P0 = 0x00;
	HC138Set(6);
	P0 = 0x01<<i;
	HC138Set(0);
	
	P0 = 0xFF;
	HC138Set(7);
	P0 = Led_Buff[i];
	HC138Set(0);
	
	i++;
	i&=0x07;
}












