
#include <main.h>

extern unsigned char shidu,yuzhi;
unsigned char WorkMod = 0,LedMod = 0;


void main()
{
	Buzz_init();
	Timer0_init();
	Timer1_init();
  DS1302_Config();
  AD_init();
	yuzhi = 50;
	
	while(1)
	{
	  Key_Driver();
		Led_Mod();
		if(WorkMod == 0)
		{
			Auto_Mod();
		}
		else
		{
			Manual_Mod();
		}
		if(LedMod == 0)
		{
			Led_shidu();
			DS1302_Read();
		}
		else
		{
			shidu = AD_Get();
			shidu = shidu*99/255;			
			Led_yuzhi();
		}
	}

}


void Timer0() interrupt 1
{
	TL0 = 0xCD;		
	TH0 = 0xD4;	



}

void Timer1() interrupt 3
{
	TL1 = 0xCD;		
	TH1 = 0xD4;	

	Key_Scan();
}

















