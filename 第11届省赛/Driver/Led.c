#include <Led.h>

extern bit flag5S;
extern unsigned char key_mod;
extern unsigned char Vcnt;
extern int VP;
extern unsigned char key_error_cnt;
	unsigned int VAIN3;
	
	
	unsigned char i;
	
unsigned char code Led_SMG[] = {
	~0x3F,~0x06,~0x5B,~0x4F,~0x66,~0x6D,~0x7D,~0x07,~0x7F,~0x6F,~0x77,~0x7C,~0x39,~0x5E,~0x79,~0x71,0xFF
};


void Led_Signal()
{
	P0 = 0xFF;
	if(i == 0)
	{
		if(flag5S == 1)
		{
			HC138Y(4);
			P0 = 0xFE;
			HC138Y(0);
			flag5S = 0;
		}
	}
	else
	{
		HC138Y(4);
		P0 = 0xFF;
		HC138Y(0);
		flag5S = 0;	
	}
	
	if(Vcnt % 2 == 0)
	{
		HC138Y(4);
		P0 = 0xFF;
		HC138Y(0);		
	}
	else
	{
		HC138Y(4);
		P0 = 0xFD;
		HC138Y(0);		
	}

	if(key_error_cnt >= 3)
	{
		HC138Y(4);
		P0 = 0xFB;
		HC138Y(0);		
	}
}

void number_Vcnt()
{
	VAIN3 = AD_Get();
	VAIN3 = VAIN3*100/51;
	
  if(VAIN3 > VP+5)
	{
		i = 1;
	}
	else if(VAIN3 < VP-5)
	{
		i = 0;
	}
	if((VAIN3 < VP+5)&&(VAIN3 > VP-5))
	{
		if(i == 1)
		{
			Vcnt++;
			i = 0;
		}
	}
}



void Led_Display(unsigned char pos,unsigned char dat)
{
	P0 = 0xFF;
  HC138Y(6);
	P0 = 0x01 << pos;
	HC138Y(7);
	P0 = dat;
	delay_smg(500);
}	

void Led_Show()
{
  if(key_mod == 0)
	{
		Led_shuju();
	}
	else if(key_mod == 1)
	{
		Led_canshu();
	}
	else if(key_mod == 2)
	{
		Led_jishu();
	}
	
}

void Led_shuju()
{	
	Led_Display(0,~0x3E);
		
	Led_Display(5,Led_SMG[VAIN3/100%10] & 0x7F);
  Led_Display(6,Led_SMG[VAIN3/10%10]);
  Led_Display(7,Led_SMG[VAIN3%10]);
}

void Led_canshu()
{
	Led_Display(0,~0x73);
	
	Led_Display(5,Led_SMG[VP/100%10] & 0x7F);
	Led_Display(6,Led_SMG[VP/10%10]);
	Led_Display(7,Led_SMG[VP%10]);
}

void Led_jishu()
{
	Led_Display(0,~0x37);

	Led_Display(5,Led_SMG[Vcnt/100%10]);
	Led_Display(6,Led_SMG[Vcnt/10%10]);
	Led_Display(7,Led_SMG[Vcnt%10]);	
}


















