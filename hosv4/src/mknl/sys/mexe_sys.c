/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �V�X�e������ �V�X�e���^�X�N���s                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"


static void mknl_exe_sys_start(VP_INT exinf);	/* �V�X�e���^�X�N�̎��s */

static FP mknl_exe_sys_exec;					/* �V�X�e�����s�Ԓn */


/* �V�X�e�����s  */
void mknl_exe_sys(
		FP     exec,
		VP_INT exinf)
{
	T_HOSPAC_CTXINF *ctxinf_run;
	
	/* ���s���R���e�L�X�g�̑ޔ� */
	ctxinf_run = &mknl_run_mtcb->ctxinf;
	
	/* �V�X�e�����s�Ԓn�ۑ� */
	mknl_exe_sys_exec = exec;
	
	/* �A�C�h���R���e�L�X�g���V�X�e���^�X�N�Ƃ��Ĉꎞ���p */
	hospac_del_ctx(&mknl_idlctx);												/* �A�C�h���R���e�L�X�g��j�� */
	hospac_cre_ctx(&mknl_idlctx, exinf, exec, mknl_idl_stksz, mknl_idl_stk);	/* �A�C�h���^�X�N���� */
	
	/* �^�X�N�R���e�L�X�g�X�C�b�`���s */
	mknl_run_mtcb = NULL;
	hospac_swi_ctx(ctxinf_run, &mknl_idlctx);
}


/* �V�X�e���^�X�N�̎��s */
void mknl_exe_sys_start(VP_INT exinf)
{
	/* �V�X�e���^�X�N�Ŏ��s */
	mknl_exe_sys_exec(exinf);
	
	/* ������A�C�h���ɖ߂� */
	mknl_idl_loop();
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
