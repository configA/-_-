#include "tftlcd.h"
#include "font.h" 
#include "uart.h"
#include "stdlib.h"



//LCD的画笔颜色和背景色	   
u16 FRONT_COLOR=WHITE;	//画笔颜色
u16 BACK_COLOR=BLACK;  //背景色 

_tftlcd_data tftlcd_data; 

void Delay(unsigned int dly)
{
    unsigned int i,j;

    for(i=0;i<dly;i++)
    	for(j=0;j<255;j++);
}
//写寄存器函数
//cmd:寄存器值
void LCD_WriteCmd(u16 cmd)
{
#ifdef TFT20_HX8309
	unsigned char cmdH, cmdL;
	cmdH = cmd >> 8;
	cmdL = cmd & 0x00FF;

	TFT_WR = 1;	 		  //初始化WR
	TFT_CS = 0;			  //打开片选
	
	TFT_RD = 1;           //选择写
	TFT_RS = 0;			  //选择命令
		
	TFT_DATAPORTH = cmdH; //放置命令数据
	TFT_DATAPORTL = cmdL; //放置命令数据

	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	
	TFT_CS = 1;			  //关闭片选
#endif

#ifdef TFT22_R61503B
	unsigned char cmdH, cmdL;
	cmdH = cmd >> 8;
	cmdL = cmd & 0x00FF;
	
	
	TFT_WR = 1;	 		  //初始化WR
	TFT_CS = 0;			  //打开片选
	
	TFT_RD = 1;           //选择写
	TFT_RS = 0;			  //选择命令
	
	
	TFT_DATAPORTH = cmdH; //放置命令数据
	TFT_WR = 0;			  //写入时序
	
	TFT_WR = 1;
	TFT_DATAPORTH = cmdL;
	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	
	TFT_CS = 1;			  //关闭片选 
#endif

#ifdef TFT22_ILI9225B
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=0;

 	TFT_DATAPORTH=cmd>>8;
	TFT_WR=0;
 	TFT_WR=1;

 	TFT_DATAPORTH=cmd&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;
#endif

#ifdef TFT24_ST7781R	
	TFT_CS=0;
 	TFT_RS=0;
 	TFT_DATAPORTH=cmd>>8;
 	TFT_DATAPORTL=cmd;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;
#endif

#ifdef TFT26_R61509V	
	TFT_CS=0;
 	TFT_RS=0;
 	TFT_DATAPORTH=cmd>>8;
 	TFT_DATAPORTL=cmd;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;
#endif

#ifdef TFT26_ILI9325D	
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=0;

 	TFT_DATAPORTL=cmd>>8;
	TFT_WR=0;
 	TFT_WR=1;

 	TFT_DATAPORTL=cmd&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;
#endif

#ifdef TFT24_ST7789S	
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=0;
 	TFT_DATAPORTH=cmd;
	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;
#endif

#ifdef TFT24_SSD1297	
	TFT_CS=0;
 	TFT_RS=0;
 	TFT_DATAPORTH=cmd>>8;
 	TFT_DATAPORTL=cmd;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;
#endif

#ifdef TFT20_ILI9225
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=0;

 	TFT_DATAPORTH=cmd>>8;
	TFT_WR=0;
 	TFT_WR=1;

 	TFT_DATAPORTH=cmd&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;
#endif

#ifdef TFT20_ILI9341
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=0;
 	TFT_DATAPORTH=cmd;
	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;
#endif

#ifdef TFT20_ST7775R	
	TFT_CS=0;
 	TFT_RS=0;
 	TFT_DATAPORTH=cmd>>8;
 	TFT_DATAPORTL=cmd;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;
#endif

#ifdef TFT20_ST7775RV	
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=0;

 	TFT_DATAPORTL=cmd>>8;
	TFT_WR=0;
 	TFT_WR=1;

 	TFT_DATAPORTL=cmd&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;
#endif

#ifdef TFT20_ILI9225C
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=0;

 	TFT_DATAPORTL=cmd>>8;
	TFT_WR=0;
 	TFT_WR=1;

 	TFT_DATAPORTL=cmd&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;
#endif

#ifdef TFT20_R61503U	
	TFT_CS=0;
 	TFT_RS=0;
 	TFT_DATAPORTH=cmd>>8;
 	TFT_DATAPORTL=cmd;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;
#endif

#ifdef TFT20_HX8340B
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=0;
 	TFT_DATAPORTH=cmd;
	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;
#endif

#ifdef TFT24_HX8357A	
	TFT_CS=0;
 	TFT_RS=0;
 	TFT_DATAPORTH=cmd>>8;
 	TFT_DATAPORTL=cmd;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;
#endif

#ifdef TFT18_S6D0144	
	TFT_CS=0;
 	TFT_RS=0;
 	TFT_DATAPORTH=cmd>>8;
 	TFT_DATAPORTL=cmd;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;
#endif
}

//写数据
//dat:要写入的值
void LCD_WriteData(u16 dat)
{
#ifdef TFT20_HX8309
	unsigned char datH, datL;
	datH = dat >> 8;
	datL = dat & 0x00FF;

	TFT_WR = 1;	 		  //初始化WR
	TFT_CS = 0;			  //打开片选
	
	TFT_RD = 1;           //选择写
	TFT_RS = 1;			  //选择发送数据
		
	TFT_DATAPORTH = datH;  //放置命令数据
	TFT_DATAPORTL = datL;  //放置命令数据

	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	
	TFT_CS = 1;			  //关闭片选
#endif

#ifdef TFT22_R61503B
	unsigned char datH, datL;
	datH = dat >> 8;
	datL = dat & 0xFF;
	
	TFT_WR = 1;	 		  //初始化WR
	TFT_CS = 0;			  //打开片选
		
	TFT_RD = 1;           //选择写
	TFT_RS = 1;			  //选择发送数据
	

	TFT_DATAPORTH = datH;  //放置命令数据
	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;

	TFT_DATAPORTH = datL;	

	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	
	 TFT_CS = 1;			  //关闭片选
#endif
#ifdef TFT22_ILI9225B
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;
		 
 	TFT_DATAPORTH=dat>>8;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_DATAPORTH=dat&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;	
#endif

#ifdef TFT24_ST7781R
	TFT_CS=0;
 	TFT_RS=1;	 
 	TFT_DATAPORTH=dat>>8;
 	TFT_DATAPORTL=dat;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif

#ifdef TFT26_R61509V
	TFT_CS=0;
 	TFT_RS=1;	 
 	TFT_DATAPORTH=dat>>8;
 	TFT_DATAPORTL=dat;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif	

#ifdef TFT26_ILI9325D
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;
		 
 	TFT_DATAPORTL=dat>>8;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_DATAPORTL=dat&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;	
#endif

#ifdef TFT24_ST7789S	
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;
 	TFT_DATAPORTH=dat;
	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;
#endif

#ifdef TFT24_SSD1297
	TFT_CS=0;
 	TFT_RS=1;	 
 	TFT_DATAPORTH=dat>>8;
 	TFT_DATAPORTL=dat;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif

#ifdef TFT20_ILI9225
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;
		 
 	TFT_DATAPORTH=dat>>8;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_DATAPORTH=dat&0xff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;	
#endif

#ifdef TFT20_ILI9341
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;
 	TFT_DATAPORTH=dat;
	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif

#ifdef TFT20_ST7775R
	TFT_CS=0;
 	TFT_RS=1;	 
 	TFT_DATAPORTH=dat>>8;
 	TFT_DATAPORTL=dat;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif

#ifdef TFT20_ST7775RV
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;
		 
 	TFT_DATAPORTL=dat>>8;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_DATAPORTL=dat&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;	
#endif

#ifdef TFT20_ILI9225C
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;
		 
 	TFT_DATAPORTL=dat>>8;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_DATAPORTL=dat&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;	
#endif

#ifdef TFT20_R61503U
	TFT_CS=0;
 	TFT_RS=1;	 
 	TFT_DATAPORTH=dat>>8;
 	TFT_DATAPORTL=dat;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif

#ifdef TFT20_HX8340B
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;
 	TFT_DATAPORTH=dat;
	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif

#ifdef TFT24_HX8357A
	TFT_CS=0;
 	TFT_RS=1;	 
 	TFT_DATAPORTH=dat>>8;
 	TFT_DATAPORTL=dat;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif

#ifdef TFT18_S6D0144
	TFT_CS=0;
 	TFT_RS=1;	 
 	TFT_DATAPORTH=dat>>8;
 	TFT_DATAPORTL=dat;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif	
}

