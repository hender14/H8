/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �^�X�N����                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �^�X�N�D��x�ύX */
void mknl_chg_pri(
				T_MKNL_TCB *mtcb,	/* �D��x��ύX����^�X�N */
				PRI tskpri)			/* �ݒ肷��D��x */
{
	/* �D��x�ύX */
	if ( !(mtcb->tskstat & TTS_WAI) )
	{
		/* �҂���ԂłȂ���΃��f�B�[�L���[�Ɍq���Ȃ��� */
		mknl_rmv_que(mtcb);
		mknl_adf_que(&mknl_rdq_tbl[tskpri - TMIN_TPRI], mtcb);
	}
	mtcb->tskpri = tskpri;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
