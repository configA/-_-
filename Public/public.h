#ifndef _public_H
#define _public_H

#include "reg52.h" 
#include "intrins.h"

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;


typedef enum 
{
	DISABLE = 0, ENABLE = !DISABLE
}FunctionalState;


struct STU 
{
	u16 x;
	u16 y;
	u8 str[20];
};//�������͵�ͬʱ����s1,s2����ȫ�ֵĽṹ�����

struct Washing_time
{
	u8 Wat;//��ˮʱ��
	u8 Was;//ϴ��ʱ��
	u8 Ri;//Ưϴʱ��
	u8 De;//��ˮʱ��
};


extern code struct STU const Coord[];
extern code struct STU const Plan[];	
extern code struct STU const Custom[];

void delay_10us(u16 us);
void delay_ms(u16 ms);


#endif
