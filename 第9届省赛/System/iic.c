#include "iic.h"

#define DELAY_TIME 40


unsigned char EEPROM_Read(unsigned char addr)
{
	unsigned char dat;
	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();

	IIC_Start();
	IIC_SendByte(0xA1);
	IIC_WaitAck();

	dat = IIC_RecByte();
	IIC_Stop();
	
	return dat;
}

void EEPROM_Write(unsigned char addr,unsigned char dat)
{
	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();
	IIC_SendByte(dat);
	IIC_WaitAck();
	IIC_Stop();	
}

void PCF8591Init()
{
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();
	IIC_SendByte(0x43);
	IIC_WaitAck();
	IIC_Stop();	
}

unsigned char AD_RB2_AIN3()
{
	unsigned char output = 0;
	PCF8591Init();
	
	IIC_Start();
	IIC_SendByte(0x91);
	IIC_WaitAck();
	
	output = IIC_RecByte();
	IIC_SendAck(1);
	IIC_Stop();
	
	return output;
}





//I2C�����ڲ���ʱ����
void IIC_Delay(unsigned char i)
{
    do{_nop_();}
    while(i--);        
}

//I2C���������ź�
void IIC_Start(void)
{
    SDA = 1;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 0;
    IIC_Delay(DELAY_TIME);
    SCL = 0;	
}

//I2C����ֹͣ�ź�
void IIC_Stop(void)
{
    SDA = 0;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//����Ӧ����Ӧ���ź�
void IIC_SendAck(bit ackbit)
{
    SCL = 0;
    SDA = ackbit;  					
    IIC_Delay(DELAY_TIME);
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SCL = 0; 
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//�ȴ�Ӧ��
bit IIC_WaitAck(void)
{
    bit ackbit;
	
    SCL  = 1;
    IIC_Delay(DELAY_TIME);
    ackbit = SDA;
    SCL = 0;
    IIC_Delay(DELAY_TIME);
    return ackbit;
}

//I2C���߷���һ���ֽ�����
void IIC_SendByte(unsigned char byt)
{
    unsigned char i;

    for(i=0; i<8; i++)
    {
        SCL  = 0;
        IIC_Delay(DELAY_TIME);
        if(byt & 0x80) SDA  = 1;
        else SDA  = 0;
        IIC_Delay(DELAY_TIME);
        SCL = 1;
        byt <<= 1;
        IIC_Delay(DELAY_TIME);
    }
    SCL  = 0;  
}

//I2C���߽���һ���ֽ�����
unsigned char IIC_RecByte(void)
{
    unsigned char i, da;
    for(i=0; i<8; i++)
    {   
    	SCL = 1;
	IIC_Delay(DELAY_TIME);
	da <<= 1;
	if(SDA) da |= 1;
	SCL = 0;
	IIC_Delay(DELAY_TIME);
    }
    return da;    
}
