#include "Progress.h"
extern unsigned int Start_Time;//��ʼʱ��
extern unsigned int count;//����ʱ��
extern unsigned char indicate;
struct Washing_time M_Time[4] = {//����ģʽʱ��Ľṹ��  0��ˮ 1ϴ�� 2Ưϴ 3��ˮ
{15,15,15,10},			//ǿ��ģʽ
{10,10,10,8},
{5,5,5,3},
{0,0,0,0}};

//��������ʾ
//percent�����ȣ��ٷ���
void ProgressBar_Show(u8 percent,u8 PROGRESSBAR_START_X,u8 PROGRESSBAR_START_Y)
{
	//static u8 int_flag=0;
	u8 temp[4];
	u8 color_temp=0;
	u8 font_size=12;
	u8 progress;//��������ʵ�ʳ���
	
	progress = (percent*PROGRESSBAR_WIDTH)/100;
	color_temp=BACK_COLOR;//����ɫ 
	if(percent<10)
	{
		temp[0]=' ';
		temp[1]=' ';
		temp[2]=percent%100%10+0x30;//��ʾ��λ	
	}	
	else if(percent<100)
	{
		temp[0]=' ';
		temp[1]=percent%100/10+0x30;
		temp[2]=percent%100%10+0x30;//��ʾ��λ��
	}
	else
	{
		temp[0]=percent/100+0x30;
		temp[1]=percent%100/10+0x30;
		temp[2]=percent%100%10+0x30;//��ʾ100	
	}		
	temp[3]='%';
//	if(int_flag==0) //ֻ����һ�γ�ʼ��
//	{
//		int_flag=1;
//		gui_fill_rectangle(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,PROGRESSBAR_WIDTH,PROGRESSBAR_HEIGHT,PROGRESSBAR_BACKCOLOR);//������		
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



//��ʼ��ʱ��  �����ʱ��  ���ڵ�ʱ�� ��������λ��
void Progress_Bar(u16 Start,u16 Time_Required,u16 Now_Time,u8 X,u8 Y)
{
	u8 Percentage=0;//�ٷֱ�
	u16 time=0;
	Percentage = ((float)(Now_Time - Start)/(Time_Required))*100;//����ٷֱ�
	//gui_fill_rectangle(PROGRESSBAR_START_X,PROGRESSBAR_START_Y,PROGRESSBAR_WIDTH,PROGRESSBAR_HEIGHT,PROGRESSBAR_BACKCOLOR);
	printf("Now=%d Start=%d Req=%d %d\r\n",Now_Time,Start,Time_Required,(u16)Percentage);
	ProgressBar_Show((u8)Percentage,X,Y);
	if(Percentage >= 100)
	{
		Start_Time = count;//Ϊ��һ�����̵���ʼʱ����׼��
		if(++indicate == 6)  indicate = 0;
	}
}

