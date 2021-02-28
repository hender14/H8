/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �^�X�N����                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �^�X�N�̋����҂����� */
void mknl_rsm_tsk(
		T_MKNL_TCB *mtcb)	/* �����҂���������^�X�N */
{
	/* �����҂����� */
	if ( mtcb->tskstat == TTS_WAS )
	{
		mtcb->tskstat = TTS_WAI;		/* ��d�҂���ԂȂ�҂���� */
	}
	else
	{
		mtcb->tskstat = TTS_RDY;		/* �����҂���ԂȂ���s�\��� */
		mknl_adf_que(&mknl_rdq_tbl[mtcb->tskpri - TMIN_TPRI], mtcb);
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
