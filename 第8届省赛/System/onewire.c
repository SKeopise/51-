/*	# 	单总线代码片段说明
	1. 	本文件夹中提供的驱动代码供参赛选手完成程序设计参考。
	2. 	参赛选手可以自行编写相关代码或以该代码为基础，根据所选单片机类型、运行速度和试题
		中对单片机时钟频率的要求，进行代码调试和修改。
*/

//

#include "onewire.h"



sbit DQ = P1^4;

unsigned int Temp_Data = 0;


void Ds18B20ReadInit()
{
	init_ds18b20();
	Write_DS18B20(0xCC);
	Write_DS18B20(0x44);
}

void Ds18B20ReadTempData()
{
	unsigned char LSB,MSB;
	
	init_ds18b20();
	Write_DS18B20(0xCC);
	Write_DS18B20(0xBE);

	LSB = Read_DS18B20();
	MSB = Read_DS18B20();
	
	Temp_Data = MSB;
	Temp_Data = Temp_Data << 8;
	Temp_Data = Temp_Data | LSB;
	
	if((Temp_Data & 0xF800) == 0x0000)
	{
		Temp_Data >>= 4;
	}	
}







void Delay_OneWire(unsigned int t)  
{
	unsigned char i;
	while(t--){
		for(i=0;i<12;i++);
	}
}

//
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

//
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

//
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
