/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �V�X�e������                                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �O���[�o���ϐ��錾 */
STAT            mknl_ctx_stat;			/* �V�X�e���̃R���e�L�X�g��� */
T_MKNL_TCB      *mknl_run_mtcb = NULL;	/* ���s���^�X�N�R���g���[���u���b�N */
T_HOSPAC_CTXINF mknl_idlctx;			/* �A�C�h�����[�v�̃R���e�L�X�g */



/* �ʃJ�[�l���V�X�e���̏����� */
void mknl_ini_sys(void)
{
	/* �v���Z�b�T���ۉ��R���|�[�l���g�̏����� */
	hospac_ini_sys();
	
	/* �A�C�h���^�X�N���� */
	hospac_cre_ctx(&mknl_idlctx, 0, mknl_idl_loop, mknl_idl_stksz, mknl_idl_stk);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
