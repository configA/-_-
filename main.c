#include "STDIO.H"
#include "REG52.H"
#include "bsp_key.h"
#include "public.h"
#include "bsp_time.h"
#include "uart.h"
#include "tftlcd.h"
#include "touch.h"
#include "gui.h"
#include "Progress.h"
#include "ui.h"
//-----主要函数
void key_proc(void);
void tft_proc(void);
//-----定时器变量
long time_tick=0; 
unsigned int key_delay=0;//按键函数减速变量
unsigned int tft_delay=0;//液晶屏函数减速变量
unsigned int count=0;//运行时间
unsigned int count_old=999;//上一次的运行时间用于在时间改变时改变液晶屏
unsigned char key_val=0;//读取到的按键值
unsigned char key_old=0,key_down=0;//上一次的变量 按键的下降沿
unsigned char key_time=0;//用于判断是否是长按
unsigned char key_long=0;//长按标志位 长按时为1
unsigned char key_flag=0;//长按开始的时候置1
//-----全局变量
unsigned char interface=1;//界面选择  1初始化界面 2进度表界面 3自定义时间界面
unsigned char BUF[20];//字符串缓存区域
unsigned char line=0;//光标选择的行号
unsigned char line_old;//光标选择上一次的行号
extern struct Washing_time M_Time[4];//声明外部各个模式时间的结构体
extern code struct STU const Custom[];//声明自定义界面的结构体

unsigned char Laundry_Mode=0; //洗衣模式 0强力模式 1标准模式 2快速模式
unsigned char indicate=0;//0无  1进水 2洗涤 3漂洗 4脱水 5 6结束
unsigned int Start_Time=0;//存放过程的起始时间
unsigned char Temporary_time[4] = {0,0,0,0};//储存自定义模式时间的中间变量
unsigned char Position[4]={125,117,101,149};//液晶屏文字后数字所在的位置

/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{	
	UART_Init();//串口初始化
	TFTLCD_Init();//液晶屏初始化
	Mode_Selection();//初始化界面 选择需要哪个模式
	//ProgressBar_Test();
	time0_init();//定时器初始化
	printf("init OK\r\n");//串口重定向输出调试信息
	while(1)
	{		
		key_proc();//按键函数
		tft_proc();//液晶屏函数
	}		
}



/***********************定时器0中断函数(10ms)***********************/
void time0() interrupt 1 
{
	time_tick ++;
	TH0=0XD8;	//给定时器赋初值，定时10ms
	TL0=0XF0;
	if(key_delay)//只有不等于0的时候可以加
		key_delay = 0;//10ms扫描一次按键
	
	if(tft_delay)//只有不等于0的时候可以加
		if(++tft_delay == 40) tft_delay = 0;//400ms进一次液晶屏函数
	
	if(!(time_tick % 100))
		count++;//运行时间
}

