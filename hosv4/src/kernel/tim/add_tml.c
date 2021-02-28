/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� ���ԊǗ�                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* �^�C�}�I�u�W�F�N�g�����X�g�ɒǉ� */
void kernel_add_tml(
		T_KERNEL_TIM *timobj)	/* �o�^����^�C�}�I�u�W�F�N�g */
{
	/* ���ɓo�^����Ă����牽�����Ȃ� */
	if ( timobj->next != NULL )
	{
		return;
	}
	
	/* ���X�g�ɓo�^ */
	if ( kernel_tml_head == NULL )
	{
		/* ���X�g����̏ꍇ�̒ǉ� */
		timobj->next = timobj;
		timobj->prev = timobj;
		kernel_tml_head = timobj;
	}
	else
	{
		/* ���X�g�̖����ɒǉ� */
		timobj->next = kernel_tml_head;
		timobj->prev = kernel_tml_head->prev;
		timobj->next->prev = timobj;
		timobj->prev->next = timobj;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
