
#include <main.h>

bit flag5S = 0;

void main()
{
	ALL_init();	
  Timer1_init();
	Time0_init();	
	AD_init();
	VP = Read_EEPROM(0x00)*10;
	
	 while(1)
	 {	
		 number_Vcnt();
		 Led_Show();
	   Key_Driver();
		 Led_Signal();
		 DAC(VAIN3*51/100);
	 }

}



void Timer1() interrupt 3
{	 
	TL1 = 0xCD;	
	TH1 = 0xD4;	

	

}

void Timer0() interrupt 1
{	
	static int t = 0;
	TL0 = 0xCD;	
	TH0 = 0xD4;
		
	t++;
	if(t>5000)
	{
		flag5S = 1;
		t = 0;
	}

  Key_Scan();
}












