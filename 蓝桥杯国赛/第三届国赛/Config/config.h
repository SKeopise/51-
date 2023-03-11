#ifndef _CONFIG_H_
#define _CONFIG_H_


#include <STC15F2K60S2.H>


#include "ds1302.h"
#include "init.h"
#include "led.h"
#include "key.h"
#include "iic.h"
#include "EEPROM.h"
#include "sonic.h"


extern unsigned char TimerData[7];     			 //DS1302的时间存储
extern unsigned char PassWord[6];       		 //实际密码存储
extern unsigned char Password_Mode;      		 //当前输入密码的状态，0为输入密码解锁，1为设置界面的输入旧密码，2为输入新密码
extern unsigned char PassWordBuff[6];    	     //按键输入密码的显示缓存
extern unsigned char Number_Code;       	     //输入密码时的位数缓存
extern unsigned char Error_Cnt;						 //密码输入错误的次数
extern unsigned char Buzz_Time; 						 //蜂鸣器响起时间
extern unsigned char Door_Open_Time;						 //开门时间

extern unsigned int Sonic_Time;
extern float Sonic_Dist;

extern bit Door_Mod;                    //0为自动门状态，1为密码门状态
extern bit Password_Right;              //判断密码是否正确
extern bit Password_Over;             	//判断当前密码输入是否完成
extern bit Buzz_Warring;					//蜂鸣器警报开关
extern bit Door_Open;                   //门的开关

extern bit Sonic_Far;

sbit LED0 = P0^0;
sbit LED1 = P0^1;
sbit LED2 = P0^2;
sbit LED3 = P0^3;
sbit LED4 = P0^4;
sbit LED5 = P0^5;
sbit LED6 = P0^6;
sbit LED7 = P0^7;

sbit BUZZ = P0^6;
sbit RELAY = P0^4;

sbit KEY_IN_0 = P4^4;
sbit KEY_IN_1 = P4^2;
sbit KEY_IN_2 = P3^5;
sbit KEY_IN_3 = P3^4;

sbit KEY_OUT_0 = P3^0;
sbit KEY_OUT_1 = P3^1;
sbit KEY_OUT_2 = P3^2;
sbit KEY_OUT_3 = P3^3;

sbit TX = P1^0;
sbit RX = P1^1;













#endif
