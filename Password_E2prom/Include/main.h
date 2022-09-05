#ifndef _MAIN_H_
#define _MAIN_H_


#include "config.h"
#include "stc_led.h"
#include <stc_int.h>
#include <stc_key.h>
#include <stc_28BYJ48.h>
#include <stc_BUZZ.h>
#include <stc_i2c.h>
#include <stc_LCD1602.h>
#include <EEPROM.h>
#include <STC_UART.h>  
#include <Password.h>





unsigned char T0RH = 0;
unsigned char T0RL = 0;
extern unsigned char T1RH,T1RL;


extern unsigned char cntBuf;
extern unsigned char pdata PasswordBuf[MAX_LEN];
extern unsigned char pdata Password_dat1[MAX_LEN];




bit Decide_Mod();	

void Lcd1602_ShowPassword(unsigned char *buf,unsigned char len);

void Enter_Init();	
	
	
	
#endif