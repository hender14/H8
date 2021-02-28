/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*  �ʃJ�[�l�� �L���[����                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �^�X�N���L���[�����ɒǉ� */
void mknl_adf_que(
		T_MKNL_QUE *que,	/* �ǉ�����L���[ */
		T_MKNL_TCB *mtcb)	/* �ǉ�����^�X�N */
{
	T_MKNL_TCB *mtcb_head;
	T_MKNL_TCB *mtcb_tail;
	
	mtcb->que = que;
	if ( que->head == NULL )
	{
		/* �L���[�Ƀ^�X�N��������ΐ擪�ɐݒ� */
		que->head  = mtcb;
		mtcb->next = mtcb;
		mtcb->prev = mtcb;
	}
	else
	{
		/* �L���[�����ɒǉ� */
		mtcb_head       = que->head;
		mtcb_tail       = mtcb_head->prev;
		mtcb->next      = mtcb_head;
		mtcb->prev      = mtcb_tail;
		mtcb_head->prev = mtcb;
		mtcb_tail->next = mtcb;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
