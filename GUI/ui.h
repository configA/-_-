#include "tftlcd.h"
#include "touch.h"
#include "gui.h"
#include "Progress.h"
#include "public.h"


#define Initialization 	 1 //��ʼ������Ϊ1
#define Customize  			 0 //�Զ������Ϊ0

void Mode_Selection();//��ʼ������
//�к�����һ�ε��к�  �ӵ�0�п�ʼ
void Choice(u8 line,u8 line_old,u8 Interface);//ѡ��ʱ���
void Schedule();//���ȱ����
void Custom_Time();//ʱ�����ý���