void LCD_WriteData_Color(u16 color)
{
#ifdef TFT20_HX8309
	unsigned char datH, datL;
	datH = color >> 8;
	datL = color & 0x00FF;

	TFT_WR = 1;	 		  //初始化WR
	TFT_CS = 0;			  //打开片选
	
	TFT_RD = 1;           //选择写
	TFT_RS = 1;			  //选择发送数据
		
	TFT_DATAPORTH = datH;  //放置命令数据
	TFT_DATAPORTL = datL;  //放置命令数据

	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	
	TFT_CS = 1;			  //关闭片选
#endif

#ifdef TFT22_R61503B
	 unsigned char datH, datL;
	datH = color >> 8;
	datL = color & 0xFF;
	
	TFT_WR = 1;	 		  //初始化WR
	TFT_CS = 0;			  //打开片选
		
	TFT_RD = 1;           //选择写
	TFT_RS = 1;			  //选择发送数据
	

	TFT_DATAPORTH = datH;  //放置命令数据
	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;

	TFT_DATAPORTH = datL;	

	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	
	 TFT_CS = 1;			  //关闭片选
#endif
#ifdef TFT22_ILI9225B
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;
		 
 	TFT_DATAPORTH=color>>8;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_DATAPORTH=color&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;	
#endif

#ifdef TFT24_ST7781R
	TFT_CS=0;
 	TFT_RS=1;	 
 	TFT_DATAPORTH=color>>8;
 	TFT_DATAPORTL=color;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif

#ifdef TFT26_R61509V
	TFT_CS=0;
 	TFT_RS=1;	 
 	TFT_DATAPORTH=color>>8;
 	TFT_DATAPORTL=color;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif

#ifdef TFT26_ILI9325D
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;
		 
 	TFT_DATAPORTL=color>>8;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_DATAPORTL=color&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;	
#endif

#ifdef TFT24_ST7789S
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;	 
 	TFT_DATAPORTH=color>>8;
	TFT_WR = 0;			  
	TFT_WR = 1;
 	TFT_DATAPORTH=color&0xFF;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif

#ifdef TFT24_SSD1297
	TFT_CS=0;
 	TFT_RS=1;	 
 	TFT_DATAPORTH=color>>8;
 	TFT_DATAPORTL=color;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif

#ifdef TFT20_ILI9225
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;
		 
 	TFT_DATAPORTH=color>>8;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_DATAPORTH=color&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;	
#endif

#ifdef TFT20_ILI9341
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;
		 
 	TFT_DATAPORTH=color>>8;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_DATAPORTH=color&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;	
#endif

#ifdef TFT20_ST7775R
	TFT_CS=0;
 	TFT_RS=1;	 
 	TFT_DATAPORTH=color>>8;
 	TFT_DATAPORTL=color;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif

#ifdef TFT20_ST7775RV
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;
		 
 	TFT_DATAPORTL=color>>8;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_DATAPORTL=color&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;	
#endif

#ifdef TFT20_ILI9225C
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;
		 
 	TFT_DATAPORTL=color>>8;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_DATAPORTL=color&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;	
#endif

#ifdef TFT20_R61503U
	TFT_CS=0;
 	TFT_RS=1;	 
 	TFT_DATAPORTH=color>>8;
 	TFT_DATAPORTL=color;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif

#ifdef TFT20_HX8340B
	TFT_WR=1;
	TFT_CS=0;
	TFT_RD=1;
 	TFT_RS=1;
		 
 	TFT_DATAPORTH=color>>8;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_DATAPORTH=color&0x00ff;
 	TFT_WR=0;
 	TFT_WR=1;

 	TFT_CS=1;	
#endif

#ifdef TFT24_HX8357A
	TFT_CS=0;
 	TFT_RS=1;	 
 	TFT_DATAPORTH=color>>8;
 	TFT_DATAPORTL=color;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif

#ifdef TFT18_S6D0144
	TFT_CS=0;
 	TFT_RS=1;	 
 	TFT_DATAPORTH=color>>8;
 	TFT_DATAPORTL=color;
 	TFT_WR=0;
 	TFT_WR=1;
 	TFT_CS=1;	
#endif	
}

void LCD_WriteCmdData(u16 cmd,u16 dat)
{
	LCD_WriteCmd(cmd);
	LCD_WriteData(dat);
}

