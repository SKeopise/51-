#include <Password.h>


  unsigned char cntBuf;
	unsigned char pdata PasswordBuf[MAX_LEN];
	
	unsigned char pdata Password_dat1[MAX_LEN];
	
	unsigned char pdata Password_Read[MAX_LEN];



void Key_Number(unsigned char keycode)
{
	switch(state)
	{
		case 3:
			break;
		case 4:
			break;
		default:
			Enter_Init();
			if(cntBuf < MAX_LEN)
			{
				PasswordBuf[cntBuf++] = keycode;
				Show_PSWcnt();
			}
			else
			{
				Fill_Number(PasswordBuf,'\0',MAX_LEN);
				LcdShowStr(0,0,"Password Error  ");
				LcdShowStr(0,1,"too long ");
				delay_01(1500);
				Enter_Init();
				cntBuf = 0;
			}
		break;
	}
}


void Key_Enter()
{
	
		switch(state)
		{
			case 0://����������ȷ���������״̬	
			if(CmpMemory(PasswordBuf,Password_Read,sizeof(Password_dat1)))
			{
				LcdShowStr(0,0,"Password Correct  ");
				LcdShowStr(0,1,"Unlocked Now      ");	
				delay_01(1000);
				LcdWriteCmd(0x01); //����
				state = 3;  //�������״̬
			}
			else   //������������������������5�Σ���������״̬�������������
			{
				LcdShowStr(0,0,"Password Error    ");
				LcdShowStr(0,1,"Try again         ");
				delay_01(1000);
				LcdWriteCmd(0x01); //����				
				EnterCnt++;
				if(EnterCnt > 5)
				{				
					state = 4;
					EnterCnt = 0;
				}
			}
				cntBuf = 0;	
				Enter_Init();
				Fill_Number(PasswordBuf,'\0',MAX_LEN);
			break;
/////////////////////////////////////////////////////////////////////					
				/*������������״̬*/				
			case 1:
				Fill_Number(Password_dat1,'\0',MAX_LEN);
				Copy_Number(Password_dat1,PasswordBuf,sizeof(PasswordBuf));
				Fill_Number(PasswordBuf,'\0',MAX_LEN);
				state = 2;
				LcdShowStr(0,0,"Enter again     ");
				LcdShowStr(0,1,"                ");
				cntBuf = 0;
			break;
///////////////////////////////////////////////////////////////////////////////
				/*�ظ��������룬ȷ��Ϊ��ͬ�󱣴����벢���뿪����������ͬ����������*/	
			case 2:					
				if(CmpMemory(Password_dat1,PasswordBuf,sizeof(Password_dat1)))
				{
					Save_Password();
					Read_Password();
					LcdShowStr(0,0,"Successful   ");
					LcdShowStr(0,1,"Locked Now   ");
					state = 0;
				}
				else
				{
					LcdShowStr(0,0,"Password atypism ");
					LcdShowStr(0,1,"Please Reset    ");		
					state = 1;
				}
					cntBuf = 0;				
					delay_01(1500);
					LcdWriteCmd(0x01); //����		
					Enter_Init();
					Fill_Number(Password_dat1,'\0',MAX_LEN);
					Fill_Number(PasswordBuf,'\0',MAX_LEN);
			break;
///////////////////////////////////////////////////////////////////////////			
				/*������������*/
			case 3:
				LcdShowStr(0,0,"Reset Password   ");
				LcdShowStr(0,1,"                 ");
				delay_01(1500);
				LcdWriteCmd(0x01); //����	
				Fill_Number(PasswordBuf,'\0',MAX_LEN);
				cntBuf = 0;			
				state = 1;	
				Enter_Init();
			break;
///////////////////////////////////////////////////////////////////////////
				/*����״̬���»س��������������������������������*/
			case 4:
				LcdShowStr(0,0,"WARNING  ");
				LcdShowStr(0,1,"It's Locked ");
				Buzz_Warning();			
				LcdWriteCmd(0x01); //����	
				LcdShowStr(0,0,"Press Enter  ");
				LcdShowStr(0,1,"Reset Password  ");			
				state = 3;
				
			break;		
		}
	
	
}


