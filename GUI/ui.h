#include "tftlcd.h"
#include "touch.h"
#include "gui.h"
#include "Progress.h"
#include "public.h"


#define Initialization 	 1 //初始化界面为1
#define Customize  			 0 //自定义界面为0

void Mode_Selection();//初始化界面
//行号与上一次的行号  从第0行开始
void Choice(u8 line,u8 line_old,u8 Interface);//选中时标红
void Schedule();//进度表界面
void Custom_Time();//时间设置界面