//读数据
//返回值:读到的值
u16 LCD_ReadData(void)
{
	u16 ram;

	TFT_DATAPORTH=0xff;
	TFT_DATAPORTL=0xff;

#ifdef TFT20_HX8309
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
	ram=TFT_DATAPORTH;
	ram<<=8;
	ram|=TFT_DATAPORTL;
	TFT_RD=1;	
 	TFT_CS=1;
#endif

#ifdef TFT22_R61503B
	
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
 	ram=TFT_DATAPORTH;
 	ram<<=8;	

	TFT_RD=1;	
	TFT_RD=0;
	_nop_();
	ram|=TFT_DATAPORTH;
	TFT_RD=1;
 	TFT_CS=1;
#endif

#ifdef TFT22_ILI9225B
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
 	ram=TFT_DATAPORTH;
 	ram<<=8;	

	TFT_RD=1;	
	TFT_RD=0;
	_nop_();
	ram|=TFT_DATAPORTH;
	TFT_RD=1;
 	TFT_CS=1;
#endif

#ifdef TFT24_ST7781R
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
	ram=TFT_DATAPORTH;
 	ram<<=8;
	ram|=TFT_DATAPORTL;	 
	TFT_RD=1;
 	TFT_CS=1;
#endif

#ifdef TFT26_R61509V
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
	ram=TFT_DATAPORTH;
	ram<<=8;
	ram|=TFT_DATAPORTL;
	TFT_RD=1;	
 	TFT_CS=1;
#endif

#ifdef TFT26_ILI9325D
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
	ram=TFT_DATAPORTL;
	ram<<=8;
	ram|=TFT_DATAPORTL;
	TFT_RD=1;	
 	TFT_CS=1;
#endif

#ifdef TFT24_ST7789S	
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
 	ram=TFT_DATAPORTH;	
	TFT_RD=1;
 	TFT_CS=1;
#endif

#ifdef TFT24_SSD1297
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
	ram=TFT_DATAPORTH;
	ram<<=8;
	ram|=TFT_DATAPORTL;
	TFT_RD=1;	
 	TFT_CS=1;
#endif

#ifdef TFT20_ILI9225
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
 	ram=TFT_DATAPORTH;
 	ram<<=8;	

	TFT_RD=1;	
	TFT_RD=0;
	_nop_();
	ram|=TFT_DATAPORTH;
	TFT_RD=1;
 	TFT_CS=1;
#endif

#ifdef TFT20_ILI9341
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
 	ram=TFT_DATAPORTH;
 	ram<<=8;	

	TFT_RD=1;	
	TFT_RD=0;
	_nop_();
	ram|=TFT_DATAPORTH;
	TFT_RD=1;
 	TFT_CS=1;
#endif

#ifdef TFT20_ST7775R
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
	ram=TFT_DATAPORTH;
	ram<<=8;
	ram|=TFT_DATAPORTL;
	TFT_RD=1;	
 	TFT_CS=1;
#endif

#ifdef TFT20_ST7775RV
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
	ram=TFT_DATAPORTL;
	ram<<=8;
	ram|=TFT_DATAPORTL;
	TFT_RD=1;	
 	TFT_CS=1;
#endif

#ifdef TFT20_ILI9225C
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
 	ram=TFT_DATAPORTL;
 	ram<<=8;	

	TFT_RD=1;	
	TFT_RD=0;
	_nop_();
	ram|=TFT_DATAPORTL;
	TFT_RD=1;
 	TFT_CS=1;
#endif

#ifdef TFT20_R61503U
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
	ram=TFT_DATAPORTH;
	ram<<=8;
	ram|=TFT_DATAPORTL;
	TFT_RD=1;	
 	TFT_CS=1;
#endif

#ifdef TFT20_HX8340B
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
 	ram=TFT_DATAPORTH;
 	ram<<=8;	

	TFT_RD=1;	
	TFT_RD=0;
	_nop_();
	ram|=TFT_DATAPORTH;
	TFT_RD=1;
 	TFT_CS=1;
#endif

#ifdef TFT24_HX8357A
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
	ram=TFT_DATAPORTH;
	ram<<=8;
	ram|=TFT_DATAPORTL;
	TFT_RD=1;	
 	TFT_CS=1;
#endif

#ifdef TFT18_S6D0144
	TFT_CS=0;
	TFT_RS=1;
	TFT_RD=0;
	_nop_();
	ram=TFT_DATAPORTH;
	ram<<=8;
	ram|=TFT_DATAPORTL;
	TFT_RD=1;	
 	TFT_CS=1;
#endif

	return ram;	
}

//设置LCD显示方向
//dir:0,竖屏；1,横屏
void LCD_Display_Dir(u8 dir)
{
	tftlcd_data.dir=dir;
	if(dir==0)  //默认竖屏方向
	{
#ifdef TFT20_HX8309
		LCD_WriteCmdData(0x0001,0x011b); //Output Direct
#endif
#ifdef TFT22_R61503B
		LCD_WriteCmdData(0x0001,0x0500); //Output Direct
		LCD_WriteCmdData(0x0003, 0x1030);   //设置彩屏显示方向的寄存器
#endif
#ifdef TFT22_ILI9225B		
		LCD_WriteCmdData(0x0001, 0x011C); //Output Direct
		LCD_WriteCmdData(0x0003, 0x1030);   //设置彩屏显示方向的寄存器
#endif

#ifdef TFT24_ST7781R		
		LCD_WriteCmdData(0x0001, 0x0100); //Output Direct
		LCD_WriteCmd(0x0003);   //设置彩屏显示方向的寄存器
		LCD_WriteData(0x5030);
#endif

#ifdef TFT26_R61509V		
		LCD_WriteCmdData(0x0001, 0x0100); //Output Direct
		LCD_WriteCmdData(0x0003, 0x1030);   //设置彩屏显示方向的寄存器
#endif

#ifdef TFT26_ILI9325D		
		LCD_WriteCmdData(0x0001, 0x0100); //Output Direct
		LCD_WriteCmdData(0x0003, 0x1030);   //设置彩屏显示方向的寄存器
#endif

#ifdef TFT24_ST7789S
		LCD_WriteCmdData(0x36,0x10); ///设置彩屏显示方向的寄存器  
#endif

#ifdef TFT24_SSD1297
		LCD_WriteCmdData(0x0011, 0x6830); //Output Direct		
		LCD_WriteCmdData(0x0001, 0x2B3F); //Output Direct
#endif

#ifdef TFT20_ILI9225		
		LCD_WriteCmdData(0x0001, 0x011C); //Output Direct
		LCD_WriteCmdData(0x0003, 0x1030);   //设置彩屏显示方向的寄存器
#endif

#ifdef TFT20_ILI9341		
		LCD_WriteCmdData(0x36, 0x08); //Output Direct
#endif

#ifdef TFT20_ST7775R
		LCD_WriteCmdData(0x01, 0x011C); //Output Direct
		LCD_WriteCmdData(0x03, 0x1030); //Output Direct		
#endif

#ifdef TFT20_ST7775RV
		LCD_WriteCmdData(0x01, 0x011C); //Output Direct
		LCD_WriteCmdData(0x03, 0x1030); //Output Direct		
#endif

#ifdef TFT20_ILI9225C		
		LCD_WriteCmdData(0x0001, 0x011C); //Output Direct
		LCD_WriteCmdData(0x0003, 0x1030);   //设置彩屏显示方向的寄存器
#endif

#ifdef TFT20_R61503U		
		LCD_WriteCmdData(0x0001, 0x0100); //Output Direct
		LCD_WriteCmdData(0x0003, 0x1030);   //设置彩屏显示方向的寄存器
#endif

#ifdef TFT20_HX8340B		
		LCD_WriteCmdData(0x01, 0x00); //Output Direct
#endif

#ifdef TFT24_HX8357A		
		LCD_WriteCmdData(0x16,0x08);
#endif

#ifdef TFT18_S6D0144		
		LCD_WriteCmdData(0x03,0x1030);
#endif

		tftlcd_data.height=HEIGHT;
		tftlcd_data.width=WIDTH;		
	}
	else
	{
#ifdef TFT20_HX8309
    	LCD_WriteCmdData(0x0001, 0x001b); //Output Direct
#endif

#ifdef TFT22_R61503B
    	LCD_WriteCmdData(0x0001, 0x0400); //Output Direct
		LCD_WriteCmdData(0x0003, 0x1038);   //设置彩屏显示方向的寄存器#endif
#endif

#ifdef TFT22_ILI9225B		
		LCD_WriteCmdData(0x0001, 0x031C); //Output Direct
		LCD_WriteCmdData(0x0003, 0x1038);   //设置彩屏显示方向的寄存器#endif
#endif

#ifdef TFT24_ST7781R
		LCD_WriteCmdData(0x0001, 0x0000); //Output Direct		
		LCD_WriteCmd(0x0003);   //设置彩屏显示方向的寄存器
		LCD_WriteData(0x5038);
#endif

#ifdef TFT26_R61509V		
		LCD_WriteCmdData(0x0001, 0x0000); //Output Direct
		LCD_WriteCmdData(0x0003, 0x1038);   //设置彩屏显示方向的寄存器
#endif

#ifdef TFT26_ILI9325D		
		LCD_WriteCmdData(0x0001, 0x0000); //Output Direct
		LCD_WriteCmdData(0x0003, 0x1038);   //设置彩屏显示方向的寄存器
#endif

#ifdef TFT24_ST7789S		
		LCD_WriteCmdData(0x36,0x60); ///设置彩屏显示方向的寄存器
#endif

#ifdef TFT24_SSD1297		
		LCD_WriteCmdData(0x0011, 0x6838); //Output Direct
		LCD_WriteCmdData(0x0001, 0x6B3F); //Output Direct
#endif

#ifdef TFT20_ILI9225		
		LCD_WriteCmdData(0x0001, 0x031C); //Output Direct
		LCD_WriteCmdData(0x0003, 0x1038);   //设置彩屏显示方向的寄存器#endif
#endif

#ifdef TFT20_ILI9341		
		LCD_WriteCmdData(0x36, 0x68); //Output Direct
#endif

#ifdef TFT20_ST7775R
		LCD_WriteCmdData(0x01, 0x031C); //Output Direct
		LCD_WriteCmdData(0x03, 0x1038); //Output Direct
#endif

#ifdef TFT20_ST7775RV
		LCD_WriteCmdData(0x01, 0x031C); //Output Direct
		LCD_WriteCmdData(0x03, 0x1038); //Output Direct
#endif

#ifdef TFT20_ILI9225C		
		LCD_WriteCmdData(0x0001, 0x031C); //Output Direct
		LCD_WriteCmdData(0x0003, 0x1038);   //设置彩屏显示方向的寄存器#endif
#endif

#ifdef TFT20_R61503U		
		LCD_WriteCmdData(0x0001, 0x031C); //Output Direct
		LCD_WriteCmdData(0x0003, 0x1038);   //设置彩屏显示方向的寄存器
#endif

#ifdef TFT20_HX8340B		
		LCD_WriteCmdData(0x01, 0x00); //Output Direct
#endif

#ifdef TFT24_HX8357A		
		LCD_WriteCmdData(0x16,0x48);//0x48
#endif

#ifdef TFT18_S6D0144
		LCD_WriteCmdData(0x03,0x1018);
		LCD_WriteCmdData(0x01,0x0714);
#endif

	   	tftlcd_data.height=WIDTH;
		tftlcd_data.width=HEIGHT;
	}
}


