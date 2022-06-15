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
//-----��Ҫ����
void key_proc(void);
void tft_proc(void);
//-----��ʱ������
long time_tick=0; 
unsigned int key_delay=0;//�����������ٱ���
unsigned int tft_delay=0;//Һ�����������ٱ���
unsigned int count=0;//����ʱ��
unsigned int count_old=999;//��һ�ε�����ʱ��������ʱ��ı�ʱ�ı�Һ����
unsigned char key_val=0;//��ȡ���İ���ֵ
unsigned char key_old=0,key_down=0;//��һ�εı��� �������½���
unsigned char key_time=0;//�����ж��Ƿ��ǳ���
unsigned char key_long=0;//������־λ ����ʱΪ1
unsigned char key_flag=0;//������ʼ��ʱ����1
//-----ȫ�ֱ���
unsigned char interface=1;//����ѡ��  1��ʼ������ 2���ȱ���� 3�Զ���ʱ�����
unsigned char BUF[20];//�ַ�����������
unsigned char line=0;//���ѡ����к�
unsigned char line_old;//���ѡ����һ�ε��к�
extern struct Washing_time M_Time[4];//�����ⲿ����ģʽʱ��Ľṹ��
extern code struct STU const Custom[];//�����Զ������Ľṹ��

unsigned char Laundry_Mode=0; //ϴ��ģʽ 0ǿ��ģʽ 1��׼ģʽ 2����ģʽ
unsigned char indicate=0;//0��  1��ˮ 2ϴ�� 3Ưϴ 4��ˮ 5 6����
unsigned int Start_Time=0;//��Ź��̵���ʼʱ��
unsigned char Temporary_time[4] = {0,0,0,0};//�����Զ���ģʽʱ����м����
unsigned char Position[4]={125,117,101,149};//Һ�������ֺ��������ڵ�λ��

/*******************************************************************************
* �� �� ��       : main
* ��������		 : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void main()
{	
	UART_Init();//���ڳ�ʼ��
	TFTLCD_Init();//Һ������ʼ��
	Mode_Selection();//��ʼ������ ѡ����Ҫ�ĸ�ģʽ
	//ProgressBar_Test();
	time0_init();//��ʱ����ʼ��
	printf("init OK\r\n");//�����ض������������Ϣ
	while(1)
	{		
		key_proc();//��������
		tft_proc();//Һ��������
	}		
}



/***********************��ʱ��0�жϺ���(10ms)***********************/
void time0() interrupt 1 
{
	time_tick ++;
	TH0=0XD8;	//����ʱ������ֵ����ʱ10ms
	TL0=0XF0;
	if(key_delay)//ֻ�в�����0��ʱ����Լ�
		key_delay = 0;//10msɨ��һ�ΰ���
	
	if(tft_delay)//ֻ�в�����0��ʱ����Լ�
		if(++tft_delay == 40) tft_delay = 0;//400ms��һ��Һ��������
	
	if(!(time_tick % 100))
		count++;//����ʱ��
}

