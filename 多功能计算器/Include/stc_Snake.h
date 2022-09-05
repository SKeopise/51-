

#ifndef _SNAKE_H_
#define _SNAKE_H_


#include <config.h>
#include <stdlib.h>
#include <stc_delay.h>
#include <stc_key.h>
#include <stc_BUZZ.h>





	unsigned char _kbhit();
	unsigned char _getch();

	void InitGreedySnake();
	unsigned char GreedySnake();

	void UpdateSmg(unsigned int val);
  void InitSys(unsigned char val);



	void Snake_while();







 #endif