/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �^�X�N����                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �^�X�N�̏I�� */
void mknl_ter_tsk(
				T_MKNL_TCB *mtcb)	/* �I��������^�X�N */
{
	/* �^�C���A�E�g�L���[�ɂ���΍폜 */
	mknl_rmv_tmout(mtcb);		

	/* �^�X�N�L���[����O�� */
	if ( mtcb->que != NULL )
	{
		mknl_rmv_que(mtcb);
	}

	mtcb->tskstat = TTS_DMT;	/* �x�~��Ԃɐݒ� */
	mtcb->tskwait = 0;			/* �҂��v���N���A */

	/* ���s�R���e�L�X�g�̍폜 */
	hospac_del_ctx(&mtcb->ctxinf);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
