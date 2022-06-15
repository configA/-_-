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
};//声明类型的同时定义s1,s2两个全局的结构体变量

struct Washing_time
{
	u8 Wat;//进水时间
	u8 Was;//洗涤时间
	u8 Ri;//漂洗时间
	u8 De;//脱水时间
};


extern code struct STU const Coord[];
extern code struct STU const Plan[];	
extern code struct STU const Custom[];

void delay_10us(u16 us);
void delay_ms(u16 ms);


#endif