void TFTLCD_Init(void)
{
	u16 i=0;
	TFT_RST=1;  
	delay_ms(100);
	
	TFT_RST=0;
	delay_ms(100);

	TFT_RST=1;
	delay_ms(100);

	LCD_WriteCmd(0X0000);			   	
	tftlcd_data.id=LCD_ReadData();    

	LCD_WriteCmd(0x0000);LCD_WriteData(0x0001);//打开晶振
	delay_ms(500);
	
	LCD_WriteCmd(0x0003);LCD_WriteData(0x0003);//0xA8A4
	LCD_WriteCmd(0x000C);LCD_WriteData(0x0000);    
	LCD_WriteCmd(0x000D);LCD_WriteData(0x080C);   
	LCD_WriteCmd(0x000E);LCD_WriteData(0x2b000);//2B00    
	LCD_WriteCmd(0x001E);LCD_WriteData(0x00B0); 
	delay_ms(500);
	
	LCD_WriteCmd(0x0001);LCD_WriteData(0x693F);//驱动输出控制320*240  0x6B3F	0x2B3F
	LCD_WriteCmd(0x0002);LCD_WriteData(0x0600);
	LCD_WriteCmd(0x0010);LCD_WriteData(0x0000);  
	LCD_WriteCmd(0x0011);LCD_WriteData(0x6830); //定义数据格式  16位色 	横屏 0x6058   0x6078
	LCD_WriteCmd(0x0005);LCD_WriteData(0x0000);  
	LCD_WriteCmd(0x0006);LCD_WriteData(0x0000);  
	LCD_WriteCmd(0x0016);LCD_WriteData(0xEF1C);  
	LCD_WriteCmd(0x0017);LCD_WriteData(0x0003);  
	LCD_WriteCmd(0x0007);LCD_WriteData(0x0233); //0x0233       
	LCD_WriteCmd(0x000B);LCD_WriteData(0x0000);  
	delay_ms(500);
	
	LCD_WriteCmd(0x000F);LCD_WriteData(0x0000); //扫描开始地址
	LCD_WriteCmd(0x0041);LCD_WriteData(0x0000);  
	LCD_WriteCmd(0x0042);LCD_WriteData(0x0000);  
	LCD_WriteCmd(0x0048);LCD_WriteData(0x0000);  
	LCD_WriteCmd(0x0049);LCD_WriteData(0x013F);  
	LCD_WriteCmd(0x004A);LCD_WriteData(0x0000);  
	LCD_WriteCmd(0x004B);LCD_WriteData(0x0000); 
	 
	LCD_WriteCmd(0x0044);LCD_WriteData(0xEF00);  
	LCD_WriteCmd(0x0045);LCD_WriteData(0x0000);  
	LCD_WriteCmd(0x0046);LCD_WriteData(0x013F); 
	 
	LCD_WriteCmd(0x0030);LCD_WriteData(0x0707);  
	LCD_WriteCmd(0x0031);LCD_WriteData(0x0204);  
	LCD_WriteCmd(0x0032);LCD_WriteData(0x0204);  
	LCD_WriteCmd(0x0033);LCD_WriteData(0x0502);  
	LCD_WriteCmd(0x0034);LCD_WriteData(0x0507);  
	LCD_WriteCmd(0x0035);LCD_WriteData(0x0204);  
	LCD_WriteCmd(0x0036);LCD_WriteData(0x0204);  
	LCD_WriteCmd(0x0037);LCD_WriteData(0x0502);  
	LCD_WriteCmd(0x003A);LCD_WriteData(0x0302);  
	LCD_WriteCmd(0x003B);LCD_WriteData(0x0302);  
	LCD_WriteCmd(0x0023);LCD_WriteData(0x0000);  
	LCD_WriteCmd(0x0024);LCD_WriteData(0x0000);  
	LCD_WriteCmd(0x0025);LCD_WriteData(0x8000);  
	
	LCD_WriteCmd(0x004f);LCD_WriteData(0x0000);        //行首址0
	LCD_WriteCmd(0x004e);LCD_WriteData(0x0000);        //列首址0

	LCD_WriteCmd(0x0022);

	LCD_Display_Dir(TFTLCD_DIR);		//0：竖屏  1：横屏  默认竖屏
	LCD_Clear(BACK_COLOR);

}