void Key_Esc()
{

	Enter_Init();
	Fill_Number(PasswordBuf,'\0',MAX_LEN);
	cntBuf = 0;
		 
}


void Show_PSWcnt()
{
	unsigned char PSWcntbuf[MAX_LEN+1];

		Copy_Number(PSWcntbuf,PasswordBuf,MAX_LEN);
		Fill_Number(PSWcntbuf+cntBuf,'\0',sizeof(PSWcntbuf)-cntBuf);
		LcdShowStr(0,1,PSWcntbuf);
}



void Copy_Number(unsigned char *out,unsigned char *in,unsigned char len)
{
	while(len--)
	{
		*out++ = *in++;
	}
}

void Fill_Number(unsigned char *dat,unsigned char byt,unsigned char len)
{
	while(len--)
	{
		*dat++ = byt++;
	}
}

/* ���������鰴λ�ۼӵõ������ΪУ��λ */
unsigned char PSW_Check(unsigned char *dat,unsigned char len)
{
	unsigned char sum = 0;
	
	while(len--)
	{
		sum += *dat++;
	}
	return sum;
}

/*��ȡ���벢��֮ǰ������������һλ����У��*/
bit Read_Password()
{
	unsigned char savebuf2[MAX_LEN+1];
	unsigned char sum;
	
	E2Read(savebuf2,SAVE_ADDR,MAX_LEN+1);
	sum = PSW_Check(savebuf2,MAX_LEN);
	if(savebuf2[MAX_LEN] == ~sum)
	{
		Copy_Number(Password_Read,savebuf2,MAX_LEN);
		return 1;
	}
	else
	{
		Fill_Number(Password_Read,'\0',MAX_LEN);
		return 0;
	}
}


/*��������������һλ���У��λ�󱣴���EEPROM��*/
void Save_Password()
{
	unsigned char savebuf1[MAX_LEN+1];

	Copy_Number(savebuf1,Password_dat1,MAX_LEN);
	savebuf1[MAX_LEN] = ~PSW_Check(savebuf1,MAX_LEN);
	E2Write(savebuf1,SAVE_ADDR,MAX_LEN+1);
}




bit CmpMemory(unsigned char *ptr1, unsigned char *ptr2, unsigned char len)
{
    while (len--)
    {
        if (*ptr1++ != *ptr2++)  //�������������ʱ���̷���0
        {
            return 0;
        }
    }
    return 1;  //�Ƚ���ȫ���������ݶ�����򷵻�1
}
///* ��һ�ַ��������16�ֽڵĹ̶������ַ��������㲿�ֲ��ո�
//   out-�������ַ������ָ�룬in-�������ַ���ָ�� */
//void TrimString16(unsigned char *out, unsigned char *in)
//{
//    unsigned char i = 0;
//    
//    while (*in != '\0')  //�����ַ���ֱ�������ַ�������
//    {
//        *out++ = *in++;
//        i++;
//        if (i >= 16)    //�����������Ѵﵽ16�ֽ�ʱ��ǿ������ѭ��
//        {
//            break;
//        }
//    }
//    for ( ; i<16; i++)  //�粻��16���ֽ����ÿո���
//    {
//        *out++ = ' ';
//    }
//    *out = '\0';        //�����ӽ�����
//}




void KeyAction(unsigned char keycode)     //��������������keycodeΪ��������
{	
	if((keycode >= 0x30) && (keycode <= 0x39))
	{
		OpenBuzz(NoteFrequ[keycode-0x30]);
		delay_02(10);
		StopBuzz();
		
    Key_Number(keycode);
	}

	else if(keycode == 0x0D)    //�س��� ��������
	{
		OpenBuzz(2768);
		delay_02(10);
		StopBuzz();				
		
    Key_Enter();		
	}
	else if(keycode == 0x1B)    //Esc������
	{
		OpenBuzz(2349);
		delay_02(10);
		StopBuzz();				
		
		Key_Esc();
	}
}










