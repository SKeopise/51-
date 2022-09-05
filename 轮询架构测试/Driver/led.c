#include <led.h>



unsigned char code LedChar[] = {
	0xC0,0xF9,0xA4,0xB0,0x99,0X92,0x82,0xF8,0x80,0X90	
};

unsigned char LedBuff[] = {
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};


//void Led_Display(unsigned char pos,unsigned char dat)
//{
//	P0 = 0xFF;
//	HC138(6);
//	P0 = 0x01 << pos;
//	HC138(7);
//	P0 = dat;
//  HC138(0);
//	delay(300);
//}

void Led_interrupt()
{
	static unsigned char i=0;
	
	P0 = 0xFF;
	HC138(6);
	P0 = 0x01 << i;
	HC138(7);
	P0 = LedBuff[i];
  HC138(0);
	
	i++;
	if(i>7)
	{
		i=0;
	}
}


//void Led_DS18B20()
//{
//	static unsigned char i=0;
//	
//	switch(i)
//	{
//		case 0: Led_Display(7,LedChar[temp%10]); i++; break;
//		case 1: Led_Display(6,LedChar[(temp%100)/10]); i++; break;
//		case 2: Led_Display(5,LedChar[temp/100]); i++; break;
//		
//		case 3: Led_Display(1,LedChar[1]); i++; break;
//		case 4: Led_Display(0,~0x3E); i=0; break;
//		default: break;
//	}
//}

void Led_18B20Buff()
{
	if(workmod == 0)
	{
		LedBuff[7] = LedChar[temp%10];
		LedBuff[6] = LedChar[(temp%100)/10] & ~0x80;
		LedBuff[5] = LedChar[temp/100];
		LedBuff[4] = 0xFF;
		LedBuff[3] = 0xFF;
		LedBuff[2] = 0xFF;

		LedBuff[1] = LedChar[1];
		LedBuff[0] = ~0x3E;	
	}
}


void Led_DS1302Buff()
{
	if(workmod == 1)
	{
		LedBuff[7] = LedChar[Timer[0]%16];
		LedBuff[6] = LedChar[Timer[0]/16];
		LedBuff[5] = ~0x40;
		LedBuff[4] = LedChar[Timer[1]%16];
		LedBuff[3] = LedChar[Timer[1]/16];
		LedBuff[2] = 0xFF;

		LedBuff[1] = LedChar[2];
		LedBuff[0] = ~0x3E;	
	}
}










