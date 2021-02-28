/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �^�X�N����                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �^�X�N�̋����҂� */
void mknl_sus_tsk(
		T_MKNL_TCB *mtcb)	/* �����҂���Ԃɂ���^�X�N */
{
	/* �^�X�N�̋����҂�(���f�B�[�L���[����O��) */
	if ( mtcb->tskstat == TTS_WAI )
	{
		mtcb->tskstat = TTS_WAS;
	}
	else
	{
		mtcb->tskstat = TTS_SUS;
		mknl_rmv_que(mtcb);
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
