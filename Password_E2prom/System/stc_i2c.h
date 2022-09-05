#ifndef _STC_I2C_H_
#define _STC_I2C_H_

#define I2CDelay() {_nop_();_nop_();_nop_();_nop_();}



void I2CStart();
void I2CStop();

bit I2CWrite(unsigned char dat);

unsigned char I2CReadNAK();

unsigned char I2CReadACK();















#endif