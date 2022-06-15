#include "Progress.h"
extern unsigned int Start_Time;//起始时间
extern unsigned int count;//运行时间
extern unsigned char indicate;
struct Washing_time M_Time[4] = {//各个模式时间的结构体  0进水 1洗涤 2漂洗 3脱水
{15,15,15,10},			//强力模式
{10,10,10,8},
{5,5,5,3},
{0,0,0,0}};

//进度条显示
//percent：进度，百分数
void ProgressBar_Show(u8 percent,u8 PROGRESSBAR_START_X,u8 PROGRESSBAR_START_Y)
{
	//static u8 int_flag=0;
	u8 temp[4];
	u8 color_temp=0;
	u8 font_size=12;
	u8 progress;//进度条的实际长度
	
	progress = (percent*PROGRESSBAR_WIDTH)/100;
	color_temp=BACK_COLOR;//背景色 
	if(percent<10)
	{
		temp[0]=' ';
		temp[1]=' ';
		temp[2]=percent%100%10+0x30;//显示个位	
	}	
	else if(percent<100)
	{
		temp[0]=' ';
		temp[1]=percent%100/10+0x30;
		temp[2]=percent%100%10+0x30;//显示两位数
	}
	else
	{
		temp[0]=percent/100+0x30;
		temp[1]=percent%100/10+0x30;
		temp[2]=percent%100%10+0x30;//显示100	
	}		
	temp[3]='%';
//	if(int_flag==0) //只进行一次初始化
//	{
//		int_flag=1;
//		gui_fill_rectangle(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,PROGRESSBAR_WIDTH,PROGRESSBAR_HEIGHT,PROGRESSBAR_BACKCOLOR);//填充矩形		
//	}
	gui_fill_rectangle(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,progress,PROGRESSBAR_HEIGHT,PROGRESSBAR_FRONTCOLOR);
	if(percent>(PROGRESSBAR_WIDTH/2))
	{
		gui_show_strmidex(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,PROGRESSBAR_WIDTH,PROGRESSBAR_HEIGHT,PROGRESSBAR_FONTCOLOR,font_size,temp,1);	
	}
	else
	{
		BACK_COLOR=PROGRESSBAR_BACKCOLOR;
		gui_show_strmidex(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,PROGRESSBAR_WIDTH,PROGRESSBAR_HEIGHT,PROGRESSBAR_FONTCOLOR,font_size,temp,0);	
	}	
	BACK_COLOR=color_temp;
}



//开始的时间  所需的时间  现在的时间 进度条的位置
void Progress_Bar(u16 Start,u16 Time_Required,u16 Now_Time,u8 X,u8 Y)
{
	u8 Percentage=0;//百分比
	u16 time=0;
	Percentage = ((float)(Now_Time - Start)/(Time_Required))*100;//计算百分比
	//gui_fill_rectangle(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,PROGRESSBAR_WIDTH,PROGRESSBAR_HEIGHT,PROGRESSBAR_BACKCOLOR);
	printf("Now=%d Start=%d Req=%d %d\r\n",Now_Time,Start,Time_Required,(u16)Percentage);
	ProgressBar_Show((u8)Percentage,X,Y);
	if(Percentage >= 100)
	{
		Start_Time = count;//为下一个过程的起始时间做准备
		if(++indicate == 6)  indicate = 0;
	}
}