//设置窗口,并自动设置画点坐标到窗口左上角(sx,sy).
//sx,sy:窗口起始坐标(左上角)
//width,height:窗口宽度和高度,必须大于0!!
//窗体大小:width*height. 
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height)
{
#ifdef TFT20_HX8309
	u16 x,y,xy;
	x=(width<<8)|sx;
	y=(height<<8)|sy;
	xy = (sy<<8)|sx;
	if(tftlcd_data.dir==0)	
	{
		LCD_WriteCmd(0x44);LCD_WriteData(x);
	 	LCD_WriteCmd(0x45);LCD_WriteData(y);
	 	LCD_WriteCmd(0x21);LCD_WriteData(xy);	
	}
	else
	{
		xy = (sx<<8)|sy;
		LCD_WriteCmd(0x45);LCD_WriteData(x);
	 	LCD_WriteCmd(0x44);LCD_WriteData(y);
	 	LCD_WriteCmd(0x21);LCD_WriteData(xy);
	}
	LCD_WriteCmd(0x22);
#endif

#ifdef TFT22_R61503B
	if(tftlcd_data.dir==0)	
	{
		LCD_WriteCmd(0x0050);
		LCD_WriteData(sx);     	 
		LCD_WriteCmd(0x0051);
		LCD_WriteData(width);  
		LCD_WriteCmd(0x0052);
		LCD_WriteData(sy);
		LCD_WriteCmd(0x0053);
		LCD_WriteData(height);

		LCD_WriteCmd(0x0020);
		LCD_WriteData(sx);
		LCD_WriteCmd(0x0021);
		LCD_WriteData(sy);

		LCD_WriteCmd(0x0022);
	
	}
	else
	{
		LCD_WriteCmd(0x0052);
		LCD_WriteData(sx);     	 
		LCD_WriteCmd(0x0053);
		LCD_WriteData(width);  
		LCD_WriteCmd(0x0050);
		LCD_WriteData(sy);
		LCD_WriteCmd(0x0051);
		LCD_WriteData(height);

		LCD_WriteCmd(0x0021);
		LCD_WriteData(sx);
		LCD_WriteCmd(0x0020);
		LCD_WriteData(sy);

		LCD_WriteCmd(0x0022);
	}
#endif
	
#ifdef TFT22_ILI9225B
	if(tftlcd_data.dir==0)	
	{
		LCD_WriteCmdData(0x0037, sx);
		LCD_WriteCmdData(0x0036, width); 
		LCD_WriteCmdData(0x0039, sy);
		LCD_WriteCmdData(0x0038, height);
	
		LCD_WriteCmdData(0x0020, sx);
		LCD_WriteCmdData(0x0021, sy);
	
		LCD_WriteCmd(0x0022);
	}
	else
	{
		LCD_WriteCmdData(0x0039, sx);
		LCD_WriteCmdData(0x0038, width); 
		LCD_WriteCmdData(0x0037, sy);
		LCD_WriteCmdData(0x0036, height);
	
		LCD_WriteCmdData(0x0021, sx);
		LCD_WriteCmdData(0x0020, sy);
	
		LCD_WriteCmd(0x0022);
	}
#endif

#ifdef TFT24_ST7781R
	if(tftlcd_data.dir==0)	
	{
		LCD_WriteCmdData(0x0050, sx); // Horizontal Address Start Position
		LCD_WriteCmdData(0x0051, width); // Horizontal Address End Position
		LCD_WriteCmdData(0x0052, sy); // Vertical Address Start Position
		LCD_WriteCmdData(0x0053, height); // Vertical Address End Position
	
		LCD_WriteCmdData(0x0020, sx); // Horizontal Address Start Position
		LCD_WriteCmdData(0x0021, sy); // Vertical Address Start Position
		LCD_WriteCmd(0x0022); 	
	}
	else
	{
		LCD_WriteCmdData(0x0052, sx); // Horizontal Address Start Position
		LCD_WriteCmdData(0x0053, width); // Horizontal Address End Position
		LCD_WriteCmdData(0x0050, sy); // Vertical Address Start Position
		LCD_WriteCmdData(0x0051, height); // Vertical Address End Position
	
		LCD_WriteCmdData(0x0021, sx); // Horizontal Address Start Position
		LCD_WriteCmdData(0x0020, sy); // Vertical Address Start Position
		LCD_WriteCmd(0x0022);	
	}	
#endif

#ifdef TFT26_R61509V
	if(tftlcd_data.dir==0)	
	{
		LCD_WriteCmd(0x0210);   LCD_WriteData(sx);
		LCD_WriteCmd(0x0211);   LCD_WriteData(width);
		LCD_WriteCmd(0x0212);   LCD_WriteData(sy);
		LCD_WriteCmd(0x0213);   LCD_WriteData(height);
	
		LCD_WriteCmd(0x0200);   LCD_WriteData(sx);
		LCD_WriteCmd(0x0201);   LCD_WriteData(sy);
	
		LCD_WriteCmd(0x0202);
	}
	else
	{
		LCD_WriteCmd(0x0212);   LCD_WriteData(sx);
		LCD_WriteCmd(0x0213);   LCD_WriteData(width);
		LCD_WriteCmd(0x0210);   LCD_WriteData(sy);
		LCD_WriteCmd(0x0211);   LCD_WriteData(height);
	
		LCD_WriteCmd(0x0201);   LCD_WriteData(sx);
		LCD_WriteCmd(0x0200);   LCD_WriteData(sy);
	
		LCD_WriteCmd(0x0202);
	}
#endif

#ifdef TFT26_ILI9325D
	if(tftlcd_data.dir==0)	
	{
		LCD_WriteCmdData(0x0050, sx); // Horizontal GRAM Start Address 
		LCD_WriteCmdData(0x0051, width); // Horizontal GRAM End Address 
		LCD_WriteCmdData(0x0052, sy); // Vertical GRAM Start Address 
		LCD_WriteCmdData(0x0053, height); // Vertical GRAM Start Address 
	
		LCD_WriteCmdData(0x0020, sx); // GRAM horizontal Address 
		LCD_WriteCmdData(0x0021, sy); // GRAM Vertical Address
		LCD_WriteCmd(0x0022);
	}
	else
	{
		LCD_WriteCmdData(0x0052, sx); // Horizontal GRAM Start Address 
		LCD_WriteCmdData(0x0053, width); // Horizontal GRAM End Address 
		LCD_WriteCmdData(0x0050, sy); // Vertical GRAM Start Address 
		LCD_WriteCmdData(0x0051, height); // Vertical GRAM Start Address 
	
		LCD_WriteCmdData(0x0021, sx); // GRAM horizontal Address 
		LCD_WriteCmdData(0x0020, sy); // GRAM Vertical Address
		LCD_WriteCmd(0x0022);
	}
#endif

#ifdef TFT24_ST7789S
		LCD_WriteCmd(0x2a);   
		LCD_WriteData(sx>>8);
		LCD_WriteData(sx&0xff);
		LCD_WriteData(width>>8);
		LCD_WriteData(width&0xff);
	
		LCD_WriteCmd(0x2b);   
		LCD_WriteData(sy>>8);
		LCD_WriteData(sy&0xff);
		LCD_WriteData(height>>8);
		LCD_WriteData(height&0xff);

		LCD_WriteCmd(0x2c);
#endif

#ifdef TFT24_SSD1297
		if(tftlcd_data.dir==0)
		{
			LCD_WriteCmd(0x0044);LCD_WriteData(width<<8|sx);	
			LCD_WriteCmd(0x0045);LCD_WriteData(sy);  	  
			LCD_WriteCmd(0x0046);LCD_WriteData(height);	 	
			LCD_WriteCmd(0x004e);LCD_WriteData(sx); 	
			LCD_WriteCmd(0x004f);LCD_WriteData(sy); 	
			LCD_WriteCmd(0x0022);  
		}
		else
		{
			LCD_WriteCmd(0x0044);LCD_WriteData(height<<8|sy);	
			LCD_WriteCmd(0x0045);LCD_WriteData(sx);  	  
			LCD_WriteCmd(0x0046);LCD_WriteData(width);	 	
			LCD_WriteCmd(0x004e);LCD_WriteData(sy); 	
			LCD_WriteCmd(0x004f);LCD_WriteData(sx); 	
			LCD_WriteCmd(0x0022);	
		} 
#endif

#ifdef TFT20_ILI9225
	if(tftlcd_data.dir==0)	
	{
		LCD_WriteCmdData(0x0037, sx);
		LCD_WriteCmdData(0x0036, width); 
		LCD_WriteCmdData(0x0039, sy);
		LCD_WriteCmdData(0x0038, height);
	
		LCD_WriteCmdData(0x0020, sx);
		LCD_WriteCmdData(0x0021, sy);
	
		LCD_WriteCmd(0x0022);
	}
	else
	{
		LCD_WriteCmdData(0x0039, sx);
		LCD_WriteCmdData(0x0038, width); 
		LCD_WriteCmdData(0x0037, sy);
		LCD_WriteCmdData(0x0036, height);
	
		LCD_WriteCmdData(0x0021, sx);
		LCD_WriteCmdData(0x0020, sy);
	
		LCD_WriteCmd(0x0022);
	}
#endif

#ifdef TFT20_ILI9341
		LCD_WriteCmd(0x2a);   
		LCD_WriteData_Color(sx);
		LCD_WriteData_Color(width);
	
		LCD_WriteCmd(0x2b);   
		LCD_WriteData_Color(sy);
		LCD_WriteData_Color(height);

		LCD_WriteCmd(0x2c);
#endif

#ifdef TFT20_ST7775R
	if(tftlcd_data.dir==0)	
	{
		LCD_WriteCmd(0x36);LCD_WriteData(width); 
		LCD_WriteCmd(0x37);LCD_WriteData(sx); 
		LCD_WriteCmd(0x38);LCD_WriteData(height); 
		LCD_WriteCmd(0x39);LCD_WriteData(sy); 
	
		LCD_WriteCmd(0x20);LCD_WriteData(sx);
		LCD_WriteCmd(0x21);LCD_WriteData(sy);
	
		LCD_WriteCmd(0x22);
	}
	else
	{
		LCD_WriteCmd(0x36);LCD_WriteData(height); 
		LCD_WriteCmd(0x37);LCD_WriteData(sy); 
		LCD_WriteCmd(0x38);LCD_WriteData(width); 
		LCD_WriteCmd(0x39);LCD_WriteData(sx); 
	
		LCD_WriteCmd(0x20);LCD_WriteData(sy);
		LCD_WriteCmd(0x21);LCD_WriteData(sx);
	
		LCD_WriteCmd(0x22);
	}
#endif

#ifdef TFT20_ST7775RV
	if(tftlcd_data.dir==0)	
	{
		LCD_WriteCmd(0x36);LCD_WriteData(width); 
		LCD_WriteCmd(0x37);LCD_WriteData(sx); 
		LCD_WriteCmd(0x38);LCD_WriteData(height); 
		LCD_WriteCmd(0x39);LCD_WriteData(sy); 
	
		LCD_WriteCmd(0x20);LCD_WriteData(sx);
		LCD_WriteCmd(0x21);LCD_WriteData(sy);
	
		LCD_WriteCmd(0x22);
	}
	else
	{
		LCD_WriteCmd(0x36);LCD_WriteData(height); 
		LCD_WriteCmd(0x37);LCD_WriteData(sy); 
		LCD_WriteCmd(0x38);LCD_WriteData(width); 
		LCD_WriteCmd(0x39);LCD_WriteData(sx); 
	
		LCD_WriteCmd(0x20);LCD_WriteData(sy);
		LCD_WriteCmd(0x21);LCD_WriteData(sx);
	
		LCD_WriteCmd(0x22);
	}
#endif

#ifdef TFT20_ILI9225C
	if(tftlcd_data.dir==0)	
	{
		LCD_WriteCmdData(0x0037, sx);
		LCD_WriteCmdData(0x0036, width); 
		LCD_WriteCmdData(0x0039, sy);
		LCD_WriteCmdData(0x0038, height);
	
		LCD_WriteCmdData(0x0020, sx);
		LCD_WriteCmdData(0x0021, sy);
	
		LCD_WriteCmd(0x0022);
	}
	else
	{
		LCD_WriteCmdData(0x0039, sx);
		LCD_WriteCmdData(0x0038, width); 
		LCD_WriteCmdData(0x0037, sy);
		LCD_WriteCmdData(0x0036, height);
	
		LCD_WriteCmdData(0x0021, sx);
		LCD_WriteCmdData(0x0020, sy);
	
		LCD_WriteCmd(0x0022);
	}
#endif

#ifdef TFT20_R61503U
	if(tftlcd_data.dir==0)	
	{
		LCD_WriteCmdData(0x0050, sx); // Horizontal Address Start Position
		LCD_WriteCmdData(0x0051, width); // Horizontal Address End Position
		LCD_WriteCmdData(0x0052, sy); // Vertical Address Start Position
		LCD_WriteCmdData(0x0053, height); // Vertical Address End Position
	
		LCD_WriteCmdData(0x0020, sx); // Horizontal Address Start Position
		LCD_WriteCmdData(0x0021, sy); // Vertical Address Start Position
		LCD_WriteCmd(0x0022); 	
	}
	else
	{
		LCD_WriteCmdData(0x0052, sx); // Horizontal Address Start Position
		LCD_WriteCmdData(0x0053, width); // Horizontal Address End Position
		LCD_WriteCmdData(0x0050, sy); // Vertical Address Start Position
		LCD_WriteCmdData(0x0051, height); // Vertical Address End Position
	
		LCD_WriteCmdData(0x0021, sx); // Horizontal Address Start Position
		LCD_WriteCmdData(0x0020, sy); // Vertical Address Start Position
		LCD_WriteCmd(0x0022);	
	}	
#endif

#ifdef TFT20_HX8340B
	if(tftlcd_data.dir==0)
	{
		LCD_WriteCmd(0x02);LCD_WriteData(sx>>8);     
		LCD_WriteCmd(0x03);LCD_WriteData(sx&0xff);	 
		LCD_WriteCmd(0x04);LCD_WriteData(width>>8); 
		LCD_WriteCmd(0x05);LCD_WriteData(width&0xff); 
		
		LCD_WriteCmd(0x06);LCD_WriteData(sy>>8); 
		LCD_WriteCmd(0x07);LCD_WriteData(sy&0xff);
		LCD_WriteCmd(0x08);LCD_WriteData(height>>8); 
		LCD_WriteCmd(0x09);LCD_WriteData(height&0xff);
	}
 	else
	{
		LCD_WriteCmd(0x02);LCD_WriteData(sx>>8);     
		LCD_WriteCmd(0x03);LCD_WriteData(sx&0xff);	 
		LCD_WriteCmd(0x04);LCD_WriteData(width>>8); 
		LCD_WriteCmd(0x05);LCD_WriteData(width&0xff); 
		
		LCD_WriteCmd(0x06);LCD_WriteData(sy>>8); 
		LCD_WriteCmd(0x07);LCD_WriteData(sy&0xff);
		LCD_WriteCmd(0x08);LCD_WriteData(height>>8); 
		LCD_WriteCmd(0x09);LCD_WriteData(height&0xff);
	} 	
	LCD_WriteCmd(0x22);
#endif

#ifdef TFT24_HX8357A
	if(tftlcd_data.dir==0)
	{
		LCD_WriteCmd(0x02);LCD_WriteData(sx>>8);     
		LCD_WriteCmd(0x03);LCD_WriteData(sx&0xff);	 
		LCD_WriteCmd(0x04);LCD_WriteData(width>>8); 
		LCD_WriteCmd(0x05);LCD_WriteData(width&0xff); 
		
		LCD_WriteCmd(0x06);LCD_WriteData(sy>>8); 
		LCD_WriteCmd(0x07);LCD_WriteData(sy&0xff);
		LCD_WriteCmd(0x08);LCD_WriteData(height>>8); 
		LCD_WriteCmd(0x09);LCD_WriteData(height&0xff);
	
		LCD_WriteCmdData(0x80,sx>>8); // Set CAC=0x0000 
		LCD_WriteCmdData(0x81,sx&0xff); 
		LCD_WriteCmdData(0x82,sy>>8); // Set RAC=0x0000 
		LCD_WriteCmdData(0x83,sy&0xff);	
	}
	else
	{
		LCD_WriteCmd(0x06);LCD_WriteData(sx>>8);     
		LCD_WriteCmd(0x07);LCD_WriteData(sx&0xff);	 
		LCD_WriteCmd(0x08);LCD_WriteData(width>>8); 
		LCD_WriteCmd(0x09);LCD_WriteData(width&0xff); 
		
		LCD_WriteCmd(0x02);LCD_WriteData(sy>>8); 
		LCD_WriteCmd(0x03);LCD_WriteData(sy&0xff);
		LCD_WriteCmd(0x04);LCD_WriteData(height>>8); 
		LCD_WriteCmd(0x05);LCD_WriteData(height&0xff);
	
		LCD_WriteCmdData(0x82,sx>>8); // Set CAC=0x0000 
		LCD_WriteCmdData(0x83,sx&0xff); 
		LCD_WriteCmdData(0x80,sy>>8); // Set RAC=0x0000 
		LCD_WriteCmdData(0x81,sy&0xff);	
	}
	LCD_WriteCmd(0x22);
#endif

#ifdef TFT18_S6D0144
	u16 x,y,xy;
	x=(width<<8)|sx;
	y=(height<<8)|sy;
	xy = (sy<<8)|sx;
	if(tftlcd_data.dir==0)
	{
		LCD_WriteCmd(0x44);LCD_WriteData(width<<8|sx);     	 
		LCD_WriteCmd(0x45);LCD_WriteData(height<<8|sy);  	
		LCD_WriteCmd(0x21);LCD_WriteData(sy<<8|sx);	
	}
	else
	{
		xy = (sx<<8)|sy;
		LCD_WriteCmd(0x45);LCD_WriteData(x);
	 	LCD_WriteCmd(0x44);LCD_WriteData(y);
	 	LCD_WriteCmd(0x21);LCD_WriteData(xy);
	}
		
	LCD_WriteCmd(0x22); 
#endif
}

