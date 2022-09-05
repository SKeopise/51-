
#include <init.h>


unsigned int T1RH,T1RL,T0RH,T0RL;




void ALL_init()
{
	HC138Y(5);
	P0 = 0x00;
	HC138Y(4);
	P0 = 0xFF;	
}


void Timer1_init()
{		
	AUXR |= 0x40;		
	TMOD &= 0x0F;		
	TL1 = 0xCD;	
	TH1 = 0xD4;		
	TR1 = 1;
	ET1 = 1;
	EA = 1;

}

void Time0_init()
{
	AUXR |= 0x80;	
	TMOD &= 0xF0;		
	TL0 = 0xCD;		
	TH0 = 0xD4;
	EA = 1;
	ET0 = 1;
	TR0 = 1;

}






void HC138Y(unsigned char Y)
{
	switch(Y)
	{
		case 0: P2 = (P2&0x1F) | 0x00;
		break;
		case 1: P2 = (P2&0x1F) | 0x20;
		break;
		case 2: P2 = (P2&0x1F) | 0x40;
		break;
		case 3: P2 = (P2&0x1F) | 0x60;
		break;
		case 4: P2 = (P2&0x1F) | 0x80;
		break;
		case 5: P2 = (P2&0x1F) | 0xA0;
		break;
		case 6: P2 = (P2&0x1F) | 0xC0;
		break;
		case 7: P2 = (P2&0x1F) | 0xE0;
		break;		
	}


}



void delay_smg(unsigned int t)
{
	while(t--);
}


//void delay_01(unsigned int ms)
//{
//	unsigned int i = 0;
//	
//	while(ms--)
//	{
//		for(i=0;i<628;i++);
//	}
//}













