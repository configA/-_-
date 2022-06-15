#include "public.h"  
#include "uart.h"
#include "tftlcd.h"
#include "touch.h"
#include "gui.h"

//#define PROGRESSBAR_START_X		10	  	//进度条起始X坐标
//#define PROGRESSBAR_START_Y		30		//进度条起始Y坐标
#define PROGRESSBAR_WIDTH		200		//进度条长
#define PROGRESSBAR_HEIGHT		10		//进度条高

#define PROGRESSBAR_BACKCOLOR	GREEN  	//背景色
#define PROGRESSBAR_FRONTCOLOR	RED   	//前景色
#define PROGRESSBAR_FONTCOLOR	BLUE   //进度数值颜色

void ProgressBar_Show(u8 percent,u8 PROGRESSBAR_START_X,u8 PROGRESSBAR_START_Y);
void ProgressBar_Test(u8 PROGRESSBAR_START_X,u8 PROGRESSBAR_START_Y);
//开始的时间  所需的时间  现在的时间 x坐标 y坐标
void Progress_Bar(u16 Start,u16 Time_Required,u16 Now_Time,u8 X,u8 Y);