//读取个某点的颜色值	 
//x,y:坐标
//返回值:此点的颜色
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r=0,g=0x0001,b=0x0001;
	u16 dat=0;
	if(x>=tftlcd_data.width||y>=tftlcd_data.height)return 0;	//超过了范围,直接返回		     
	LCD_Set_Window(x, y, x, y);
	
#ifdef TFT22_R61503B
	//LCD_Set_Window(x, y, x, y);
	dat=LCD_ReadData();  		//dummy Read
  	dat=LCD_ReadData();

	  
	b=dat>>11;				 
	g=(dat>>5)&0x003f;
	r=dat&0x001f;
	dat=(r<<11)|(g<<5)|(b); 
	 				    	   
	r=dat;
				    	   
	
#endif

#ifdef TFT22_ILI9225B	
	LCD_WriteCmd(0X0022);  		 				    	   
 	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//实际坐标颜色
#endif

#ifdef TFT24_ST7781R	
	LCD_WriteCmd(0X0022);
	r=LCD_ReadData();  		//dummy Read     		 				    	   
 	r=LCD_ReadData();  		//实际坐标颜色
#endif

#ifdef TFT26_R61509V	
	LCD_WriteCmd(0X0202);  		 				    	   
 	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//实际坐标颜色
#endif
	
