#ifndef KEY_H
#define KEY_H

// 在这里写下你的代码

#include "config.h"

void Key_Action_bkp1(unsigned char keycode);

void Key_Driver();

void Key_Scan();

extern void Relay(unsigned char onoff);








#endif /* KEY_H */