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
			case 0://输入密码正确，进入解锁状态	
			if(CmpMemory(PasswordBuf,Password_Read,sizeof(Password_dat1)))
			{
				LcdShowStr(0,0,"Password Correct  ");
				LcdShowStr(0,1,"Unlocked Now      ");	
				delay_01(1000);
				LcdWriteCmd(0x01); //清屏
				state = 3;  //进入解锁状态
			}
			else   //输入密码错误，若输入次数超过5次，进入锁定状态，输入次数重置
			{
				LcdShowStr(0,0,"Password Error    ");
				LcdShowStr(0,1,"Try again         ");
				delay_01(1000);
				LcdWriteCmd(0x01); //清屏				
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
				/*按键设置密码状态*/				
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
				/*重复输入密码，确认为相同后保存密码并进入开锁程序，若不同则重新设置*/	
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
					LcdWriteCmd(0x01); //清屏		
					Enter_Init();
					Fill_Number(Password_dat1,'\0',MAX_LEN);
					Fill_Number(PasswordBuf,'\0',MAX_LEN);
			break;
///////////////////////////////////////////////////////////////////////////			
				/*重新设置密码*/
			case 3:
				LcdShowStr(0,0,"Reset Password   ");
				LcdShowStr(0,1,"                 ");
				delay_01(1500);
				LcdWriteCmd(0x01); //清屏	
				Fill_Number(PasswordBuf,'\0',MAX_LEN);
				cntBuf = 0;			
				state = 1;	
				Enter_Init();
			break;
///////////////////////////////////////////////////////////////////////////
				/*锁定状态按下回车键发出警报，进入重新设置密码程序*/
			case 4:
				LcdShowStr(0,0,"WARNING  ");
				LcdShowStr(0,1,"It's Locked ");
				Buzz_Warning();			
				LcdWriteCmd(0x01); //清屏	
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

/* 将密码数组按位累加得到结果作为校验位 */
unsigned char PSW_Check(unsigned char *dat,unsigned char len)
{
	unsigned char sum = 0;
	
	while(len--)
	{
		sum += *dat++;
	}
	return sum;
}

/*读取密码并与之前保存的密码最后一位进行校验*/
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


/*将输入的密码最后一位添加校验位后保存在EEPROM中*/
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
        if (*ptr1++ != *ptr2++)  //遇到不相等数据时即刻返回0
        {
            return 0;
        }
    }
    return 1;  //比较完全部长度数据都相等则返回1
}
///* 将一字符串整理成16字节的固定长度字符串，不足部分补空格
//   out-整理后的字符串输出指针，in-待整理字符串指针 */
//void TrimString16(unsigned char *out, unsigned char *in)
//{
//    unsigned char i = 0;
//    
//    while (*in != '\0')  //拷贝字符串直到输入字符串结束
//    {
//        *out++ = *in++;
//        i++;
//        if (i >= 16)    //当拷贝长度已达到16字节时，强制跳出循环
//        {
//            break;
//        }
//    }
//    for ( ; i<16; i++)  //如不足16个字节则用空格补齐
//    {
//        *out++ = ' ';
//    }
//    *out = '\0';        //最后添加结束符
//}




void KeyAction(unsigned char keycode)     //按键动作函数，keycode为按键键码
{	
	if((keycode >= 0x30) && (keycode <= 0x39))
	{
		OpenBuzz(NoteFrequ[keycode-0x30]);
		delay_02(10);
		StopBuzz();
		
    Key_Number(keycode);
	}

	else if(keycode == 0x0D)    //回车键 发送数据
	{
		OpenBuzz(2768);
		delay_02(10);
		StopBuzz();				
		
    Key_Enter();		
	}
	else if(keycode == 0x1B)    //Esc键清零
	{
		OpenBuzz(2349);
		delay_02(10);
		StopBuzz();				
		
		Key_Esc();
	}
}