#ifdef TFT26_ILI9325D	
	LCD_WriteCmd(0X0022);
	r=LCD_ReadData();  		//dummy Read     		 				    	   
 	r=LCD_ReadData();  		//实际坐标颜色
#endif

#ifdef TFT24_ST7789S
	dat=LCD_ReadData();  		//dummy Read
  	dat=LCD_ReadData();
	dat=dat<<8;
  	dat|=LCD_ReadData();
			    	   
	r=dat;	
#endif

#ifdef TFT20_ILI9225	
	LCD_WriteCmd(0X0022);  		 				    	   
 	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//实际坐标颜色
#endif

#ifdef TFT20_ILI9341	
	LCD_WriteCmd(0X2e);  		 				    	   
 	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//实际坐标颜色
	g=LCD_ReadData();
	b=LCD_ReadData();
	return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));  		
#endif

#ifdef TFT20_ST7775R	
	LCD_WriteCmd(0X22);  		 				    	   
 	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//实际坐标颜色
#endif	

#ifdef TFT20_ST7775RV	
	LCD_WriteCmd(0X22);  		 				    	   
 	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//实际坐标颜色
#endif

#ifdef TFT20_ILI9225C	
	LCD_WriteCmd(0X0022);  		 				    	   
 	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//实际坐标颜色
#endif

#ifdef TFT20_R61503U	
	LCD_WriteCmd(0X0022);  		 				    	   
 	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//实际坐标颜色
#endif

#ifdef TFT20_HX8340B	
	LCD_WriteCmd(0X22);  		 				    	   
 	r=LCD_ReadData();  		//dummy Read
	r=LCD_ReadData();  		//实际坐标颜色
	g=LCD_ReadData();
	b=LCD_ReadData();
	return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));  		
