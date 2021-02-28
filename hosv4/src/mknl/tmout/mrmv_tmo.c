/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �^�C���A�E�g�L���[�Ǘ�                                     */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �^�C���A�E�g�҂��s�񂩂�^�X�N����菜�� */
void mknl_rmv_tmout(
		T_MKNL_TCB *mtcb)	/* �҂��s�񂩂�폜����^�X�N */
{
	/* �^�C���A�E�g�L���[�ɖ��ڑ��Ȃ疳�� */
	if ( mtcb->tm_prev == NULL )
	{
		return;
	}

	/* �L���[�̍Ō�̂P�^�X�N�Ȃ� */
	if ( mtcb->tm_next == mtcb )
	{
		mknl_timout_head = NULL;	/* �^�C���A�E�g�L���[����ɂ��� */
	}
	else
	{
		/* �����łȂ���� */
		if ( mtcb != mknl_timout_head->tm_prev )
		{
			/* ���ԍ����𐴎Z */
			mtcb->tm_next->diftim += mtcb->diftim;
		}
	
		/* �擪�Ȃ� */
		if ( mtcb == mknl_timout_head )
		{
			mknl_timout_head = mtcb->tm_next;	/* �擪�ʒu�X�V */
		}
		
		/* �L���[����O�� */
		mtcb->tm_next->tm_prev = mtcb->tm_prev;
		mtcb->tm_prev->tm_next = mtcb->tm_next;
	}
	
	/* ���ڑ��ɐݒ� */
	mtcb->tm_prev = NULL;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
