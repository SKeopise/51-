#include "onewire.h"



void InitDs18b20()
{
	init_ds18b20();
	Write_DS18B20(0xCC);
	Write_DS18B20(0x44);
}

unsigned int TempRead()
{
	unsigned int Temp = 0;	
	unsigned char LSB,MSB;
		
	init_ds18b20();
	Write_DS18B20(0xCC);
	Write_DS18B20(0xBE);
			
	LSB = Read_DS18B20();
	MSB = Read_DS18B20();
	
	Temp = MSB;
	Temp = (Temp << 8) | LSB;
	
	if((Temp & 0xF800) == 0x000)
	{
		Temp = Temp >> 4;		
		Temp = Temp * 100;		
		Temp = Temp + (LSB & 0x0F)*6.25;
	}
	
	return Temp;
	
}



//单总线内部延时函数
void Delay_OneWire(unsigned int t)  
{
	t = t * 12;
	while (t--);
}

//单总线写操作
void Write_DS18B20(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 0;
		DQ = dat&0x01;
		Delay_OneWire(5);
		DQ = 1;
		dat >>= 1;
	}
	Delay_OneWire(5);
}

//单总线读操作
unsigned char Read_DS18B20(void)
{
	unsigned char i;
	unsigned char dat;
  
	for(i=0;i<8;i++)
	{
		DQ = 0;
		dat >>= 1;
		DQ = 1;
		if(DQ)
		{
			dat |= 0x80;
		}	    
		Delay_OneWire(5);
	}
	return dat;
}

//DS18B20初始化
bit init_ds18b20(void)
{
  	bit initflag = 0;
  	
  	DQ = 1;
  	Delay_OneWire(12);
  	DQ = 0;
  	Delay_OneWire(80);
  	DQ = 1;
  	Delay_OneWire(10); 
    initflag = DQ;     
  	Delay_OneWire(5);
  
  	return initflag;
}
