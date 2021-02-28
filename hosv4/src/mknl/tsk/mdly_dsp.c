/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �^�X�N����                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �x�����Ă����f�B�X�p�b�`�̎��s */
void mknl_dly_dsp(void)
{
	/* �V�X�e���R���e�L�X�g�`�F�b�N */
	if ( mknl_ctx_stat & (MKNL_TSS_INDP | MKNL_TSS_DDSP | MKNL_TSS_DINT) )
	{
		return;		/* �f�B�X�p�b�`���s�\�łȂ���Εۗ����s */
	}

	/* �x���t���O�`�F�b�N */
	if ( !(mknl_ctx_stat & MKNL_TSS_DDLY) )
	{
		return;		/* �x����������Ή������Ȃ� */
	}

	/* �x���t���O�N���A */
	mknl_ctx_stat = MKNL_TSS_TSK;

	/* �x���f�B�X�p�b�`���s */
	mknl_exe_dsp();
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
