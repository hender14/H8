/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*  �ʃJ�[�l�� �L���[����                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �^�X�N���L���[�����ɒǉ� */
void mknl_add_que(
		T_MKNL_QUE *que,	/* �ǉ�����L���[ */
		T_MKNL_TCB *mtcb,	/* �ǉ�����^�X�N */
		ATR        atr)		/* �ǉ����̑��� */
{
	if ( atr & TA_TPRI )
	{
		mknl_adp_que(que, mtcb);	/* �^�X�N�D��x���ɒǉ� */
	}
	else
	{
		mknl_adf_que(que, mtcb);	/* FIFO���ɒǉ� */
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
