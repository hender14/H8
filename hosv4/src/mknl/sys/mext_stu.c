/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �V�X�e������                                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �X�^�[�g�A�b�v���[�`���̏I������ */
void mknl_ext_startup(void)
{
	T_HOSPAC_CTXINF dmy_ctx;
	T_MKNL_TCB      *mtcb;
	
	mknl_ctx_stat = MKNL_TSS_TSK;	/* �^�X�N���ɐݒ� */
	
	/* �ō��D��x�̎��s�\�^�X�N��T�� */
	mtcb = mknl_srh_top();
	
	/* ���̊֐����Ăяo�����R���e�L�X�g���A�C�h���^�X�N�Ƃ��ď����J�n */
	if ( mtcb != NULL )
	{
		mknl_run_mtcb = mtcb;
		hospac_swi_ctx(&dmy_ctx, &mtcb->ctxinf);	/* �^�X�N���J�n */
	}
	else
	{
		mknl_run_mtcb = NULL;
		hospac_swi_ctx(&dmy_ctx, &mknl_idlctx);		/* �A�C�h���R���e�L�X�g�o�^�̂� */
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
