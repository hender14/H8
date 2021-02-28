/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*  �ʃJ�[�l�� �L���[����                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �^�X�N�D��x���Œǉ� */
void mknl_adp_que(
		T_MKNL_QUE *que,	/* �ǉ�����L���[ */
		T_MKNL_TCB *mtcb)	/* �ǉ�����^�X�N */
{
	T_MKNL_TCB *mtcb_next;
	T_MKNL_TCB *mtcb_prev;
	
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
		/* �}���ʒu���L���[��擪���猟�� */
		mtcb_next = que->head;
		do {
			/* ��������D��̃^�X�N������Α}���ʒu���o���� */
			if ( mtcb_next->tskpri > mtcb->tskpri )
			{
				if ( mtcb_next == que->head )	/* �}���ʒu���擪�Ȃ� */
				{
					mtcb_prev = mtcb_next->prev;
					que->head = mtcb;
				}
				break;
			}

			/* ���ɐi�� */
			mtcb_prev = mtcb_next;
			mtcb_next = mtcb_next->next;
		} while ( mtcb_next != que->head );
		
		/* �^�X�N���L���[�ɑ}�� */
		mtcb->next      = mtcb_next;
		mtcb->prev      = mtcb_prev;
		mtcb_next->prev = mtcb;
		mtcb_prev->next = mtcb;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
