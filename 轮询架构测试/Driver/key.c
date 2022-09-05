#include <key.h>



unsigned char code KeyMap[4][4] = {
	{0x07,0x11,0x15,0x19},
	{0x06,0x10,0x14,0x18},
	{0x05,0x09,0x13,0x17},
	{0x04,0x08,0x12,0x16},
};

unsigned char Key_Sta[4][4] = {
		{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}
}; 







void KeyAction(unsigned char keycode)
{
	if(keycode == 0x12)
	{
	  workmod++;
		if(workmod > 1)
		{
			workmod = 0;
		}
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
				  KeyAction(KeyMap[i][j]);
				}
				backup[i][j] = Key_Sta[i][j];
			}
		}
	}	
}

void Key_Scan()
{
  static unsigned char i;
	static unsigned char keyout;
	static unsigned char KeyBuf[4][4] = {
			{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
			{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF}
	};

	KeyBuf[keyout][0] = (KeyBuf[keyout][0] << 1) | KEY_IN_1;
	KeyBuf[keyout][1] = (KeyBuf[keyout][1] << 1) | KEY_IN_2;
	KeyBuf[keyout][2] = (KeyBuf[keyout][2] << 1) | KEY_IN_3;
	KeyBuf[keyout][3] = (KeyBuf[keyout][3] << 1) | KEY_IN_4;

	for(i=0;i<4;i++)
	{
			if((KeyBuf[keyout][i] & 0x0F) == 0x00)
			{
			  Key_Sta[keyout][i] = 0;
			}
			else if((KeyBuf[keyout][i] & 0x0F) == 0x0F)
			{
			  Key_Sta[keyout][i] = 1;
			}
	}
	
	keyout++;
	keyout = keyout & 0x03;
	
	switch(keyout)
	{
		case 0:KEY_OUT_4 = 1;KEY_OUT_1 = 0; break;
		case 1:KEY_OUT_1 = 1;KEY_OUT_2 = 0; break;
		case 2:KEY_OUT_2 = 1;KEY_OUT_3 = 0; break;
		case 3:KEY_OUT_3 = 1;KEY_OUT_4 = 0; break;
		default: break;
	}
	
}



