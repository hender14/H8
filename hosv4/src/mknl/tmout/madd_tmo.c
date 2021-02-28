/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �^�C���A�E�g�L���[�Ǘ�                                     */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �^�C���A�E�g�҂��s��Ƀ^�X�N��ǉ� */
ER mknl_add_tmout(
		T_MKNL_TCB *mtcb,	/* �҂��s��ɉ�����^�X�N */
		RELTIM     tmout)	/* �^�C���A�E�g�܂ł̎��� */
{
	T_MKNL_TCB* mtcb_tmp;

	/* �ŏ��̂P�Ȃ� */
	if ( mknl_timout_head == NULL )
	{
		/* �ŏ��̂P���L���[�ɓo�^ */
		mtcb->tm_next    = mtcb;
		mtcb->tm_prev    = mtcb;
		mknl_timout_head = mtcb;

		/* �^�C���A�E�g������ݒ� */
		mtcb->diftim = tmout;

		return E_OK;
	}
	
	/* �}���ꏊ������ */
	mtcb_tmp = mknl_timout_head;
	do
	{
		/* ���Ԕ�r */
		if ( tmout < mtcb_tmp->diftim )
		{
			/* ���Ԃ̍�����ݒ� */
			mtcb_tmp->diftim -= tmout;
			mtcb->diftim      = tmout;

			/* ���X�g�ɑ}�� */
			mtcb->tm_next          = mtcb_tmp;
			mtcb->tm_prev          = mtcb_tmp->tm_prev;
			mtcb->tm_next->tm_prev = mtcb;
			mtcb->tm_prev->tm_next = mtcb;
			
			/* �擪�Ȃ� */
			if ( mtcb_tmp == mknl_timout_head )
			{
				mknl_timout_head = mtcb;	/* �擪�|�C���^�X�V */
			}
			
			return E_OK;
		}
		
		tmout -= mtcb_tmp->diftim;		/* ���������Z */
		
		mtcb_tmp = mtcb_tmp->tm_next;	/* ����TCB�֐i�� */
	} while ( mtcb_tmp != mknl_timout_head );	/* ���X�g���������܂Ń��[�v */
	
	/* �����ɒǉ� */
	mtcb->tm_next          = mtcb_tmp;
	mtcb->tm_prev          = mtcb_tmp->tm_prev;
	mtcb->tm_next->tm_prev = mtcb;
	mtcb->tm_prev->tm_next = mtcb;

	/* �c����������ݒ� */
	mtcb->diftim = tmout;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
