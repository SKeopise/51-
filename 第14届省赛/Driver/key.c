#include "key.h"



//按键映射表
unsigned char code Key_Map[2][2] = {
	{'5','9'},
	{'4','8'}
};

//按键状态表
unsigned char Key_Sta[2][2] = {
	{1,1},{1,1}
};


unsigned char MenuModeSelect_S4 = 0;	//菜单模式选择
unsigned char BackupMenuChange_S5 = 0;	//回显菜单选择

unsigned int Parm_Temp = 300;		//温度参数
unsigned int Parm_Temp_Buf = 300;	//温度参数缓存

bit flag_Long_Set_KeyS9 = 0;	//长按设置键S9是否被按下标志


void KeyAction0(unsigned char keycode)	//按键按下动作执行对应的操作,参数为按键映射表中的键值
{
	if(keycode == '4')
	{
		MenuSelectContorlKeyS4();	//进行菜单选择控制
	}
	else if(keycode == '5')
	{
		BackupDataMenuSelectKeyS5();	//进行回显数据菜单选择
	} 
	else if(keycode == '8')		
	{
		TempParmModeAddKeyS8();	//进行温度参数模式增加
	}
	else if(keycode == '9')	
	{
		TempParmModeReduceKeyS9();	//进行温度参数模式减少
		if(BackupMenuChange_S5 == 2)	//如果当前处于时间回显界面		
		{
			flag_Long_Set_KeyS9 = 1;	//长按设置键S9被按下,用于记录S9长按时间
		}
	}		
}

void KeyAction1(unsigned char keycode)	//按键松开动作执行对应的操作,参数为按键映射表中的键值
{
	if(keycode == '9')
	{
		if(flag_Long_Set_KeyS9 == 1)	//如果长按设置键S9被按下
		{
			if(flag_Clear_Data == 1)	//如果清除数据标志被置位,即长按设置键S9被按下超过2秒,则清除所有触发数据
			{
				flag_Clear_Data = 0;	//清除数据标志清零,防止重复清除数据
				AllTripDataInit();		//所有触发数据初始化
			}                         
			flag_Long_Set_KeyS9 = 0;	//长按设置键S9被按下标志清零,表面现在按键S9没有被按下
		}
	}
}

void AllTripDataInit()	//所有触发数据初始化
{
	Trip_Cnt = 0;	//触发次数清零
	Temp_Data_Max = 0;	//温度数据最大值清零
	Temp_Data_Avg = 0;	//温度数据平均值清零
	Hum_Data_Max = 0;	//湿度数据最大值清零
	Hum_Data_Avg = 0;	//湿度数据平均值清零
	Ds1302_Last_Trip_Time[0] = 0x00;	//上一次触发时间清零
	Ds1302_Last_Trip_Time[1] = 0x00;	
	Ds1302_Last_Trip_Time[2] = 0x00;
	flag_First_Tirp = 0;	//第一次触发标志清零
	flag_First_Hum_Right = 0;		//第一次湿度正确标志清零
}

void MenuSelectContorlKeyS4()	//菜单选择控制键
{
	MenuModeSelect_S4++;	//菜单模式选择加1
	if(MenuModeSelect_S4 > 2)	//如果菜单模式选择大于2
	{
		MenuModeSelect_S4 = 0;	//菜单模式选择清零,菜单模式只能选择0,1,2三个界面
		Parm_Temp = Parm_Temp_Buf;	//在退出温度参数设置模式时,将温度参数缓存赋值给温度参数,更新温度参数
	}
	if(MenuModeSelect_S4 == 0)	//如果菜单模式选择为0
	{
		BackupMenuChange_S5 = 0;	//保证在每次进入回显数据模式时,回显菜单选择为0
	}
}

void BackupDataMenuSelectKeyS5()	//回显数据菜单选择
{
	if(MenuModeSelect_S4 == 1)	//如果处于回显数据模式
	{
		BackupMenuChange_S5++;	//回显菜单选择加1
		if(BackupMenuChange_S5 > 2)	//如果回显菜单选择大于2
		{
			BackupMenuChange_S5 = 0;	//回显菜单选择清零,回显菜单只能选择0,1,2三个界面
		}		
	}	
}


void TempParmModeReduceKeyS9()	//温度参数减少
{
	if(MenuModeSelect_S4 == 2)	//如果处于温度参数设置模式
	{
		if(Parm_Temp_Buf > 0)	//如果温度参数大于0
		{
			Parm_Temp_Buf -= 10;	//温度参数减10
		}
	}
}

void TempParmModeAddKeyS8()	//温度参数增加
{
	if(MenuModeSelect_S4 == 2)	//如果处于温度参数设置模式
	{
		if(Parm_Temp_Buf < 990)	//如果温度参数小于990
		{
			Parm_Temp_Buf += 10;	//温度参数加10
		}
	}
}

void KeyDriver()	//按键驱动
{
	unsigned char i,j;	//循环变量
	static unsigned char Key_Backup[2][2] = {	//上一次按键状态,0表示按键按下,1表示按键松开
		{1,1},{1,1}
	};

	for(i=0;i<2;i++)		//遍历按键状态表
	{
		for(j=0;j<2;j++)	//遍历按键状态表
		{
			if(Key_Backup[i][j] != Key_Sta[i][j])	//判断按键是否有变化,有变化则执行按键动作
			{
				if(Key_Backup[i][j] == 1)	//如果之前按键是松开的状态,则说明这次是按键按下
				{
					KeyAction0(Key_Map[i][j]);	//执行按键按下动作
				}
				else	//如果之前按键是按下的状态,则说明这次是按键松开
				{
					KeyAction1(Key_Map[i][j]);	//执行按键松开动作
				}
				
				Key_Backup[i][j] = Key_Sta[i][j];	//更新按键状态
			}
		}
	}	
}




void KeyScan()	//按键扫描
{
	unsigned char i = 0;	
	static unsigned char Key_Out = 0; 	//当前进行扫描的行
	static unsigned char Key_Buff[2][2] = {	//按键缓存,0表示按键按下,1表示按键松开,用于消抖
		{0xFF,0xFF},{0xFF,0xFF}
	};
	
	Key_Buff[Key_Out][0] = (Key_Buff[Key_Out][0] << 1) | KEY_IN_0;	//保存此次扫描的按键状态,第一列为KEY_IN_0,第二列为KEY_IN_1
	Key_Buff[Key_Out][1] = (Key_Buff[Key_Out][1] << 1) | KEY_IN_1;
	
	for(i=0;i<2;i++)	//判断按键状态
	{
		if(Key_Buff[Key_Out][i] == 0x00)	//如果每行每列的某个按键连续8次扫描都为0,则表示按键按下
		{
			Key_Sta[Key_Out][i] = 0;	//按键按下
		}
		else if(Key_Buff[Key_Out][i] == 0xFF)	//如果每行每列的某个按键连续8次扫描都为1,则表示按键松开
		{
			Key_Sta[Key_Out][i] = 1;	//按键松开
		}	
	}
	
	Key_Out++;	//下一行进行扫描
	Key_Out &= 0x01;	//Key_Out只能为0或1
	
	switch(Key_Out)	//选择行
	{
		case 0: KEY_OUT_2 = 0; KEY_OUT_3 = 1; break;	//KEY_OUT_2为0,KEY_OUT_3为1,表示扫描第一行
		case 1: KEY_OUT_3 = 0; KEY_OUT_2 = 1; break;	//KEY_OUT_3为0,KEY_OUT_2为1,表示扫描第二行
		default: break;	
	}
	
}













