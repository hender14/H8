/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �^�X�N����                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �^�X�N�̊J�n */
void mknl_sta_tsk(
		T_MKNL_TCB *mtcb,					/* �ʃJ�[�l���^�X�N�R���g���[���u���b�N */
		VP_INT     exinf,					/* �^�X�N�̊g����� */
		FP         task,					/* �^�X�N�̋N���Ԓn */
		PRI        tskpri,					/* �^�X�N�̋N�����D��x */
		SIZE       stksz,					/* �^�X�N�̃X�^�b�N�̈�̃T�C�Y */
		VP         stk)						/* �^�X�N�̃X�^�b�N�̈�̐擪�Ԓn */
{
	/* ���s�R���e�L�X�g�̍쐬 */
	mtcb->data = exinf;
	hospac_cre_ctx(&mtcb->ctxinf, exinf, task, stksz, stk);

	/* �^�X�N�̏�Ԑݒ� */
	mtcb->tskstat = TTS_RDY;	/* ���f�B�[��Ԃɐݒ� */
	mtcb->texstat = 0;			/* ��O��ԏ����� */
	mtcb->tskpri  = tskpri;		/* �D��x�ݒ� */
	mtcb->tskwait = 0;			/* �҂��v�������� */

	/* ���f�B�[�L���[�ɐݒ� */
	mknl_adf_que(&mknl_rdq_tbl[tskpri - TMIN_TPRI], mtcb);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
