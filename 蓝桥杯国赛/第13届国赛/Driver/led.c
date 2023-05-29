
#include "led.h"




code unsigned char Led_Number[] =
{
	0xc0, //0
	0xf9, //1
	0xa4, //2
	0xb0, //3
	0x99, //4
	0x92, //5
	0x82, //6
	0xf8, //7
	0x80, //8
	0x90, //9
	0xFF
};

unsigned char Led_Buff[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};










void SmgMenuMain()
{
	Led_Buff[0] = Led_Number[(NE555_Freq/10000)%10];
	Led_Buff[1] = Led_Number[(NE555_Freq/1000)%10];
	Led_Buff[2] = Led_Number[(NE555_Freq/100)%10];
	Led_Buff[3] = Led_Number[(NE555_Freq/10)%10];
	Led_Buff[4] = Led_Number[(NE555_Freq)%10];

}






void SmgDisplay()
{
	static unsigned char i = 0;

    HC138Set(7);
    P0 = 0xFF;	
	HC138Set(6);
	P0 = 0x01 << i;
	HC138Set(7);
	P0 = 0xFF;
	P0 = Led_Buff[i];
	HC138Set(0);
	
	i++;
	i &= 0x07;	
}















