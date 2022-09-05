#include <DS18B20.h>


	int temp;
	unsigned char LSB,MSB;


bit Get18B20Ack()
{
	bit ack;
	
  EA = 0;
	DQ = 0;
	Delay_OneWire(40);
	DQ = 1;
	Delay_OneWire(5);
	ack = DQ;
	while(!DQ);
  EA = 1;
	
	return ack;	
}


bit Start18B20()
{
  bit ack;
	
	ack = Get18B20Ack();
	if(ack == 0)
	{
		Write_DS18B20(0xCC);
		Write_DS18B20(0x44);
	}
	return ~ack;
}

bit Get18B20Temp()
{
	bit ack;
	
	ack = Get18B20Ack();
	if(ack == 0)
	{
		Write_DS18B20(0xCC);
		EA = 0;
		Write_DS18B20(0xBE);
		EA = 1;
		LSB = Read_DS18B20();
		MSB = Read_DS18B20();		
		temp = ((int)MSB << 8)+LSB;
	}
	return ~ack;
}

void DS18B20_Read()
{
  bit res;
	
	res = Get18B20Temp();
  if(res)
	{
		temp >>= 4;
		temp = temp*10;
		temp = temp + (LSB & 0x0F)* 0.625;	
	}
	Start18B20();
}