/***********************按键函数和液晶屏大范围变化函数***********************/
void key_proc(void)
{
	if(key_delay) return;//时间没有到就返回
		else key_delay = 1;
	key_val = key_scan();//读取独立按键函数
	key_down = key_val & (key_val ^ key_old);//读取下降沿 如果不是下降沿则为0
	
	if((key_val == 6)&&(key_old == 0))//6刚按下时
	{
		key_flag = 1;//表示第一次按下
		key_down = 0;//先不进switch
	}
	
	if(key_flag)
		key_time++;//按键函数大概10ms进一次 所以10ms加一次	
	
	if((key_val == 0)&&(key_old == 6))//6放开时判断是否是长按
	{	
		if(key_time >= 100)
			key_long = 1;//长按标志位置1
		else
			key_long = 0;//长按标志位置0
		key_flag = 0;//标志位清0
		key_time = 0;//时间清0
		key_down = 6;//进switch
	}
	if(key_down != 0)
		printf("%d\r\n",(u16)key_down);//出现下降沿时输出调试信息
	
	switch(key_down)//各个按键的变化
    {
		
		case 1://在界面一和三时为向上移动光标
			if(--line == 255) line = 3;			
			if(interface == 1)//向上选择按钮
				Choice(line,line_old,Initialization);//选中时标红 输入参数为 行号 上一个的行号 和界面编号
			else if(interface == 3)
				Choice(line,line_old,Customize);//选中时标红 输入参数为 行号 上一个的行号 和界面编号
			
		break;
				
		case 5://在界面一和三时为向下移动光标
			if(++line == 4) line = 0;
			if(interface == 1)//向上选择按钮
				Choice(line,line_old,Initialization);//选中时标红 输入参数为 行号 上一个的行号 和界面编号
			else if(interface == 3)
				Choice(line,line_old,Customize);//选中时标红 输入参数为 行号 上一个的行号 和界面编号
		break;
		
		case 6: 
		if((interface == 3) && (key_long == 1))//为长按时为确定
		{
			//在自定义界面时为将临时的时间数组赋值给结构体
			M_Time[3].Wat=(u16)Temporary_time[0];//按确定以后赋值时间
			M_Time[3].Was=(u16)Temporary_time[1];
			M_Time[3].Ri=(u16)Temporary_time[2];
			M_Time[3].De=(u16)Temporary_time[3];
			printf("%d,%d,%d,%d\r\n",(u16)M_Time[3].Wat,(u16)M_Time[3].Was,(u16)M_Time[3].Ri,(u16)M_Time[3].De);//输出调试信息
			interface = 2;//界面切换到进度条界面
			Schedule();//进度表界面
			Laundry_Mode = 3;//模式为自定义模式
			Start_Time = count;//赋值进水起始时间
			indicate = 1;//进程为进水
		}else if((interface == 3) && (key_long == 0))//为短按时为时间减
		{
				if(Temporary_time[line] >= 5)//大于5才可以减
					Temporary_time[line] -= 5;//对应时间-5
				sprintf(BUF,"%02d",(u16)Temporary_time[line]);//格式化字符串
				LCD_ShowString(Position[line],Custom[line].y,tftlcd_data.width,tftlcd_data.height,16,BUF);//液晶屏输出
		}
		
		if(interface == 1)//在模式界面时为确定按钮
		{
				if(line != 3)//不是自定义模式时
				{
					interface = 2;//进度条界面
					Schedule();//进度表界面
					Laundry_Mode = line;//模式为行号
					Start_Time = count;//赋值进水起始时间
					indicate = 1;//进程为进水
				}else
				{
					line = 0;//行数清0
					Custom_Time();//自定义界面
					interface = 3;//界面3 自定义模式
				}
		 }
		if(indicate == 6)//但洗衣结束时按下按键6可以再来一次
		{
			indicate=0;
			interface=1;//初始化界面
			line = 0;//行数清0
			LCD_Clear(BACK_COLOR);//清屏为黑色
			Mode_Selection();//初始化界面 选择需要哪个模式
		}
			
		break;
		
		case 2:
			if(interface == 3)//在自定义界面时
			{
				if(Temporary_time[line] <= 95)//时间不能超过100
					Temporary_time[line] += 5;//对应时间+5
				sprintf(BUF,"%02d",(u16)Temporary_time[line]);//格式化字符串
				LCD_ShowString(Position[line],Custom[line].y,tftlcd_data.width,tftlcd_data.height,16,BUF);//液晶屏输出
			}
		break;		
	}
	key_old = key_val;//为上一次的按键值赋值
	line_old = line;//读取上一次的行号
}

/***********************液晶屏小范围变化函数***********************/
void tft_proc(void)
{
	if(tft_delay) return;//没到时间返回主函数
		else tft_delay = 1;
	if(count != count_old)//当时间改变时
	{
		sprintf(BUF,"%u",(u16)count);//格式时间为字符串
		FRONT_COLOR=WHITE;
		LCD_ShowString(109,300,tftlcd_data.width,tftlcd_data.height,16,BUF);//将时间显示在屏幕上
		switch (indicate)//0无  1进水 2洗涤 3漂洗 4脱水
    {
      	case 1://进水进度条
					Progress_Bar(Start_Time,M_Time[Laundry_Mode].Wat,count,10,70);//进度条函数
      	break;
				
      	case 2://洗涤进度条
					Progress_Bar(Start_Time,M_Time[Laundry_Mode].Was,count,10,110);
      	break;
				
				case 3://漂洗进度条
					Progress_Bar(Start_Time,M_Time[Laundry_Mode].Ri,count,10,150);
      	break;
				
				case 4://脱水进度条
					Progress_Bar(Start_Time,M_Time[Laundry_Mode].De,count,10,190);
      	break;
				
				case 5://结束
					LCD_ShowString(Plan[4].x,Plan[4].y,tftlcd_data.width,tftlcd_data.height,16,Plan[4].str);//液晶屏输出
					indicate++;//防止一直输出
				break;	
      }
	
		count_old = count;//为上一次的时间赋值
	}
}