#endif

	return r;
}

//清屏函数
//color:要清屏的填充色
void LCD_Clear(u16 color)
{
	u16 i=0, j=0 ;

	LCD_Set_Window(0, 0, tftlcd_data.width-1, tftlcd_data.height-1);	 //作用区域
  	for(i=0; i<tftlcd_data.width; i++)
	{
		for (j=0; j<tftlcd_data.height; j++)
		{
			LCD_WriteData_Color(color);
		}
	} 
}

//在指定区域内填充单个颜色
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
void LCD_Fill(u16 xState,u16 yState,u16 xEnd,u16 yEnd,u16 color)
{          
	u16 temp=0;

    if((xState > xEnd) || (yState > yEnd))
    {
        return;
    }   
	LCD_Set_Window(xState, yState, xEnd, yEnd); 
    xState = xEnd - xState + 1;
	yState = yEnd - yState + 1;

	while(xState--)
	{
	 	temp = yState;
		while (temp--)
	 	{			
			LCD_WriteData_Color(color);	
		}
	}	
} 

//在指定区域内填充指定颜色块			 
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 			//得到填充的宽度
	height=ey-sy+1;			//高度
	LCD_Set_Window(sx, sy,ex, ey);
 	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			LCD_WriteData_Color(color[i*width+j]);
		}
	}		    
}

//画点
//x,y:坐标
//FRONT_COLOR:此点的颜色
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_Set_Window(x, y, x, y);  //设置点的位置
	LCD_WriteData_Color(FRONT_COLOR);	
}

//快速画点
//x,y:坐标
//color:颜色
void LCD_DrawFRONT_COLOR(u16 x,u16 y,u16 color)
{	   
	LCD_Set_Window(x, y, x, y);
	LCD_WriteData_Color(color);	
} 

//画一个大点
//2*2的点			   
void LCD_DrawBigPoint(u16 x,u16 y,u16 color)
{	    
	LCD_DrawFRONT_COLOR(x,y,color);//中心点 
	LCD_DrawFRONT_COLOR(x+1,y,color);
	LCD_DrawFRONT_COLOR(x,y+1,color);
	LCD_DrawFRONT_COLOR(x+1,y+1,color);	 	  	
}

//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t=0; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

void LCD_DrawLine_Color(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawFRONT_COLOR(uRow,uCol,color);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 


// 画一个十字的标记
// x：标记的X坐标
// y：标记的Y坐标
// color：标记的颜色
void LCD_DrowSign(u16 x, u16 y, u16 color)
{
    u8 i;

    /* 画点 */
    LCD_Set_Window(x-1, y-1, x+1, y+1);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color);   
    }

    /* 画竖 */
    LCD_Set_Window(x-4, y, x+4, y);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color); 
    }

    /* 画横 */
    LCD_Set_Window(x, y-4, x, y+4);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color); 
    }
}

//画矩形	  
//(x1,y1),(x2,y2):矩形的对角坐标
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 


//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16/24
//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数	
 	num=num-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=ascii_1206[num][t]; 	 	//调用1206字体
		else if(size==16)temp=ascii_1608[num][t];	//调用1608字体
		else if(size==24)temp=ascii_2412[num][t];	//调用2412字体
		else return;								//没有的字库
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawFRONT_COLOR(x,y,FRONT_COLOR);
			else if(mode==0)LCD_DrawFRONT_COLOR(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=tftlcd_data.height)return;		//超区域了
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=tftlcd_data.width)return;	//超区域了
				break;
			}
		}  	 
	}  	    	   	 	  
}   
//m^n函数
//返回值:m^n次方.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//显示数字,高位为0,则不显示
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//color:颜色 
//num:数值(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 

//显示数字,高位为0,还是显示
//x,y:起点坐标
//num:数值(0~999999999);	 
//len:长度(即要显示的位数)
//size:字体大小
//mode:
//[7]:0,不填充;1,填充0.
//[6:1]:保留
//[0]:0,非叠加显示;1,叠加显示.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//显示字符串
//x,y:起点坐标
//width,height:区域大小  
//size:字体大小
//*p:字符串起始地址		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//退出
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
				if(*p == ':')
					printf("x=%d,y=%d\r\n",(u16)x,(u16)y);
        p++;
    }
}

/****************************************************************************
*函数名：LCD_ShowFontHZ
*输  入：x：汉字显示的X坐标
*      * y：汉字显示的Y坐标
*      * cn：要显示的汉字
*      * wordColor：文字的颜色
*      * backColor：背景颜色
*输  出：
*功  能：写二号楷体汉字
****************************************************************************/
#if 1
void LCD_ShowFontHZ(u16 x, u16 y, u8 *cn)	 
{  
	u8 i, j, wordNum;
	u16 color;
	while (*cn != '\0')
	{
		LCD_Set_Window(x, y, x+31, y+28);
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNum扫描字库的字数
			if ((CnChar32x29[wordNum].Index[0]==*cn)
			     &&(CnChar32x29[wordNum].Index[1]==*(cn+1)))
			{
				
				for(i=0; i<116; i++) 
				{	//MSK的位数
					color=CnChar32x29[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							LCD_WriteData_Color(FRONT_COLOR); 						
						} 						
						else
						{
							LCD_WriteData_Color(BACK_COLOR); 
						} 
						color<<=1;
					}//for(j=0;j<8;j++)结束
				}    
			}
		} //for (wordNum=0; wordNum<20; wordNum++)结束 	
		cn += 2;
		x += 32;
	}
}
#endif


#if 0
void LCD_ShowFontHZ(u16 x, u16 y, u8 *cn)
{
	u8 i, j, wordNum;
	u16 color;
	u16 x0=x; 
	u16 y0=y; 
	while (*cn != '\0')
	{
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNum扫描字库的字数
			if ((CnChar32x29[wordNum].Index[0]==*cn)
			     &&(CnChar32x29[wordNum].Index[1]==*(cn+1)))
			{
				for(i=0; i<116; i++) 
				{	//MSK的位数
					color=CnChar32x29[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							LCD_DrawFRONT_COLOR(x,y,FRONT_COLOR);
						} 						
						else
						{
							LCD_DrawFRONT_COLOR(x,y,BACK_COLOR);
						} 
						color<<=1;
						x++;
						if((x-x0)==32)
						{
							x=x0;
							y++;
							if((y-y0)==29)
							{
								y=y0;
							}
						}
					}//for(j=0;j<8;j++)结束
				}	
			}
			
		} //for (wordNum=0; wordNum<20; wordNum++)结束 	
		cn += 2;
		x += 32;
		x0=x;
	}
}	
#endif

void LCD_ShowPicture(u16 x, u16 y, u16 wide, u16 high,u8 *pic)
{
	u16 temp = 0;
	long tmp=0,num=0;
	LCD_Set_Window(x, y, x+wide-1, y+high-1);
	num = wide * high*2 ;
	do
	{  
		temp = pic[tmp + 1];
		temp = temp << 8;
		temp = temp | pic[tmp];
		LCD_WriteData_Color(temp);//逐点显示
		tmp += 2;
	}
	while(tmp < num);	
}

