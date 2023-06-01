#include "uart.h"


unsigned char Uart_StringBuf[10];

unsigned char Send_StringBuf[15];

unsigned char Uart_ReadCnt = 0;

bit flag_StringError = 0;

bit flag_ReadRight = 0;

bit flag_ReadEnd = 0;



void UartInit()		//4800bps@12.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x8F;		//设置定时初始值
	TH1 = 0xFD;		//设置定时初始值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
	
	ES = 1;
	EA = 1;
}


void Uart1Int() interrupt 4
{
	if(RI == 1)
	{
		RI = 0;
		if(Uart_ReadCnt < 10)
		{
			Uart_StringBuf[Uart_ReadCnt++] = SBUF;
		}
	}
	
	if(TI == 1)
	{
		TI = 0;
	}
}

void UartDriver()
{
	float Data_Buf = 0;
	unsigned int Int_Buf = 0;
	
	if(flag_ReadEnd == 1)
	{
		if(Uart_StringBuf[0] == 'S')
		{
			StringCmp(Uart_StringBuf,"ST\r\n");
			if(flag_ReadRight == 1)
			{
				flag_ReadRight = 0;
				Data_Buf = Temp_Data;
				Data_Buf /= 100;
				sprintf(Send_StringBuf,"$%2d,%2.2f\r\n",Sonic_Distence,Data_Buf);
				UartSendString(Send_StringBuf);
			}
			if(flag_StringError == 1)
			{
				flag_StringError = 0;
				UartSendString("ERROR\r\n");
			}
		}
		else if(Uart_StringBuf[0] == 'P')
		{
			StringCmp(Uart_StringBuf,"PARA\r\n");
			if(flag_ReadRight == 1)
			{
				flag_ReadRight = 0;
				Int_Buf = ParmData_Temp;
				Int_Buf /= 100;
				sprintf(Send_StringBuf,"$%2d,%2d\r\n",ParmData_Distence,Int_Buf);
				UartSendString(Send_StringBuf);
			}
			if(flag_StringError == 1)
			{
				flag_StringError = 0;
				UartSendString("ERROR\r\n");
			}		
		}
		else
		{
			UartSendString("ERROR\r\n");
		}
		StringClear(Uart_StringBuf,10);
		flag_ReadEnd = 0;
		Uart_ReadCnt = 0;
	}
}

void UartReadTimerMonitor(unsigned char ms)
{
	static unsigned char ReadCnt_Buf = 0;
	static unsigned char ReadTimer = 0;
	
	if(Uart_ReadCnt > 0)
	{
		if(ReadCnt_Buf != Uart_ReadCnt)
		{
			ReadCnt_Buf = Uart_ReadCnt;
			ReadTimer = 0;
		}
		else
		{
			if(ReadTimer < 30)
			{
				ReadTimer += ms;
				if(ReadTimer >= 30)
				{
					ReadTimer = 0;
					flag_ReadEnd = 1;
				}
			}
		}
	}
	else
	{
		ReadCnt_Buf = 0;
	}
	
}


void UartSendByte(unsigned char dat)
{
	SBUF = dat;
	while(TI == 0);
	TI = 0;
}

void UartSendString(unsigned char *str)
{
	while(*str != '\0')
	{
		UartSendByte(*str++);
	}
}


void StringCmp(unsigned char *str1,unsigned char *str2)
{
	while((*str1 != '\0') && (*str2 != '\0'))
	{
		if(*str1 != *str2)
		{
			flag_StringError = 1;
			break;
		}
		str1++;
		str2++;
	}
	if((*str1 == '\0') && (*str2 == '\0'))
	{
		flag_ReadRight = 1;
	}
	else
	{
		flag_StringError = 1;
	}
	
}


void StringClear(unsigned char *str,unsigned char len)
{
	while(len--)
	{
		*str = '\0';
		str++;
	}	
}







