#include "onewire.h"


unsigned int DS18B20_Read()       //DS18B20璇诲彇鍑芥暟
{
	unsigned char LSB,MSB;
	unsigned int temp;
	
	init_ds18b20();
	Write_DS18B20(0xCC);
	Write_DS18B20(0x44);
	
	delay_us(1000);
	
	init_ds18b20();
	Write_DS18B20(0xCC);
	Write_DS18B20(0xBE);
	
	LSB = Read_DS18B20();
	MSB = Read_DS18B20();
	
	temp = MSB;
	temp = (temp << 8) | LSB;
	
	if((temp & 0xf800) == 0x000)
	{
		temp >>= 4;
		temp = temp * 10;
		temp = temp + (LSB & 0x0F)*0.625;
	}
	return temp;
}


//单总线内部延时函数
void Delay_OneWire(unsigned int t)  
{
	t = t*12;
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
