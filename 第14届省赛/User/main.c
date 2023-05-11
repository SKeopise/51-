
#include <config.h>



unsigned int Freq_Data = 0;	//频率数据
unsigned int Temp_Data_Trip,Hum_Data_Trip;	//当前触发的温度和湿度数据
unsigned int Temp_Data_Trip_Last,Hum_Data_Trip_Last;	//上一次触发的温度和湿度数据

bit flag100ms = 0;	//100ms标志位
bit flag750ms = 0;	//750ms标志位
bit flag_ReadFreq = 0;	//读取频率标志位

bit flag_First_Tirp = 0;	//第一次触发标志位
bit flag_First_Hum_Right = 0;	//第一次湿度数据正确标志位
bit flag_HumData_Error = 0;	//湿度数据错误标志位
bit flag_Clear_Data = 0;	//清除数据标志位
bit flag_TempCmpParm = 0;	//温度比较参数标志位
bit flag_LED4_flash = 0;	//LED4闪烁标志位

bit flag_LED6_ON = 0;	//LED6亮标志位


void ReadData();		//读取数据
void LightOrDarkCmp(unsigned char dat);	//光照比较
void DataMath();	//数据处理
unsigned int HumDataMath();	//湿度数据处理

void main()
{
	Timer1Init();	//定时器1初始化,用于定时中断
	Timer0Init();	//定时器0初始化,用于NE555频率测量
	LedBuzzInit();	//LED和蜂鸣器初始化
	Ds1302ConfigTime();	//DS1302时钟初始化
	
	while(1)
	{
		ReadData();	//读取数据
		SmgMenuMain();	//显示菜单
		if(flag_Menu_Interrupt == 0) //菜单未被打断
		{
			KeyDriver();	//按键驱动
		}
	}
}

void Timer1Int() interrupt 3
{
	static unsigned int cnt = 0;	//定时器中断计数
	static unsigned char cnt_freq = 0;	//频率测量间隔时间计数
	static unsigned char cnt_menu = 0;	//菜单中断时间计数
	static unsigned char cnt_ClearData = 0;	//清除数据长按时间计数
	
	cnt++;
	
	if((cnt%100) == 0)	//每100ms进入一次
	{
		flag100ms = 1;	//100ms标志位,在main函数中处理
		cnt_freq++;	//频率测量间隔时间计数
		if(cnt_freq >= 5)	//每500ms进入一次
		{
			flag_ReadFreq = 1;	//读取频率标志位,在main函数中处理
			cnt_freq = 0;	//频率测量间隔时间计数清零
		}

		if(flag_Menu_Interrupt == 1) 		//光敏电阻由亮变暗,进行菜单中断,并记录菜单中断时间
		{
			cnt_menu++;	//菜单中断时间计数
			if(cnt_menu >= 30)	 	//菜单中断时间超过3s,则退出菜单中断
			{
				cnt_menu = 0;	//菜单中断时间计数清零
				flag_Menu_Interrupt = 0;	//菜单中断标志位清零
			}
		}
		
		if(flag_Long_Set_KeyS9 == 1)	//长按设置按键S9,清除数据
		{
			if(cnt_ClearData < 20)		//长按设置按键S9小于2s,则继续计数
			{
				cnt_ClearData++;	//清除数据长按时间计数
			}
			else	//长按设置按键S9超过2s,则清除数据
			{
				flag_Clear_Data = 1;	//清除数据标志位,在按键驱动中处理
			}
		}
		else	//如果按键S9没有被按下,则清除数据长按时间计数清零
		{
			cnt_ClearData = 0;	//清除数据长按时间计数清零
		}
		
		if(flag_TempCmpParm == 1)	//如果本次触发的温度比温度参数更高,则LED4闪烁
		{
			flag_LED4_flash = ~flag_LED4_flash;	//LED4闪烁标志位
		}
	}
	if((cnt%750) == 0)	//每750ms进入一次
	{
		flag750ms = 1;	//750ms标志位,在main函数中处理,用于读取温度数据
	}
	if(cnt >= 800) //每800ms一次循环中断
	{
		cnt = 0;	//定时器中断计数清零
	}
	

	
	LedDisplay();	//LED显示
	SmgDisplay();	//数码管显示
	KeyScan();		//按键扫描
	
}

void ReadData()	//读取数据
{
	if(flag750ms == 1)	//每750ms读取一次温度数据
	{
		flag750ms = 0;	//750ms标志位清零
		Ds18b20TempRead();	//读取温度数据
		Ds18b20TempConfig();	//配置下一次读取温度数据
	}
	if(flag100ms == 1)	//每100ms读取一次光敏电阻数据
	{	
		flag100ms = 0;	//100ms标志位清零
		Ds1302ReadTimer();	//读取DS1302时间数据
		LightOrDarkCmp(PCF8951AIN1ReadData());	//读取光敏电阻数据,并进行比较
	}
	if(flag_ReadFreq == 1)	//每500ms读取一次NE555频率数据
	{
		flag_ReadFreq = 0;	//读取频率标志位清零
		ReadFreqNe555(&Freq_Data);	//读取NE555频率数据,保存在Freq_Data中
	}
	
}

