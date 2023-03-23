/*	# 	DS1302代码片段说明
	1. 	本文件夹中提供的驱动代码供参赛选手完成程序设计参考。
	2. 	参赛选手可以自行编写相关代码或以该代码为基础，根据所选单片机类型、运行速度和试题
		中对单片机时钟频率的要求，进行代码调试和修改。
*/								

//

#include "ds1302.h"

unsigned char code Ds1302_Write_ADDR[7] = {0x80,0x82,0x84,0x86,0x88,0x8A,0x8C};         //写入数据寄存器地址
unsigned char code Ds1302_Read_ADDR[7] = {0x81,0x83,0x85,0x87,0x89,0x8B,0x8D};           //读取数据寄存器地址
unsigned char Ds1302_Time[] = {0x50,0x59,0x23,0x01,0x02,0x05,0x23};                     //当前时间存放数组

void Ds1302_Config()              //初始化，将Ds1302_Time中的数据写入到DS1302中，并开始自动计数
{
	char i = 0;
	Write_Ds1302_Byte(0x8E,0x00);
	for(i=0;i<7;i++)
	{
		Write_Ds1302_Byte(Ds1302_Write_ADDR[i],Ds1302_Time[i]);
	}
	Write_Ds1302_Byte(0x8E,0x80);
}

void Ds1302_Read()           //读取函数，调用时将DS1302中的数据存放到Ds1302_Time[]中；
{
	char i=0;
	for(i=0;i<7;i++)
	{
		Ds1302_Time[i] = Read_Ds1302_Byte(Ds1302_Read_ADDR[i]);
	}

}



void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK = 0;
		SDA = temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

//
void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

//
unsigned char Read_Ds1302_Byte ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}
