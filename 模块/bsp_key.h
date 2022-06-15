#include "reg52.h"
#include "delay.h"



//定义独立按键控制脚
sbit KEY1=P3^4;
sbit KEY2=P3^5;
sbit KEY5=P3^6;
sbit KEY6=P3^7;




unsigned char key_scan();