void LightOrDarkCmp(unsigned char dat)	//光敏电阻由亮变暗,进行菜单中断,并记录菜单中断时间
{
	static unsigned char dat_Backup = 0;	//前一次光敏电阻数据,用于判断光敏电阻是否由亮变暗
	
	if(flag_Menu_Interrupt == 0)	//如果没有触发菜单中断,则进行菜单中断判断
	{
		if(dat_Backup > 51)		//如果前一次光敏电阻数据大于51,即光敏电阻之前为亮时，判断现在的光敏电阻数据是否小于等于51
		{
			if(dat <= 51)		//如果现在的光敏电阻数据小于等于51,就是光敏电阻由亮变暗,进行菜单中断
			{
				flag_Menu_Interrupt = 1;	//菜单中断标志位置1
				DataMath();	//数据处理,采集一次温度与频率数据,并将数据进行处理
			}
		}	
	}
	dat_Backup = dat;	//保存本次光敏电阻数据,用于下一次判断
}

void DataMath()	 	//数据处理
{	
	Hum_Data_Trip = HumDataMath();	//采集一次湿度数据
	Temp_Data_Trip = Ds18b20_Temp_Data;	//采集一次温度数据
	
	if(flag_HumData_Error == 0)	//如果湿度数据没有错误,则进行数据处理
	{
		if(flag_First_Hum_Right == 0)	//如果第一次湿度数据正确,则将湿度数据赋值给湿度平均值
		{
			flag_First_Hum_Right = 1;	//第一次湿度数据正确标志位置1,避免湿度平均值被重复赋值
			Hum_Data_Avg = Hum_Data_Trip;	//湿度平均值赋值
		}		
		Hum_Data_Avg += Hum_Data_Trip;	//这两句用于计算湿度平均值
		Hum_Data_Avg /= 2;				//将之前的湿度平均值与本次湿度数据相加,再除以2,得到新的湿度平均值
		if(Hum_Data_Trip > Hum_Data_Max)	//如果本次湿度数据大于湿度最大值,则将本次湿度数据赋值给湿度最大值
		{
			Hum_Data_Max = Hum_Data_Trip;	//湿度最大值赋值
		}
		
		Ds1302_Last_Trip_Time[0] = Ds1302_Timer[0];	//记录本次触发时间
		Ds1302_Last_Trip_Time[1] = Ds1302_Timer[1];	//记录本次触发时间
		Ds1302_Last_Trip_Time[2] = Ds1302_Timer[2];	//记录本次触发时间
		Trip_Cnt++;	//触发次数计数
		
		if(flag_First_Tirp == 0)	//如果第一次触发,则将温度数据赋值给温度平均值与温度最大值
		{
			flag_First_Tirp = 1;	//第一次触发标志位置1,避免温度平均值与温度最大值被重复赋值
			Temp_Data_Avg = Temp_Data_Trip;	//温度平均值赋值
			Temp_Data_Max = Temp_Data_Trip;	//温度最大值赋值
		}			
		Temp_Data_Avg += Temp_Data_Trip;	//这两句用于计算温度平均值
		Temp_Data_Avg /= 2;					//将之前的温度平均值与本次温度数据相加,再除以2,得到新的温度平均值
		if(Temp_Data_Trip > Temp_Data_Max)	//如果本次温度数据大于温度最大值,则将本次温度数据赋值给温度最大值
		{
			Temp_Data_Max = Temp_Data_Trip;	//温度最大值赋值
		}
		
		if(Temp_Data_Trip > Parm_Temp)	//如果温度大于温度参数,则置1,否则置0
		{
			flag_TempCmpParm = 1;	//温度比较参数,如果温度大于温度参数,则置1
		}
		else
		{
			flag_TempCmpParm = 0;	//温度比较参数,如果温度小于等于温度参数,则置0
		}
		
		if(Trip_Cnt >= 2)		//如果触发次数大于等于2,则进行温度湿度与上一次数据的比较
		{
			if((Temp_Data_Trip > Temp_Data_Trip_Last) && (Hum_Data_Trip > Hum_Data_Trip_Last))	//如果温度与湿度都上升,则置1,LED6亮,否则置0,LED6灭
			{
				flag_LED6_ON = 1;	//如果温度与湿度都上升,则置1,LED6亮
			}
			else 
			{
				flag_LED6_ON = 0;	//如果温度与湿度任意一个没有上升,则置0,LED6灭
			}
		}
		
		Temp_Data_Trip_Last = Temp_Data_Trip;	//保存本次温度数据,用于下一次判断
		Hum_Data_Trip_Last = Hum_Data_Trip; 	//保存本次湿度数据,用于下一次判断
	}	
}

unsigned int HumDataMath()	//湿度数据处理
{
	float Hum_Data_Buff;	//湿度数据缓存
	unsigned int Hum_Data_True;	//湿度数据真实值
	
	if((Freq_Data >= 200) && (Freq_Data <= 2000))	//如果频率数据在200~2000之间,则进行数据处理
	{
		Hum_Data_Buff = Freq_Data;	//将频率数据赋值给湿度数据缓存
		Hum_Data_Buff *= 0.444444;	//接下来计算湿度数据与频率数据之间的关系，以符合题目要求的一次函数关系
		Hum_Data_Buff += 11.111111;	
		Hum_Data_True = Hum_Data_Buff;	//将湿度数据缓存赋值给湿度数据真实值
		flag_HumData_Error = 0;	//由于得到正确的湿度数据,所以湿度数据错误标志位置0
		return Hum_Data_True;	//返回湿度数据真实值,结束函数
	}
	else	//如果频率数据不在200~2000之间,则湿度数据错误,标志位置1
	{
		flag_HumData_Error = 1;	//湿度数据错误标志位置1
	}
	
	return 0; 	//如果湿度数据错误,则返回0
}













