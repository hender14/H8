/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �^�X�N����                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �^�X�N�̑҂��ݒ� */
void mknl_wai_tsk(
		T_MKNL_TCB *mtcb,		/* �҂���Ԃɂ���^�X�N */
		STAT        tskwait)	/* �҂��v�� */
{
	/* �҂���Ԃɐݒ� */
	mknl_rmv_que(mtcb);		/* ���f�B�[�L���[����O�� */
	mtcb->tskstat = TTS_WAI;
	mtcb->tskwait = tskwait;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
