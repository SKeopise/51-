#ifndef _STC_LCD1602_H_
#define _STC_LCD1602_H_

#include <config.h>

#define LCD1602_DB P0



void LcdWaitReady();
void LcdWriteCmd(unsigned char cmd);
void LcdWriteDat(unsigned char dat);
void LcdSetCursor(unsigned char x,unsigned char y);
void LcdShowStr(unsigned char x,unsigned char y,unsigned char *str);
void InitLcd1602();


















#endif