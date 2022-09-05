#ifndef _PASSWORD_H_
#define _PASSWORD_H_


#include <config.h>
#include <EEPROM.h>
#include <stc_delay.h>
#include <stc_LCD1602.h>
#include <stc_BUZZ.h>

#define MAX_LEN 16
#define SAVE_ADDR 0X60


extern unsigned char state,EnterCnt;
extern unsigned int code NoteFrequ[]; 



extern void Enter_Init();

void KeyAction(unsigned char keycode);


void Key_Number(unsigned char keycode);
void Key_Enter();
void Key_Esc();





bit CmpMemory(unsigned char *ptr1, unsigned char *ptr2, unsigned char len);

void Show_PSWcnt();

void Copy_Number(unsigned char *out,unsigned char *in,unsigned char len);
void Fill_Number(unsigned char *dat,unsigned char byt,unsigned char len);

unsigned char PSW_Check(unsigned char *dat,unsigned char len);
bit Read_Password();
void Save_Password();





#endif