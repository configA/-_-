#include "ui.h"

code struct STU const Coord[]={
{5,50,"Strong mode:55S"},
{5,70,"standards mode:38S"},
{5,90,"Quick mode:18S"},
{5,110,"Custom mode"},

{5,150,"KEY1:UP"},
{5,170,"KEY5:DOWN"},
{5,190,"KEY6:CONFIRM"},
{5,210},
{5,230},
{5,250},
{5,270},
{5,300}};//��ʼ�����������ṹ��

code struct STU const Plan[]={//���������溯���ṹ��
{5,50,"Water Volume"},
{5,90,"Wash"},
{5,130,"Rinse"},
{5,170,"Dehydration"},
{5,210,"KEY6:Once more"}};

code struct STU const Custom[]={//�Զ������ṹ��
{5,50,"Lnfluent Time: "},
{5,70,"Washing Time: "},
{5,90,"Rinse Time: "},
{5,110,"Dehydration Time: "},

{5,150,"KEY1:UP"},
{5,170,"KEY5:DOWN"},
{5,190,"KEY2:ADD"},
{5,210,"KEY6:SUB "},
{5,230,"LONG KEY6:CONFIRM"},
{5,250},
{5,270},
{5,300}};//��ʼ�����������ṹ��

//��ʼ������
void Mode_Selection()
{
	u8 i = 0;
	FRONT_COLOR=BROWN;
	LCD_ShowString(25,10,tftlcd_data.width,tftlcd_data.height,16,"Washing machine system");
	
	FRONT_COLOR=BRRED;
	LCD_ShowString(5,300,tftlcd_data.width,tftlcd_data.height,16,"Running time:");
	
	
	FRONT_COLOR=RED;//��һ��Ϊ��ɫ
	LCD_ShowString(Coord[0].x,Coord[0].y,tftlcd_data.width,tftlcd_data.height,16,Coord[0].str);//ǿ��ģʽ
	FRONT_COLOR=WHITE;//Ĭ�Ϻ���Ϊ��ɫ
	
	for(i=1;i<8;i++)
		LCD_ShowString(Coord[i].x,Coord[i].y,tftlcd_data.width,tftlcd_data.height,16,Coord[i].str);//��׼ģʽ

}


//�к�����һ�ε��к� �͵�ǰ�Ľ���  �ӵ�0�п�ʼ
void Choice(u8 line,u8 line_old,u8 Interface)//ѡ��ʱ���
{	
	if(Interface)
	{
		FRONT_COLOR=WHITE;//��ɫ
		LCD_ShowString(Coord[line_old].x,Coord[line_old].y,tftlcd_data.width,tftlcd_data.height,16,Coord[line_old].str);
		
		FRONT_COLOR=RED;//��ɫ
		LCD_ShowString(Coord[line].x,Coord[line].y,tftlcd_data.width,tftlcd_data.height,16,Coord[line].str);
	}else
	{
		FRONT_COLOR=WHITE;//��ɫ
		LCD_ShowString(Custom[line_old].x,Custom[line_old].y,tftlcd_data.width,tftlcd_data.height,16,Custom[line_old].str);
	
		FRONT_COLOR=RED;//��ɫ
		LCD_ShowString(Custom[line].x,Custom[line].y,tftlcd_data.width,tftlcd_data.height,16,Custom[line].str);
	}
}


void Schedule()//���ȱ����
{
	u8 i = 0;
	LCD_Clear(BACK_COLOR);//����Ϊ��ɫ
	FRONT_COLOR=BROWN;
	LCD_ShowString(50,10,tftlcd_data.width,tftlcd_data.height,16,"Washer Schedule");
	
	FRONT_COLOR=BRRED;
	LCD_ShowString(5,300,tftlcd_data.width,tftlcd_data.height,16,"Running time:");
	
	FRONT_COLOR=WHITE;//Ĭ�Ϻ���Ϊ��ɫ
	for(i=0;i<4;i++)
	{
		LCD_ShowString(Plan[i].x,Plan[i].y,tftlcd_data.width,tftlcd_data.height,16,Plan[i].str);//��ˮ
		gui_fill_rectangle(10,(70+i*40),PROGRESSBAR_WIDTH,PROGRESSBAR_HEIGHT,PROGRESSBAR_BACKCOLOR);//����������  70 110 150 190
		ProgressBar_Show(0,10,(70+i*40));//��ʼ������0
	}
}


void Custom_Time()//ʱ�����ý���
{
	u8 i = 0;
	LCD_Clear(BACK_COLOR);//����Ϊ��ɫ
	FRONT_COLOR=BROWN;
	LCD_ShowString(60,10,tftlcd_data.width,tftlcd_data.height,16,"Custom MODE");
	
	FRONT_COLOR=BRRED;
	LCD_ShowString(5,300,tftlcd_data.width,tftlcd_data.height,16,"Running time:");
	
	FRONT_COLOR=RED;//��һ��Ϊ��ɫ
	LCD_ShowString(Custom[0].x,Custom[0].y,tftlcd_data.width,tftlcd_data.height,16,Custom[0].str);//����ʱ��
	FRONT_COLOR=WHITE;//Ĭ�Ϻ���Ϊ��ɫ
	for(i=1;i<9;i++)
	{
		LCD_ShowString(Custom[i].x,Custom[i].y,tftlcd_data.width,tftlcd_data.height,16,Custom[i].str);//����ʱ��
	}
}


