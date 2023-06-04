#include "ds18b20.h"



unsigned int Temp_Data = 0;





void Ds18b20ReadConfig()
{
	init_ds18b20();
	Write_DS18B20(0xCC);
	Write_DS18B20(0x44);
}


void Ds18b20ReadData()
{
	unsigned char LSB,MSB;
	unsigned int Data_Buf;
	
	init_ds18b20();
	Write_DS18B20(0xCC);
	Write_DS18B20(0xBE);
		
	LSB = Read_DS18B20();
	MSB = Read_DS18B20();
	
	Data_Buf = MSB;
	Data_Buf = (Data_Buf << 8) | LSB;
	
	if((Data_Buf & 0xF800) != 0x0000)
	{
		Data_Buf = ~Data_Buf + 1;
	}
	Data_Buf >>= 4;
	Data_Buf *= 100;
	Data_Buf += (LSB&0x0F) * 6.25;
	
	Temp_Data = Data_Buf;
}















