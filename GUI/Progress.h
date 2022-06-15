#include "public.h"  
#include "uart.h"
#include "tftlcd.h"
#include "touch.h"
#include "gui.h"

//#define PROGRESSBAR_START_X		10	  	//��������ʼX����
//#define PROGRESSBAR_START_Y		30		//��������ʼY����
#define PROGRESSBAR_WIDTH		200		//��������
#define PROGRESSBAR_HEIGHT		10		//��������

#define PROGRESSBAR_BACKCOLOR	GREEN  	//����ɫ
#define PROGRESSBAR_FRONTCOLOR	RED   	//ǰ��ɫ
#define PROGRESSBAR_FONTCOLOR	BLUE   //������ֵ��ɫ

void ProgressBar_Show(u8 percent,u8 PROGRESSBAR_START_X,u8 PROGRESSBAR_START_Y);
void ProgressBar_Test(u8 PROGRESSBAR_START_X,u8 PROGRESSBAR_START_Y);
//��ʼ��ʱ��  �����ʱ��  ���ڵ�ʱ�� x���� y����
void Progress_Bar(u16 Start,u16 Time_Required,u16 Now_Time,u8 X,u8 Y);