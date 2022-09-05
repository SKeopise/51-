#include <BUZZ.h>



unsigned char BUZZ_Mod = 1,RELAY_Mod = 0;




void Auto_Mod()
{
	if(shidu < yuzhi)
	{
		P0 = P0 & 0x10;
	  HC138Y(5);
		RELAY = 1;
		HC138Y(0);
	}
	else
	{
		P0 = P0 & 0x10;
	  HC138Y(5);
		RELAY = 0;
		HC138Y(0);	
	}
}


void Manual_Mod()
{
	if(BUZZ_Mod == 1)
	{
		if(shidu < yuzhi)
		{
			P0 = P0 & 0x50;
			HC138Y(5);
			BUZZ = 1;
			HC138Y(0);
		}
		else
		{
			P0 = P0 & 0x50;
			HC138Y(5);
			BUZZ = 0;
			HC138Y(0);	
		}
	}
	else
	{
			P0 = P0 & 0x50;
			HC138Y(5);
			BUZZ = 0;
			HC138Y(0);	
	}
	if(RELAY_Mod == 1)
	{
		P0 = P0 & 0x50;
	  HC138Y(5);
		RELAY = 1;
		HC138Y(0);	
	}
	else
	{
		P0 = P0 & 0x50;
	  HC138Y(5);
		RELAY = 0;
		HC138Y(0);	
	}

}
























