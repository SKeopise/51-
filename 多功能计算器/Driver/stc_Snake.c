
#include <stc_Snake.h>



extern unsigned char code LedChar[];     //真值表


char pdata map[64];           //地图设定，每个元素映射，-1为食物，0为空地，大于0为蛇
unsigned char dztBuff[8];     //点阵显示缓存
unsigned char smgBuff[6];     //数码管显示缓存

unsigned char isShowHeader;
unsigned char len,i,X,Y;      
unsigned char move,inputbuf;

extern bit music;

unsigned char seed;       //随机数

extern unsigned char LedBuff_01;




unsigned char mode = 1;   //当前状态

unsigned char currentKeyVal = 0;    //当前按键值






unsigned char _kbhit()         //按键输入检测
{
	if(currentKeyVal)
	{
		return 1;
	}
	return 0;

}


unsigned char _getch()          //锁存按键输入值
{
	unsigned char ckv = currentKeyVal;
	currentKeyVal = 0;
	return ckv;
}






void InitGreedySnake()  //游戏初始化函数
{
	unsigned char j;
	move = 0x25;          			//初始化方向
	inputbuf = 0;               //重置输入缓存
	len = 3;    //设置蛇的长度
	
	X = 0;      //初始化蛇头坐标
	Y = 0;
	
	for(j = 0;j < 64; j++)       //初始化地图
	{
		map[j] = 0;
	}
	
	srand(seed);                //随机数生成
	
	while(map[i = rand() % 64]);    //选择一块空地设置食物
	
	map[i] = -1;
}
	



	unsigned char GreedySnake()      //贪吃蛇游戏运行
	{
		char mi,temp;
		char *p = 0;

		
		if(inputbuf != 0x37)        //如果没有按退出键
		{
			
			if(_kbhit())              //检测输入
			{
				inputbuf = _getch();    //获取输入
				
				switch(inputbuf)        //检测按键动作，若与原方向不冲突则执行，覆盖原动作
				{
					case 0x27 :if(move != 0x25)move = 0x27; break;
		      case 0x25 :if(move != 0x27)move = 0x25; break;
          case 0x28 :if(move != 0x26)move = 0x28; break;
          case 0x26 :if(move != 0x28)move = 0x26; break;
				}
			}
			
			switch(move)             //输入检测
			{
				case 0x27:p = &X, *p -= 1; break; //指针p指向坐标轴，更新坐标
				case 0x25:p = &X, *p += 1; break;
				case 0x28:p = &Y, *p += 1; break;
				case 0x26:p = &Y, *p -= 1; break;
			}
			
			*p = (*p + 8) % 8;               //如果越界，则移动到另一端
			
			p = map + X + Y * 8;             //p指向蛇头对应的地图元素
			
			if(*p > 1)                       //如果撞到自己
			{
			
				return 1;                      //游戏结束
			}
			
			if(*p == -1)                     //如果吃到食物
			{
				while (map[i = rand()%64]);    //地图上另寻空地
				
				map[i] = -1,len += 1;           //放置食物，蛇长+1
				
			}
			else
			{
				for(i = 0; i < 64;i++)         //前进方向为空地
				{
					if(map[i]>0)                 //去除蛇尾
					{
						map[i]--;
					}
				}
			}
			for(*p = len,mi = 0, i = 0,temp = 0; i<64;)    //遍历地图为蛇头赋值
			{
				if(map[i] == 0)
				{
					dztBuff[mi] = dztBuff[mi] & (~(0x80 >> (temp)));
				}
				else if(map[i] > 0)
				{
					dztBuff[mi] = dztBuff[mi] | (0x80 >> (temp));
				}
				else
				{
					dztBuff[mi] = dztBuff[mi] | (0x80 >> (temp));
				}	

					i++;
				temp = i % 8;
				if(temp == 0)    //如果到下一行元素
				{
					mi++;
				}
			}
		
			return 0;
		}
	
		else
		{
			return 1;
		}
}


void UpdateSmg(unsigned int val)   //分数与随机数显示，将数字转换到缓存中
{
		LedBuff_01 = ~(0x80>>(val%8));
	
		smgBuff[0] = LedChar[val%10];
    smgBuff[1] = LedChar[val/10%10];
    smgBuff[2] = LedChar[val/100%10];
    smgBuff[3] = LedChar[val/1000%10];
    smgBuff[4] = LedChar[val/10000%10];
    smgBuff[5] = LedChar[val/100000%10];		
}



void InitSys(unsigned char val)        //显示功能初始化
{
	unsigned char i;


	LedBuff_01 = val;
	
	for(i = 0; i < 8; i++)
	{
		if(i < 6)
		{
			smgBuff[i] = val;
		}
		dztBuff[i] = ~val;
	}	
}





void Snake_while()              //贪吃蛇主函数调用程序
{

switch(mode)
		{
			case 1://系统初始化，点亮所有LED确认显示功能正常
				
				InitSys(0);
			
	      delay_01(100);

				InitSys(0xFF);

				mode = 2;
			
			break;
			
			case 2://检测按键，是否开始游戏
				
				KeyDriver();

				if(currentKeyVal == 0x36)   //按数字键6开始游戏
				{
					InitSys(0xFF);
					mode = 3;
					break;	
				}

				seed += _getch();     //生成随机食物种子并将种子数显示在数码管
				
				UpdateSmg(seed);      
				
			break;
				
			case 3://贪吃蛇游戏初始化
				
				InitGreedySnake();   
			
				mode = 4;
			
			break;
			
			case 4://游戏中
				
				i = 240 - (len*10);     //调整贪吃蛇移动速度
			
				if(i<40)
				{
					i = 40;
				}
				
				delay_01(i/4);


				KeyDriver();

				if (GreedySnake())   //游戏失败结束，蜂鸣器连续响动提示
					{
						
						mode = 5;
						LedBuff_01 = 0;
						Deja_Vu();
		      }
					
				UpdateSmg(len - 3);  //显示游戏分数
						
			break;
						
			case 5: //游戏结束后蜂鸣器间鸣提示，并判断是否退出游戏
				
				KeyDriver();

				delay_01(10);
			
				i++;

				if(i>240)
				{
					i = 0;
				}

				if(i%10 == 0)
				{
					if(music == 0)
					{
						OpenBuzz(1387);
						delay_01(20);
						StopBuzz();
					}
					else
					{
						Deja_Vu();
					}	
				}

				if(_getch() == 0x37)   //按下数字键7退出游戏
				{
					InitSys(0xFF);
					mode = 2;
				}
				
			break; 
		}

}