/***********************����������Һ������Χ�仯����***********************/
void key_proc(void)
{
	if(key_delay) return;//ʱ��û�е��ͷ���
		else key_delay = 1;
	key_val = key_scan();//��ȡ������������
	key_down = key_val & (key_val ^ key_old);//��ȡ�½��� ��������½�����Ϊ0
	
	if((key_val == 6)&&(key_old == 0))//6�հ���ʱ
	{
		key_flag = 1;//��ʾ��һ�ΰ���
		key_down = 0;//�Ȳ���switch
	}
	
	if(key_flag)
		key_time++;//�����������10ms��һ�� ����10ms��һ��	
	
	if((key_val == 0)&&(key_old == 6))//6�ſ�ʱ�ж��Ƿ��ǳ���
	{	
		if(key_time >= 100)
			key_long = 1;//������־λ��1
		else
			key_long = 0;//������־λ��0
		key_flag = 0;//��־λ��0
		key_time = 0;//ʱ����0
		key_down = 6;//��switch
	}
	if(key_down != 0)
		printf("%d\r\n",(u16)key_down);//�����½���ʱ���������Ϣ
	
	switch(key_down)//���������ı仯
    {
		
		case 1://�ڽ���һ����ʱΪ�����ƶ����
			if(--line == 255) line = 3;			
			if(interface == 1)//����ѡ��ť
				Choice(line,line_old,Initialization);//ѡ��ʱ��� �������Ϊ �к� ��һ�����к� �ͽ�����
			else if(interface == 3)
				Choice(line,line_old,Customize);//ѡ��ʱ��� �������Ϊ �к� ��һ�����к� �ͽ�����
			
		break;
				
		case 5://�ڽ���һ����ʱΪ�����ƶ����
			if(++line == 4) line = 0;
			if(interface == 1)//����ѡ��ť
				Choice(line,line_old,Initialization);//ѡ��ʱ��� �������Ϊ �к� ��һ�����к� �ͽ�����
			else if(interface == 3)
				Choice(line,line_old,Customize);//ѡ��ʱ��� �������Ϊ �к� ��һ�����к� �ͽ�����
		break;
		
		case 6: 
		if((interface == 3) && (key_long == 1))//Ϊ����ʱΪȷ��
		{
			//���Զ������ʱΪ����ʱ��ʱ�����鸳ֵ���ṹ��
			M_Time[3].Wat=(u16)Temporary_time[0];//��ȷ���Ժ�ֵʱ��
			M_Time[3].Was=(u16)Temporary_time[1];
			M_Time[3].Ri=(u16)Temporary_time[2];
			M_Time[3].De=(u16)Temporary_time[3];
			printf("%d,%d,%d,%d\r\n",(u16)M_Time[3].Wat,(u16)M_Time[3].Was,(u16)M_Time[3].Ri,(u16)M_Time[3].De);//���������Ϣ
			interface = 2;//�����л�������������
			Schedule();//���ȱ����
			Laundry_Mode = 3;//ģʽΪ�Զ���ģʽ
			Start_Time = count;//��ֵ��ˮ��ʼʱ��
			indicate = 1;//����Ϊ��ˮ
		}else if((interface == 3) && (key_long == 0))//Ϊ�̰�ʱΪʱ���
		{
				if(Temporary_time[line] >= 5)//����5�ſ��Լ�
					Temporary_time[line] -= 5;//��Ӧʱ��-5
				sprintf(BUF,"%02d",(u16)Temporary_time[line]);//��ʽ���ַ���
				LCD_ShowString(Position[line],Custom[line].y,tftlcd_data.width,tftlcd_data.height,16,BUF);//Һ�������
		}
		
		if(interface == 1)//��ģʽ����ʱΪȷ����ť
		{
				if(line != 3)//�����Զ���ģʽʱ
				{
					interface = 2;//����������
					Schedule();//���ȱ����
					Laundry_Mode = line;//ģʽΪ�к�
					Start_Time = count;//��ֵ��ˮ��ʼʱ��
					indicate = 1;//����Ϊ��ˮ
				}else
				{
					line = 0;//������0
					Custom_Time();//�Զ������
					interface = 3;//����3 �Զ���ģʽ
				}
		 }
		if(indicate == 6)//��ϴ�½���ʱ���°���6��������һ��
		{
			indicate=0;
			interface=1;//��ʼ������
			line = 0;//������0
			LCD_Clear(BACK_COLOR);//����Ϊ��ɫ
			Mode_Selection();//��ʼ������ ѡ����Ҫ�ĸ�ģʽ
		}
			
		break;
		
		case 2:
			if(interface == 3)//���Զ������ʱ
			{
				if(Temporary_time[line] <= 95)//ʱ�䲻�ܳ���100
					Temporary_time[line] += 5;//��Ӧʱ��+5
				sprintf(BUF,"%02d",(u16)Temporary_time[line]);//��ʽ���ַ���
				LCD_ShowString(Position[line],Custom[line].y,tftlcd_data.width,tftlcd_data.height,16,BUF);//Һ�������
			}
		break;		
	}
	key_old = key_val;//Ϊ��һ�εİ���ֵ��ֵ
	line_old = line;//��ȡ��һ�ε��к�
}

/***********************Һ����С��Χ�仯����***********************/
void tft_proc(void)
{
	if(tft_delay) return;//û��ʱ�䷵��������
		else tft_delay = 1;
	if(count != count_old)//��ʱ��ı�ʱ
	{
		sprintf(BUF,"%u",(u16)count);//��ʽʱ��Ϊ�ַ���
		FRONT_COLOR=WHITE;
		LCD_ShowString(109,300,tftlcd_data.width,tftlcd_data.height,16,BUF);//��ʱ����ʾ����Ļ��
		switch (indicate)//0��  1��ˮ 2ϴ�� 3Ưϴ 4��ˮ
    {
      	case 1://��ˮ������
					Progress_Bar(Start_Time,M_Time[Laundry_Mode].Wat,count,10,70);//����������
      	break;
				
      	case 2://ϴ�ӽ�����
					Progress_Bar(Start_Time,M_Time[Laundry_Mode].Was,count,10,110);
      	break;
				
				case 3://Ưϴ������
					Progress_Bar(Start_Time,M_Time[Laundry_Mode].Ri,count,10,150);
      	break;
				
				case 4://��ˮ������
					Progress_Bar(Start_Time,M_Time[Laundry_Mode].De,count,10,190);
      	break;
				
				case 5://����
					LCD_ShowString(Plan[4].x,Plan[4].y,tftlcd_data.width,tftlcd_data.height,16,Plan[4].str);//Һ�������
					indicate++;//��ֹһֱ���
				break;	
      }
	
		count_old = count;//Ϊ��һ�ε�ʱ�丳ֵ
	}
}


