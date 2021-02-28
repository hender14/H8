/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*  �ʃJ�[�l�� �L���[����                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �L���[���N���A */
void mknl_clr_que(
		T_MKNL_QUE *que)	/* �N���A����L���[ */
{
	T_MKNL_TCB *mtcb;

	/* �҂��^�X�N�̉��� */
	while (	(mtcb = mknl_ref_qhd(que)) != NULL )
	{
		mknl_rmv_que(mtcb);			/* �C�x���g�t���O�̑҂��s�񂩂�폜 */
		mknl_rmv_tmout(mtcb);		/* �^�C���A�E�g�҂��s�񂩂�폜 */
		mknl_wup_tsk(mtcb, E_DLT);	/* �^�X�N�̑҂����� */
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
