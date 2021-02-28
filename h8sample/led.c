#include "iodefine.h"
#include "led.h"

//-----------------------------------------------------------------------------
//  �T�@�v�F������
//  ��  ���F�Ȃ�
//  �߂�l�F�Ȃ�
//-----------------------------------------------------------------------------
void Led_init(void)
{
	IO.PDR6.BIT.B0	= 1;		//	�I�����WLED�̏���
	IO.PDR6.BIT.B4	= 1;		//	�O���[��LED�̏���
}

//-----------------------------------------------------------------------------
//  �T�@�v�FLED�̓_���E��������
//  ��  ���Fkind    LED�̐F���
//			onoff	�_���E�������
//  �߂�l�F0	����
//			-1	�ُ�
//-----------------------------------------------------------------------------
int Led_setLight(int kind, int onoff)
{
	if (kind == D_LED_KIND_ORANGE)
	{
		if (onoff == D_LED_LIGHT_OFF)
		{
			IO.PDR6.BIT.B0	= 1;
		}
		else
		{
			IO.PDR6.BIT.B0	= 0;
		}		
	}
	else if (kind == D_LED_KIND_GREEN)
	{
		if (onoff == D_LED_LIGHT_OFF)
		{
			IO.PDR6.BIT.B4	= 1;
		}
		else
		{
			IO.PDR6.BIT.B4	= 0;
		}
	}
	else
	{
		//	�F�w�肪�K��O�̏ꍇ�ُ�I��
		return -1;
	}
	
	return 0;
}
