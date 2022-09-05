#include <Key.h>



unsigned char KeySta[4] = {1,1,1,1};

extern unsigned char BUZZ_Mod,RELAY_Mod;
extern unsigned char yuzhi;



void Key_Action(unsigned char keycode)
{
	if(keycode == 0)
	{
	  WorkMod++;
		if(WorkMod > 1)
		{
			WorkMod = 0;
		}
	}
	else if(keycode == 1)
	{
	  if(WorkMod == 0)
		{
			LedMod++;
			if(LedMod > 1)
			{
				Write_EEPROM(0x20,yuzhi);
				LedMod = 0;
			}
			if(LedMod == 1)
			{
				yuzhi = Read_EEPROM(0x20);
			}
		}
		else
		{
			BUZZ_Mod++;
			if(BUZZ_Mod > 1)
			{
				BUZZ_Mod = 0;
			}	
		}
	
	}
	else if(keycode == 2)
	{
	  if(WorkMod == 0)
		{
		  yuzhi++;
			if(yuzhi > 99)
			{
				yuzhi = 99;
			}
		}	
		else
		{
			RELAY_Mod = 1;
		}
	
	}
	else if(keycode == 3)
	{
	  if(WorkMod == 0)
		{
			if(yuzhi <= 0)
			{
				yuzhi = 1;
			}					
		  yuzhi--;
		}
		else
		{
			RELAY_Mod = 0;		
		}
	}

}



void Key_Driver()
{
	static unsigned char i;
	static unsigned char backup[4] = {1,1,1,1};
	
	for(i=0;i<4;i++)
	{
		if(backup[i] != KeySta[i])
		{
			if(backup[i] != 0)
			{
			  Key_Action(i);
			}
			backup[i] = KeySta[i];
		}
	}
}


void Key_Scan()
{
	static unsigned char i;
	static unsigned char KeyBuf[4] = {
			0xFF,0xFF,0xFF,0xFF
	};
	
		KeyBuf[0] = (KeyBuf[0] << 1) | S7;
		KeyBuf[1] = (KeyBuf[1] << 1) | S6;	
		KeyBuf[2] = (KeyBuf[2] << 1) | S5;	
		KeyBuf[3] = (KeyBuf[3] << 1) | S4;
	
	for(i=0;i<4;i++)
	{
		if((KeyBuf[i] & 0x0F) == 0x00)
		{
			KeySta[i] = 0;
		}
		if((KeyBuf[i] & 0x0F) == 0x0F)
		{
			KeySta[i] = 1;
		}
	}

}






























