
#include <stc_BUZZ.h>
#include <stc_delay.h>


 unsigned int code NoteFrequ[] = {
	 1026, 1145, 1298, 1387, 1568,
	 1760, 1976, 2093, 2349, 2637
};


 unsigned char T1RH = 0;
 unsigned char T1RL = 0;

 



void OpenBuzz(unsigned int frequ)
{
	unsigned int reload;

	reload = 65535 - (11059200 / 12) / (frequ * 2);
	T1RH = (unsigned char)(reload >> 8);
	T1RL = (unsigned char)reload;
	TH1 = 0xFF;
	TL1 = 0xFE;
	ET1 = 1;
	TR1 = 1;

}


void StopBuzz()
{
	ET1 = 0;
	TR1 = 0;
}


void Deja_Vu()
{
	OpenBuzz(1760);
	delay_01(10);
	StopBuzz();
	
	OpenBuzz(1976);
	delay_01(10);
	StopBuzz();

	OpenBuzz(2093);
	delay_01(40);
	StopBuzz();
	
	OpenBuzz(1976);
	delay_01(10);
	StopBuzz();

	OpenBuzz(1760);
	delay_01(10);
	StopBuzz();

	OpenBuzz(1568);
	delay_01(40);
	StopBuzz();	

}








