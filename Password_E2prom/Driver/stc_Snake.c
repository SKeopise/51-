
#include <stc_Snake.h>



extern unsigned char code LedChar[];     //��ֵ��


char pdata map[64];           //��ͼ�趨��ÿ��Ԫ��ӳ�䣬-1Ϊʳ�0Ϊ�յأ�����0Ϊ��
unsigned char dztBuff[8];     //������ʾ����
unsigned char smgBuff[6];     //�������ʾ����

unsigned char isShowHeader;
unsigned char len,i,X,Y;      
unsigned char move,inputbuf;

extern bit music;

unsigned char seed;       //�����

extern unsigned char LedBuff_01;




unsigned char mode = 1;   //��ǰ״̬

unsigned char currentKeyVal = 0;    //��ǰ����ֵ






unsigned char _kbhit()         //����������
{
	if(currentKeyVal)
	{
		return 1;
	}
	return 0;

}


unsigned char _getch()          //���水������ֵ
{
	unsigned char ckv = currentKeyVal;
	currentKeyVal = 0;
	return ckv;
}






void InitGreedySnake()  //��Ϸ��ʼ������
{
	unsigned char j;
	move = 0x25;          			//��ʼ������
	inputbuf = 0;               //�������뻺��
	len = 3;    //�����ߵĳ���
	
	X = 0;      //��ʼ����ͷ����
	Y = 0;
	
	for(j = 0;j < 64; j++)       //��ʼ����ͼ
	{
		map[j] = 0;
	}
	
	srand(seed);                //���������
	
	while(map[i = rand() % 64]);    //ѡ��һ��յ�����ʳ��
	
	map[i] = -1;
}
	



	unsigned char GreedySnake()      //̰������Ϸ����
	{
		char mi,temp;
		char *p = 0;

		
		if(inputbuf != 0x37)        //���û�а��˳���
		{
			
			if(_kbhit())              //�������
			{
				inputbuf = _getch();    //��ȡ����
				
				switch(inputbuf)        //��ⰴ������������ԭ���򲻳�ͻ��ִ�У�����ԭ����
				{
					case 0x27 :if(move != 0x25)move = 0x27; break;
		      case 0x25 :if(move != 0x27)move = 0x25; break;
          case 0x28 :if(move != 0x26)move = 0x28; break;
          case 0x26 :if(move != 0x28)move = 0x26; break;
				}
			}
			
			switch(move)             //������
			{
				case 0x27:p = &X, *p -= 1; break; //ָ��pָ�������ᣬ��������
				case 0x25:p = &X, *p += 1; break;
				case 0x28:p = &Y, *p += 1; break;
				case 0x26:p = &Y, *p -= 1; break;
			}
			
			*p = (*p + 8) % 8;               //���Խ�磬���ƶ�����һ��
			
			p = map + X + Y * 8;             //pָ����ͷ��Ӧ�ĵ�ͼԪ��
			
			if(*p > 1)                       //���ײ���Լ�
			{
			
				return 1;                      //��Ϸ����
			}
			
			if(*p == -1)                     //����Ե�ʳ��
			{
				while (map[i = rand()%64]);    //��ͼ����Ѱ�յ�
				
				map[i] = -1,len += 1;           //����ʳ��߳�+1
				
			}
			else
			{
				for(i = 0; i < 64;i++)         //ǰ������Ϊ�յ�
				{
					if(map[i]>0)                 //ȥ����β
					{
						map[i]--;
					}
				}
			}
			for(*p = len,mi = 0, i = 0,temp = 0; i<64;)    //������ͼΪ��ͷ��ֵ
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
				if(temp == 0)    //�������һ��Ԫ��
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


void UpdateSmg(unsigned int val)   //�������������ʾ��������ת����������
{
		LedBuff_01 = ~(0x80>>(val%8));
	
		smgBuff[0] = LedChar[val%10];
    smgBuff[1] = LedChar[val/10%10];
    smgBuff[2] = LedChar[val/100%10];
    smgBuff[3] = LedChar[val/1000%10];
    smgBuff[4] = LedChar[val/10000%10];
    smgBuff[5] = LedChar[val/100000%10];		
}



void InitSys(unsigned char val)        //��ʾ���ܳ�ʼ��
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





void Snake_while()              //̰�������������ó���
{

switch(mode)
		{
			case 1://ϵͳ��ʼ������������LEDȷ����ʾ��������
				
				InitSys(0);
			
	      delay_01(100);

				InitSys(0xFF);

				mode = 2;
			
			break;
			
			case 2://��ⰴ�����Ƿ�ʼ��Ϸ
				
				KeyDriver();

				if(currentKeyVal == 0x36)   //�����ּ�6��ʼ��Ϸ
				{
					InitSys(0xFF);
					mode = 3;
					break;	
				}

				seed += _getch();     //�������ʳ�����Ӳ�����������ʾ�������
				
				UpdateSmg(seed);      
				
			break;
				
			case 3://̰������Ϸ��ʼ��
				
				InitGreedySnake();   
			
				mode = 4;
			
			break;
			
			case 4://��Ϸ��
				
				i = 240 - (len*10);     //����̰�����ƶ��ٶ�
			
				if(i<40)
				{
					i = 40;
				}
				
				delay_01(i/4);


				KeyDriver();

				if (GreedySnake())   //��Ϸʧ�ܽ����������������춯��ʾ
					{
						
						mode = 5;
						LedBuff_01 = 0;
						Deja_Vu();
		      }
					
				UpdateSmg(len - 3);  //��ʾ��Ϸ����
						
			break;
						
			case 5: //��Ϸ�����������������ʾ�����ж��Ƿ��˳���Ϸ
				
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

				if(_getch() == 0x37)   //�������ּ�7�˳���Ϸ
				{
					InitSys(0xFF);
					mode = 2;
				}
				
			break; 
		}

}











