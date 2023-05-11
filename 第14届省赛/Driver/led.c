#include "led.h"


//数码管真值表
unsigned char code Led_Number[] =
{
	0xc0, //0
	0xf9, //1
	0xa4, //2
	0xb0, //3
	0x99, //4
	0x92, //5
	0x82, //6
	0xf8, //7
	0x80, //8
	0x90, //9
};

//数码管显示缓存
unsigned char Led_Buff[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

unsigned int Temp_Data_Max = 0;	//温度数据最大值
unsigned int Temp_Data_Avg = 0;	//温度数据平均值

unsigned int Hum_Data_Max = 0;	//湿度数据最大值
unsigned int Hum_Data_Avg = 0;	//湿度数据平均值

unsigned char Trip_Cnt = 0;		//触发次数

unsigned char Ds1302_Last_Trip_Time[3] = {0x00,0x00,0x00};	//上一次触发时间

bit flag_Menu_Interrupt = 0;	//菜单中断标志



void SmgMenuMain()
{
	if(flag_Menu_Interrupt == 0)	//如果当前光敏电阻没有被触发,则显示普通界面
	{
		if(MenuModeSelect_S4 == 0)	//如果菜单模式选择为0，显示时钟界面
		{
			SmgMenuTimer();	//时钟界面
		}
		else if(MenuModeSelect_S4 == 1)	//如果菜单模式选择为1，显示回显界面
		{
			SmgMenuBackup();	//回显界面
		}
		else if(MenuModeSelect_S4 == 2)	//如果菜单模式选择为2，显示参数界面
		{
			SmgMenuParmData();	//参数界面
		}
	}
	else	//如果当前光敏电阻被触发,则进入温湿度界面
	{
		SmgMenuInterruptTempHum();	//温湿度界面
	}
	
}

void LedDisplay()	//LED指示灯显示
{
	P0 = 0xFF;
	HC138Set(4);
	if(MenuModeSelect_S4 == 0)	//如果菜单模式选择为0,LED1亮
	{
		LED1 = 0;
	}
	else if(MenuModeSelect_S4 == 1)	//如果菜单模式选择为1,LED2亮
	{
		LED2 = 0;
	}
	else if(MenuModeSelect_S4 == 2)	//如果菜单模式选择为2,LED3亮
	{
		LED3 = 0;
	}
	
	if(flag_TempCmpParm == 1)	//如果此次温度数据超过温度参数,LED4闪烁
	{
		LED4 = flag_LED4_flash;
	}
	if(flag_HumData_Error == 1)	//如果湿度数据错误,LED5亮
	{
		LED5 = 0;
	}
	if(Trip_Cnt >= 2)	//如果触发次数大于等于2
	{
		if(flag_LED6_ON == 1)	//如果此次触发的温度和湿度数据都升高,则LED6亮
		{
			LED6 = 0;
		}
	}
	
	HC138Set(0);
	
}


void SmgMenuInterruptTempHum()	//温湿度界面显示内容函数
{
	Led_Buff[0] = 0x86;	//显示界面标志,0x86显示字母E
	
	Led_Buff[1] = 0xFF;	
	Led_Buff[2] = 0xFF;
	Led_Buff[3] = Led_Number[(Temp_Data_Trip/100)%10]; //显示温度数据的十位	
	Led_Buff[4] = Led_Number[(Temp_Data_Trip/10)%10];	//显示温度数据的个位
	Led_Buff[5] = 0xBF;		//显示分隔符
	if(flag_HumData_Error == 0)		//如果湿度数据没有错误,则显示湿度数据
	{
		Led_Buff[6] = Led_Number[(Hum_Data_Trip/100)%10];	//显示湿度数据的十位
		Led_Buff[7] = Led_Number[(Hum_Data_Trip/10)%10];	//显示湿度数据的个位	
	}
	else	//如果湿度数据错误,则显示字母AA
	{
		Led_Buff[6] = 0x88;
		Led_Buff[7] = 0x88;		
	}
}



void SmgMenuParmData()	//温度参数界面
{
	Led_Buff[0] = 0x8C;
	
	Led_Buff[1] = 0xFF;
	Led_Buff[2] = 0xFF;
	Led_Buff[3] = 0xFF;
	Led_Buff[4] = 0xFF;
	Led_Buff[5] = 0xFF;
	
	Led_Buff[6] = Led_Number[(Parm_Temp_Buf/100)%10];	//显示温度参数的十位
	Led_Buff[7] = Led_Number[(Parm_Temp_Buf/10)%10];	//显示温度参数的个位
}


void SmgMenuBackup()	//回显界面选择函数
{
	if(BackupMenuChange_S5 == 0)	//如果回显界面选择为0,显示温度回显界面
	{
		SmgMenuBackupDataTempC();	//温度回显界面
	}
	else if(BackupMenuChange_S5 == 1)	//如果回显界面选择为1,显示湿度回显界面
	{
		SmgMenuBackupDataHumidityH();	//湿度回显界面
	}
	else if(BackupMenuChange_S5 == 2)	//如果回显界面选择为2,显示触发次数和时间回显界面
	{
		SmgMenuBackupDataTimerAndTripF();	//触发次数和时间回显界面
	}
}


void SmgMenuBackupDataTimerAndTripF()	//触发次数和时间回显界面
{
	Led_Buff[0] = 0x8E;
	Led_Buff[1] = Led_Number[(Trip_Cnt/10)%10];	//显示触发次数的十位
	Led_Buff[2] = Led_Number[(Trip_Cnt)%10];;		//显示触发次数的个位
	
	Led_Buff[3] = Led_Number[Ds1302_Last_Trip_Time[2]>>4];		//显示最后一次触发时间中小时的十位
	Led_Buff[4] = Led_Number[Ds1302_Last_Trip_Time[2]&0x0F];	//显示最后一次触发时间中小时的个位
	Led_Buff[5] = 0xBF;
	Led_Buff[6] = Led_Number[Ds1302_Last_Trip_Time[1]>>4];			//显示最后一次触发时间中分钟的十位
	Led_Buff[7] = Led_Number[Ds1302_Last_Trip_Time[1]&0x0F];		//显示最后一次触发时间中分钟的个位
}


void SmgMenuBackupDataHumidityH()	//湿度回显界面
{
	Led_Buff[0] = 0x89;
	Led_Buff[1] = 0xFF;
	
	Led_Buff[2] = Led_Number[(Hum_Data_Max/100)%10];	//显示湿度最大值的十位
	Led_Buff[3] = Led_Number[(Hum_Data_Max/10)%10];		//显示湿度最大值的个位
	
	Led_Buff[4] = 0xBF;
	
	Led_Buff[5] = Led_Number[(Hum_Data_Avg/100)%10];	//显示湿度平均值的十位
	Led_Buff[6] = Led_Number[(Hum_Data_Avg/10)%10] & 0x7F;	//显示湿度平均值的个位
	Led_Buff[7] = Led_Number[(Hum_Data_Avg)%10];		//显示湿度平均值小数点后一位
}

void SmgMenuBackupDataTempC()	//温度回显界面
{
	Led_Buff[0] = 0xC6;
	Led_Buff[1] = 0xFF;
	
	Led_Buff[2] = Led_Number[(Temp_Data_Max/100)%10];	//显示温度最大值的十位
	Led_Buff[3] = Led_Number[(Temp_Data_Max/10)%10];	//显示温度最大值的个位
	
	Led_Buff[4] = 0xBF;	//显示分隔符
	
	Led_Buff[5] = Led_Number[(Temp_Data_Avg/100)%10];	//显示温度平均值的十位
	Led_Buff[6] = Led_Number[(Temp_Data_Avg/10)%10] & 0x7F;	//显示温度平均值的个位
	Led_Buff[7] = Led_Number[(Temp_Data_Avg)%10];		//显示温度平均值小数点后一位
}

void SmgMenuTimer()	//时间显示界面
{
	Led_Buff[0] = Led_Number[Ds1302_Timer[2]>>4];
	Led_Buff[1] = Led_Number[Ds1302_Timer[2]&0x0F];
	Led_Buff[2] = 0xBF;
	Led_Buff[3] = Led_Number[Ds1302_Timer[1]>>4];
	Led_Buff[4] = Led_Number[Ds1302_Timer[1]&0x0F];
	Led_Buff[5] = 0xBF;
	Led_Buff[6] = Led_Number[Ds1302_Timer[0]>>4];
	Led_Buff[7] = Led_Number[Ds1302_Timer[0]&0x0F];	
}



void SmgDisplay()	//数码管显示函数
{
	static unsigned char i = 0;	//数码管位选变量
	
	HC138Set(7);	//数码管段选
	P0 = 0xFF;	 	//消隐
	HC138Set(6);	//数码管位选
	P0 = 0x01<<i;	//位选,从左到右依次点亮数码管
	HC138Set(7);	//数码管段选
	P0 = 0xFF;		//消隐
	P0 = Led_Buff[i];	//段选,显示数码管的值
	HC138Set(0);	//138译码器悬空,防止干扰到其他模块
	
	i++;	//数码管位选变量自加
	i &= 0x07;		//数码管位选变量限制在0~7之间
}


















