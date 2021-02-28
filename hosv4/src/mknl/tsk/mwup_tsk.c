/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �^�X�N����                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �^�X�N�̑҂����� */
void mknl_wup_tsk(
		T_MKNL_TCB *mtcb,	/* �X���[�v��������^�X�N */
		ER_UINT    ercd)	/* ��������^�X�N�ɓn���G���[�R�[�h */
{
	/* �^�X�N�̃X���[�v���� */
	mtcb->ercd = ercd;
	mknl_rmv_que(mtcb);
	if ( mtcb->tskstat == TTS_WAI )
	{
		mtcb->tskstat = TTS_RDY;	/* �҂������Ȃ���s�\��� */
		mknl_adf_que(&mknl_rdq_tbl[mtcb->tskpri - TMIN_TPRI], mtcb);
	}
	else
	{
		mtcb->tskstat = TTS_SUS;	/* ��d�҂���ԂȂ狭���҂���� */
	}
	mtcb->tskwait = 0;		/* �҂��v���N���A */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
