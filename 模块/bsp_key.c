#include "bsp_key.h"

/*******************************************************************************
* �� �� ��       : key_scan
* ��������		 : �����������Ƿ��£������򷵻ض�Ӧ��ֵ

*******************************************************************************/
unsigned char key_scan()
{
	unsigned char key_val;
	if(KEY1 == 0)
		key_val = 1;
	else if(KEY2 == 0)
		key_val = 2;
	else if(KEY5 == 0)
		key_val = 5;
	else if(KEY6 == 0)
		key_val = 6;
	else
		key_val = 0;
	return key_val;
}
