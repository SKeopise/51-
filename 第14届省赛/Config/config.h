#ifndef _CONFIG_H
#define _CONFIG_H



#include <STC15F2K60S2.H>
#include <intrins.h>

#include "onewire.h"
#include "iic.h"
#include "ds1302.h"
#include "led.h"
#include "key.h"
#include "init.h"
#include "PCF8591.h"
#include "NE555.h"


extern unsigned int Ds18b20_Temp_Data;  //温度数据

extern unsigned int Temp_Data_Trip,Hum_Data_Trip;   //温度和湿度在触发时记录的数据
extern unsigned int Temp_Data_Trip_Last,Hum_Data_Trip_Last; //上一次触发时的数据

extern unsigned char Ds1302_Timer[3];   //时钟数据
extern unsigned char Ds1302_Last_Trip_Time[3];  //上一次触发时的时间

extern unsigned char MenuModeSelect_S4; //菜单模式选择

extern unsigned char BackupMenuChange_S5;   //回显菜单选择

extern unsigned int Parm_Temp;  //温度参数

extern unsigned int Parm_Temp_Buf;  //温度参数缓存

extern unsigned int Temp_Data_Max;  //温度数据最大值
extern unsigned int Temp_Data_Avg;  //温度数据平均值

extern unsigned int Hum_Data_Max;   //湿度数据最大值
extern unsigned int Hum_Data_Avg;   //湿度数据平均值

extern unsigned int Freq_Data;      //频率数据

extern unsigned char Trip_Cnt;      //触发次数

extern bit flag_Menu_Interrupt;     //菜单中断标志

extern bit flag_HumData_Error;      //湿度数据错误标志

extern bit flag_Long_Set_KeyS9;     //长按设置键S9是否被按下标志

extern bit flag_Clear_Data;        //清除数据标志

extern bit flag_First_Hum_Right;    //第一次湿度数据正确标志
extern bit flag_First_Tirp;         //第一次触发标志

extern bit flag_TempCmpParm;        //温度与参数比较标志
extern bit flag_LED4_flash;         //LED4闪烁标志

extern bit flag_LED6_ON;            //LED6亮标志

sbit BUZZ = P0^6;                   //蜂鸣器
sbit RELAY = P0^4;                  //继电器






#endif







