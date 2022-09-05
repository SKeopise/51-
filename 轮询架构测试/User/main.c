#include <config.h>

#include <init.h>
#include <ds1302.h>


unsigned char workmod = 0;




void main()
{
  Timer0init();
	Timer1init();
	ALL_INIT();
	DS1302_Config();

	while(1)
	{
	  TaskProcess();
	}

}



void Timer0() interrupt 1
{
	TL0 = 0xCD;	
	TH0 = 0xD4;	
	
	Led_interrupt();	
}

void Timer1() interrupt 3
{
	TL1 = 0xCD;	
	TH1 = 0xD4;	
	

	TaskRemarks();
	Key_Scan();	
}



