#ifndef _CONFIG_H
#define _CONFIG_H



#include <STC15F2K60S2.H>
#include <intrins.h>

#include "init.h"
#include "key.h"
#include "led.h"
#include "ds1302.h"
#include "iic.h"
#include "Sonic.h"







extern unsigned char Timer_Data[3];
extern unsigned char Read_Timer_Parm;   //采集时间参数
extern unsigned char Read_Timer_Parm_Buf;
extern unsigned char Len_Parm;          //距离参数
extern unsigned char Len_Parm_Buf; 
extern unsigned int Sonic_Len_Data;     //超声波测距距离
extern unsigned int Sonic_Data_MAX;
extern unsigned int Sonic_Data_MIN;
extern unsigned int Sonic_Data_Sympal;


extern bit Sonic_Too_Far;
extern bit flag_Light_Dark;
extern unsigned char flag_L5;
extern bit flag_First_Read;


extern bit Show_Mode;                               //界面显示切换变量，0数据显示界面，1参数设置界面
extern unsigned char pdata Show_Data_Mode;          //数据显示界面：0时间显示，1距离显示，2数据记录
extern bit Show_Parm_Mode;                          //参数设置界面：0采集时间参数，1距离参数
extern bit Read_Lens_Mode;                          //距离显示模式下，测距的方式：0触发模式，1定时模式
extern unsigned char Data_Save_Mode;                //数据记录界面下：0最大值，1最小值，2平均值























#endif
