/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (Windows�p)                            */
/*    ���荞�ݏ���                                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �[�����荞�݂̃G�~�����[�g(ITRON�^�X�N�Ƃ͖��֌W�̃X���b�h����ĂԂ���) */
void hospac_win_int(INTNO intno)
{
	T_HOSPAC_CTXINF *ctxinf;
	T_KERNEL_INTCB intcb;

	/* �͈̓`�F�b�N */
	if ( intno < KERNEL_TMIN_INTNO || intno > KERNEL_TMAX_INTNO )
	{
		return;
	}

	/* �Z�}�t�H����� */
	WaitForSingleObject(hospac_hSem, INFINITE);

	/* ���s���X���b�h���T�X�y���h���� */
	if ( mknl_run_mtcb != NULL )
	{
		ctxinf = &mknl_run_mtcb->ctxinf;
	}
	else
	{
		ctxinf = &mknl_idlctx;
	}
	SuspendThread(ctxinf->hThread);
	ctxinf->blIntSuspend = TRUE;
	Sleep(0);

	/* ���荞�݃t���O�Z�b�g */
	hospac_blInt = TRUE;

	/* ���[�J���ɃR�s�[ */
	intcb = KERNEL_INTNO_TO_INTCB(intno);

	/* ��^�X�N��(���荞�݃R���e�L�X�g�Ɉڍs) */
	mknl_sta_ind();
	
	/* ���荞�݂̎��s */
	if ( intcb.isr != NULL )
	{
		intcb.isr(intcb.exinf);		/* ���荞�݃T�[�r�X���[�`�����s */
	}

	/* �^�X�N���Ɉڍs */
	mknl_ext_ind();

	/* ���荞�݃t���O�N���A */
	hospac_blInt = FALSE;

	/* �x���t���O�N���A */
	mknl_ctx_stat = MKNL_TSS_TSK;

	/* �ō��D��x�̎��s�\�^�X�N��T�� */
	mknl_run_mtcb = mknl_srh_top();
	if ( mknl_run_mtcb != NULL )
	{
		ctxinf = &mknl_run_mtcb->ctxinf;
	}
	else
	{
		ctxinf = &mknl_idlctx;
	}

	/* �Z�}�t�H��ԋp */
	if ( ctxinf->blIntSuspend )
	{
		ctxinf->blIntSuspend = FALSE;
		ReleaseSemaphore(hospac_hSem, 1, NULL);
	}

	/* ���s���X���b�h�̕��A */
	ResumeThread(ctxinf->hThread);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
