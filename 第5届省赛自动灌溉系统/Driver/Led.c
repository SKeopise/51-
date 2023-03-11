
#include <Led.h>


extern unsigned char Timer[7];

unsigned char shidu,yuzhi;

unsigned char LedChar[] = {
	~0x3f,~0x06,~0x5b,~0x4f,~0x66,~0x6d,~0x7d,~0x07,~0x7f,~0x6f,~0x77,~0x7c,~0x39,~0x5e,~0x79,~0x71,~0x00
};


void Led_Driver(unsigned char pos,unsigned char dat)
{
	P0 = 0xFF;
	HC138Y(6);
	P0 = 0x01 << pos;
	HC138Y(7);
	P0 = dat;
	delay_01(500);
}



void Led_shidu()
{
	shidu = AD_Get();
	shidu = shidu*99/255;
	
	Led_Driver(0,LedChar[Timer[2]/16]);
	Led_Driver(1,LedChar[Timer[2]%16]);
	Led_Driver(2,0xBF);
	Led_Driver(3,LedChar[Timer[1]/16]);
	Led_Driver(4,LedChar[Timer[1]%16]);
	Led_Driver(5,0xFF);
	Led_Driver(6,LedChar[shidu/10%10]);
	Led_Driver(7,LedChar[shidu%10]);

}

void Led_yuzhi()
{
	Led_Driver(0,0xBF);
	Led_Driver(1,0xBF);
	Led_Driver(2,0xFF);	
	Led_Driver(3,0xFF);
	Led_Driver(4,0xFF);	
	Led_Driver(5,0xFF);	
	
	Led_Driver(6,LedChar[yuzhi/10%10]);
	Led_Driver(7,LedChar[yuzhi%10]);	
}

void Led_Mod()
{
	P0 = 0xFF;
	HC138Y(4);
	if(WorkMod == 1)
	{
		P0 = ~0x01;
	}
	else
	{
		P0 = ~0x02;
	}
	HC138Y(0);
}


































