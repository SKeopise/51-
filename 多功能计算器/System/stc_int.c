
#include <config.h>

#include <stc_int.h>


	extern	unsigned long sec;
	extern unsigned char flag1s;




void Led_Display_init()    //����ܳ�ʼ��
{
  ADDR3 = 1;
	ENLED = 0;

}


void interrupt_init()      //��ʱ��T0�жϳ�ʼ��         
{
  EA = 1;
	ET0 =1;

}



void ConfigTimer0(unsigned int ms)    //��ʱ����ʼ��
{
	extern unsigned char T0RH;
	extern unsigned char T0RL;
	unsigned long tmp;

	tmp = 11059200 / 12;
	tmp = (tmp * ms) / 1000;
	tmp = 65536 - tmp;
	tmp = tmp + 18;
	T0RH = (unsigned char)(tmp >> 8);
	T0RL = (unsigned char)tmp;
	TMOD &= 0x00;
	TMOD |= 0x11;
	TH0 = T0RH;
	TL0 = T0RL;
	ET0 = 1;
  
	TR0 = 1;
	
}












