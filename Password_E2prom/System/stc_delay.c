
#include <stc_delay.h>


void delay_01(unsigned int i)
{
	unsigned int cnt = 0;
	
	while(i--)
	{
		for( ;cnt<50000;cnt++);
	}

}

void delay_02(unsigned int num) //ÑÓÊ±º¯Êý
{
	 unsigned int i;
	 while(num--)
	 for(i=0; i<628; i++);
		
}









