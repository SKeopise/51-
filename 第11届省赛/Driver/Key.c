#include <Key.h>

int VP;
unsigned char Vcnt;

	unsigned char key_error_cnt = 0;

unsigned char code keycode_map[4][4] = {
  {0x07,0x11,0x15,0x19},
	{0x06,0x10,0x14,0x18},
	{0x05,0x09,0x13,0x17},
	{0x04,0x08,0x12,0x16}
};

unsigned char Key_Sta[4][4] = {
		{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
};

unsigned char key_mod = 0;



void KeyAction_01(unsigned char keycode)
{
	if(keycode == 0x12)
	{
		key_mod++;
			if(key_mod == 2)
			{
				Write_EEPROM(0x00,VP/10);		
			}
			if(key_mod >= 3)
			{
				key_mod = 0;
			}
		key_error_cnt = 0;
	}
	else if(keycode == 0x13)
	{
    if(key_mod == 2)
		{
			Vcnt = 0;
			key_error_cnt = 0;
		}	
		else
		{
			key_error_cnt++;
		}
	}
	else if(keycode == 0x16)
	{
		if(key_mod == 1)
		{
			key_error_cnt = 0;
		  VP += 50;
			if(VP > 500)
			{
				VP = 0;
			}
		}
		else
		{
			key_error_cnt++;
		}
	}
	else if(keycode == 0x17)
	{
		if(key_mod == 1)
		{
			key_error_cnt = 0;
		  VP -= 50;
			if(VP < 0)
			{
				VP = 500;
			}
		}
		else
		{
			key_error_cnt++;
		}
	}
	else
	{
		key_error_cnt++;	
	}
	
}






void Key_Driver()
{
	static unsigned char i,j;
	static unsigned char backup[4][4] = {
		{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
	};
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(backup[i][j] != Key_Sta[i][j])
			{
				if(backup[i][j] != 0)
				{

						KeyAction_01(keycode_map[i][j]);

				}
				backup[i][j] = Key_Sta[i][j];
			}
		}
	}  
	

}


void Key_Scan()
{
	unsigned char i;
	static unsigned char keyout = 0;
	static unsigned char keybuf[4][4] = {
		{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
		{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF}
	};
	
	keybuf[keyout][0] = (keybuf[keyout][0]<<1) | KEY_IN_1;
	keybuf[keyout][1] = (keybuf[keyout][1]<<1) | KEY_IN_2;
	keybuf[keyout][2] = (keybuf[keyout][2]<<1) | KEY_IN_3;
	keybuf[keyout][3] = (keybuf[keyout][3]<<1) | KEY_IN_4;
	
	for(i=0;i<4;i++)
	{
		if((keybuf[keyout][i] & 0x0F) == 0x00)
		{
			Key_Sta[keyout][i] = 0;
		}
		else if((keybuf[keyout][i] & 0x0F) == 0x0F)
		{
			Key_Sta[keyout][i] = 1;
		}
	}
	
	keyout++;
	keyout = keyout & 0x03;
	switch(keyout)
	{
		case 0:KEY_OUT_4 = 1; KEY_OUT_1 = 0;break;
		case 1:KEY_OUT_1 = 1; KEY_OUT_2 = 0;break;
	  case 2:KEY_OUT_2 = 1; KEY_OUT_3 = 0;break;
	  case 3:KEY_OUT_3 = 1; KEY_OUT_4 = 0;break;
		default:break;
	}
}




























